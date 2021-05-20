#include <algorithm>
#include <forward_list>
#include <fstream>
#include <functional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "ara/log/logging.h"

#include "application/idc6mt/accessor/variable.h"

#include "configuration_parser.h"

namespace mt {

class ParseException : public std::runtime_error {
public:
    template<typename... Args>
    ParseException(Args&&... args)
        : std::runtime_error(std::forward<Args>(args)...)
    {
    }
};

ConfigurationFileParser::ConfigurationFileParser(
    ara::log::Logger& logger, const std::string& configurationPath)
{
    logger.LogVerbose() << "Parsing configuration file: " << configurationPath.c_str();

    auto allSections = ParseSections(configurationPath);

    for (const auto& s : allSections) {
        if (s.first == "COMMON") {
            // TODO config versioning
            logger.LogWarn() << "Config versioning is currently unsupported";
            continue;
        } else {
            try {
                auto variable = ParseVariableSection(s.first, s.second);
                logger.LogVerbose() << "Added variable " << s.first.c_str();
                m_variables.insert(std::move(variable));
            } catch (const ParseException& e) {
                logger.LogWarn() << "Error parsing section `" << s.first.c_str()
                                 << "`: " << e.what();
            } catch (const std::runtime_error& e) {
                logger.LogWarn() << "Critical Error parsing section `" << s.first.c_str()
                                 << "`: " << e.what();
            }
        }
    }
}

auto ConfigurationFileParser::GetVariables() & -> const std::unordered_set<Variable>&
{
    return m_variables;
}

auto ConfigurationFileParser::GetVariables() && -> std::unordered_set<Variable>
{
    return std::move(m_variables);
}

auto ConfigurationFileParser::ParseSections(const std::string& configPath)
    -> std::unordered_map<std::string, std::string>
{
    // Sections in `.ini` files are formatted as section name in square brackets. This regular
    // expression matches a line that looks like
    // `[NAME]`
    // and captures the NAME inside brackets.
    std::regex sectionNameRegex(R"(^\[(\w+)\])");

    std::unordered_map<std::string, std::string> records;
    auto it = records.begin();

    std::ifstream configFileStream(configPath);
    // For each line in the configuration file it is checked if this line is a section name or not
    for (std::string line; getline(configFileStream, line);) {
        std::smatch section;
        if (std::regex_match(line, section, sectionNameRegex)) {
            // If current line matches the regular expression, it's name is used as a key for the
            // `records` hashmap.
            auto res = records.insert({std::move(section[1].str()), {}});
            it = res.first;
        } else {
            // Other lines are values for the records hashmap and will be parsed later
            if (it == records.end()) {
                // Each configuration line must belong to a section. In case no section stands
                // before a configuration line, an exception is thrown because it means that
                // configuration file is malformed.
                throw ParseException("No section header");
            }
            it->second += line + " ";
        }
    }
    return records;
}

auto ConfigurationFileParser::ParseVariableSection(
    const std::string& sectionName, const std::string& sectionData) const -> Variable
{
    // The following regular expressions extract data from the corresponding configuration entries.
    std::regex addressRegex("address=([x0-9a-fA-F]+)", std::regex::extended);
    std::regex sizeRegex(R"(size=([x0-9a-fA-F]+))");
    std::regex offsetStringRegex(R"(offset=([0-9a-fA-Fx\:]+))");
    std::regex offsetValuesRegex(R"(([0-9a-fA-Fx]+)+)");

    auto extract = [&sectionData](auto&& regex) {
        std::smatch matches;
        if (std::regex_search(sectionData, matches, regex)) {
            if (matches.size() != 2) {
                throw ParseException("Malformed section");
            }
            return matches[1].str();
        } else {
            throw ParseException("Mandatory section missing");
        }
    };

    auto extractOffsets = [&offsetValuesRegex](auto&& offsetString) {
        std::smatch offsets;
        std::regex_match(offsetString, offsets, offsetValuesRegex);
        std::vector<uintptr_t> result;
        // The entry on index 0 respresents the whole line, the rest stand for the corresponding
        // capture groups
        for (size_t i = 1; i < offsets.size(); ++i) {
            result.push_back(std::stoull(offsets[i], 0, 16));
        }
        return result;
    };

    uintptr_t address = std::stoull(extract(addressRegex), 0, 16);
    size_t size = std::stoull(extract(sizeRegex), 0, 16);
    auto offsets = extractOffsets(extract(offsetStringRegex));

    return Variable(sectionName, address, size, std::move(offsets));
}

} // namespace mt
