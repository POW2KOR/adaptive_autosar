#include <algorithm>
#include <fstream>
#include <functional>
#include <regex>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <dirent.h>
#include <stdio.h>

#include "ara/log/logging.h"
#include "ara/log/logstream.h"

#include "application/idc6mt/accessor/variable.h"
#include "application/idc6mt/accessor/memory_accessor_factory.h"

#include "configuration_parser.h"
#include "measurement_daemon.h"

namespace mt {

MeasurementTraceDaemon::MeasurementTraceDaemon(const std::string& configurationDirectory)
{
    m_logger.LogInfo() << "Loading configuration";

    auto files = IterateDirectory(configurationDirectory, [](const std::string& s) {
        std::string ending = ".ini";
        return std::equal(ending.crbegin(), ending.crend(), s.crbegin());
    });

    if (files.empty()) {
        throw MtdException("Could not find any configuration files at " + configurationDirectory);
    }

    for (const auto& f : files) {
        auto processName = f.substr(0, f.length() - 4);
        std::string fullConfigPath = configurationDirectory + "/" + f;

        m_knownVariablesForProcesses[processName]
            = ConfigurationFileParser(m_logger, fullConfigPath).GetVariables();
    }

    m_logger.LogInfo() << "Configuretion loaded";
}

auto MeasurementTraceDaemon::ReadVariables() -> void const
{
    m_logger.LogDebug() << "Rebuilding PID index";

    RebuildProcessIndex();

    m_logger.LogDebug() << "Start reading variables";

    for (const auto& v : m_knownVariablesForProcesses) {
        const auto& processName = v.first;
        const auto& variables = v.second;

        // Find active processes with given name
        auto processIt = m_processNameToPidMapping.find(v.first);
        if (processIt == m_processNameToPidMapping.cend()) {
            m_logger.LogWarn() << "Process `" << processName.c_str() << "` not found";
            continue;
        }

        // Iterate all known PIDs for given process name
        for (const auto& pid : processIt->second) {
            m_logger.LogDebug() << "Reading data from process `" << processName.c_str()
                                << "` with PID " << pid.c_str();
            auto accessor = MemoryAccessorFactory::CreateAccessor(pid, processName);
            for (const auto& variable : variables) {
                DisplayVariable(
                    processName, pid, variable.GetName(), accessor->ReadVariable(variable));
            }
        }
    }

    m_logger.LogDebug() << "Finish reading variables";
}

auto MeasurementTraceDaemon::IterateDirectory(
    const std::string& path, std::function<bool(const std::string&)> filter)
    -> std::vector<std::string>
{
    auto directory = opendir(path.c_str());
    if (!directory) {
        throw MtdException("Cannot open given directory " + path);
    }

    std::vector<std::string> files{};

    struct dirent* entry;
    while ((entry = readdir(directory))) {
        std::string itemName(entry->d_name);
        m_logger.LogVerbose() << "Found entry: " << entry->d_name;
        if (filter) {
            if (filter(itemName)) {
                m_logger.LogVerbose() << "Matched entry: " << entry->d_name;
                files.emplace_back(std::move(itemName));
            }
        } else {
            files.emplace_back(std::move(itemName));
        }
    }

    closedir(directory);

    return files;
}

auto MeasurementTraceDaemon::RebuildProcessIndex() -> void
{
    m_processNameToPidMapping.clear();
    m_logger.LogDebug() << "Dropped old PID mapping";

    std::string procDir = "/proc";
    auto processes = IterateDirectory(
        procDir, [](auto&& s) { return std::all_of(s.cbegin(), s.cend(), isdigit); });

    for (const auto& pid : processes) {
        auto cmdlineFile = procDir + '/' + pid + "/cmdline";

        m_logger.LogVerbose() << "Opening cmdline file: " << cmdlineFile.c_str();

        std::fstream cmdlineFileStream(cmdlineFile);
        std::string processName;
        cmdlineFileStream >> processName;

        // Remove information that stands after the process's name and is divided by `0x00`
        // separator
        processName = processName.substr(0, processName.find('\0'));

        m_logger.LogVerbose() << "Found process `" << processName.c_str() << "` with PID "
                              << pid.c_str();

        if (m_knownVariablesForProcesses.find(processName) != m_knownVariablesForProcesses.cend()) {
            m_logger.LogDebug() << "Adding PID " << pid.c_str() << " to mapping";
            m_processNameToPidMapping[processName].insert(pid);
        }
    }
}

auto MeasurementTraceDaemon::DisplayVariable(
    const std::string& processName,
    const std::string& processPid,
    const std::string& variableName,
    const MemoryAccessorInterface::MemoryChunk& chunk) const -> void
{
    auto logStream = ara::log::LogStream(m_logger, ara::log::LogLevel::kInfo);
    logStream << "Process `" << processName.c_str() << "`, PID " << processPid.c_str()
              << " variable `" << variableName.c_str() << "`, raw value: ";
    for (const auto byte : chunk) {
        // Bytes of the memory chunk are explicitly casted to `size_t` because otherwise they are
        // interpreted as chars, and this malforms the string output
        logStream << static_cast<size_t>(byte) << " ";
    }
}

} // namespace mt
