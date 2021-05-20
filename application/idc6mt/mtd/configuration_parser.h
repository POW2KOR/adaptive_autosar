#pragma once

namespace mt {

/**
 * @brief Configuration file parser for the Measurement and Trace Daemon
 */
class ConfigurationFileParser {
public:
    /**
     * @brief Constructs an instance of a parser
     *
     * @param logger Logger to report
     * @param configurationPath Path to a configuration file
     */
    ConfigurationFileParser(ara::log::Logger& logger, const std::string& configurationPath);

    /**
     * @brief Getter for parsed variables
     *
     * @detail Lvalue overload
     *
     * @return Hashset of variables described in given configuration file
     */
    auto GetVariables() & -> const std::unordered_set<Variable>&;

    /**
     * @brief Getter for parsed variables
     *
     * @detail Rvalue overload
     *
     * @return Hashset of variables described in given configuration file
     */
    auto GetVariables() && -> std::unordered_set<Variable>;

private:
    /**
     * Parses configuration file and splits it into sections
     *
     * @param configPath Path to the configuration file
     *
     * @return
     */
    auto ParseSections(const std::string& configPath)
        -> std::unordered_map<std::string, std::string>;

    /**
     * @brief Parse a config file section
     *
     * @param name A string which represents name of the section
     * @param data A string which represents a config section data
     *
     * @return A Variable created from the given config file entry
     */
    auto ParseVariableSection(const std::string& name, const std::string& data) const -> Variable;

    //!< Internal storage for the variablea
    std::unordered_set<Variable> m_variables;
};

} // namespace mt
