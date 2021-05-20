#pragma once

namespace mt {

/**
 * @brief Represents functionality of the Measurement and Trace Daemon
 */
class MeasurementTraceDaemon {
public:
    /**
     * @brief Helper class for representing Daemon's exceptions
     */
    class MtdException : public std::runtime_error {
    public:
        template<typename... Args>
        MtdException(Args&&... args)
            : std::runtime_error(std::forward<Args>(args)...)
        {
        }
    };

    /**
     * @brief Constructs an instance of MeasurementTraceDaemon
     *
     * @param configurationDirectory Path to the directory with Daemon's
     * configuration files
     */
    MeasurementTraceDaemon(const std::string& configurationDirectory);

    /**
     * @brief Copy constructor. Explicitly deleted
     */
    MeasurementTraceDaemon(const MeasurementTraceDaemon&) = delete;

    /**
     * @brief Copy assignment operator. Explicitly deleted
     */
    MeasurementTraceDaemon& operator=(const MeasurementTraceDaemon&) = delete;

    /**
     * @brief Move constructor
     *
     * @param rhs RValue reference to an instance of Daemon
     */
    MeasurementTraceDaemon(MeasurementTraceDaemon&& rhs) = default;

    /**
     * @brief Move assignment operator
     *
     * @param rhs RValue reference to an instance of Daemon
     */
    MeasurementTraceDaemon& operator=(MeasurementTraceDaemon&& rhs) = default;

    /**
     * @brief Reads all known variables
     */
    auto ReadVariables() -> void const;

private:
    /**
     * @brief Return a vector of elements in given directory matching predicate
     *
     * @param path Path of directory to inspect
     * @param filter Function to filter directory elements. Might be `nullptr`
     * in case no filtering is needed
     *
     * @return A vector of strings which represent matching elements
     */
    auto IterateDirectory(const std::string& path, std::function<bool(const std::string&)> filter)
        -> std::vector<std::string>;

    /**
     * Matches process names with corresponding PIDs for currently running
     * processes
     *
     * @detail Reads all PID directories in `/proc` directory and obtains
     * process name of those PIDs, then rebuilds internal process index
     */
    auto RebuildProcessIndex() -> void;

    /**
     * @brief Performs action on variable read from target process
     *
     * @param processName Name of the target process
     * @param processPid String representing PID of target process
     * @param variableName String representing name of target process
     * @param chunk Raw bytes representation of the target variable
     */
    auto DisplayVariable(
        const std::string& processName,
        const std::string& processPid,
        const std::string& variableName,
        const MemoryAccessorInterface::MemoryChunk& chunk) const -> void;

    //!< Main logger for the Daemon
    ara::log::Logger& m_logger{ara::log::CreateLogger("MTD", "Measurement and Trace Daemon")};

    //!< Mapping of process names to corresponding PIDs
    std::unordered_map<std::string, std::unordered_set<std::string>> m_processNameToPidMapping;

    //!< Mapping of process names to knows variables for those processes
    std::unordered_map<std::string, std::unordered_set<Variable>> m_knownVariablesForProcesses;
};

} // namespace mt
