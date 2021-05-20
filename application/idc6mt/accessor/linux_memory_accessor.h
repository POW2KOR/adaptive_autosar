#pragma once

#include "memory_accessor.h"

namespace mt {

class LinuxMemoryAccessor : public MemoryAccessorInterface {
public:
    using typename MemoryAccessorInterface::MemoryChunk;

    /**
     * @brief Constructs Linux Memory accessor
     *
     * @param pidString String with PID of target process
     * @param processName String with the name of target process
     */
    LinuxMemoryAccessor(std::string pidString, const std::string& processName);

    /**
     * @brief Copy constructor
     */
    LinuxMemoryAccessor(const LinuxMemoryAccessor&) = default;

    /**
     * @brief Copy assignment operator
     */
    LinuxMemoryAccessor& operator=(const LinuxMemoryAccessor&) = default;

    /**
     * @brief Move constructor
     */
    LinuxMemoryAccessor(LinuxMemoryAccessor&&) = default;

    /**
     * @brief Move assignment operator
     */
    LinuxMemoryAccessor& operator=(LinuxMemoryAccessor&&) = default;

    /**
     * @brief Destructor for Linux Memory accessor
     */
    ~LinuxMemoryAccessor();

    /**
     * @brief Read variable from the observed process
     *
     * @param variable Variable object representing a variable
     *
     * @return A memory chunk read from the observed process
     */
    auto ReadVariable(const Variable& variable) const -> MemoryChunk override;

private:
    /**
     * @brief Calculate appropriate virtual address from the given load address
     *
     * @param elfAddress Address of the variable obtained from the ELF file
     *
     * @return Virtual address for the target variable in current virtual memory space of the
     * target process.
     */
    auto GetVirtualAddress(uintptr_t elfAddress) const -> uintptr_t;

    /**
     * @brief Read memory region from target process address space
     *
     * @param pid PID of the target process
     * @param offset Address in process address space
     * @param length Amount of bytes to read
     *
     * @return A memory chunk read from the observed process
     */
    auto ReadRawMemory(int pid, uintptr_t offset, size_t length) const -> MemoryChunk;

    /**
     * @brief Converts chunk of raw bytes into an address
     *
     * @detail Converts an array of bytes into an address, e.g.
     * [0x12, 0x34, 0x56, 0x78] -> 0x12345678 or 0x78563412, depending on the target's byte order
     *
     * @param chunk Chunk of bytes representing address
     *
     * @return Address value
     */
    auto ChunkToAddress(const MemoryChunk& chunk) const -> uintptr_t;

    //!< Logger for the accessor
    ara::log::Logger& m_logger{ara::log::CreateLogger("LMA", "Linux memory accessor")};

    //!< String representation of target's PID
    std::string m_pidString;

    //!< Memory region start for the target process
    uintptr_t m_memoryRegionStart;
};

} // namespace mt
