#include <algorithm>
#include <cstdint>
#include <fstream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>
#include <fcntl.h>
#include <sys/ptrace.h>
#include <sys/uio.h>
#include <unistd.h>

#include "ara/log/logging.h"

#include "application/idc6mt/accessor/variable.h"
#include "linux_memory_accessor.h"

namespace mt {

LinuxMemoryAccessor::LinuxMemoryAccessor(std::string pidString, const std::string& processName)
    : m_pidString(std::move(pidString))
{
    if (!std::all_of(m_pidString.cbegin(), m_pidString.cend(), isdigit)) {
        throw std::runtime_error("Given PID string " + m_pidString + " is not numeric");
    }

    std::string mapsPath = "/proc/" + m_pidString + "/maps";
    m_logger.LogDebug() << "Opening memory mapping file: " << mapsPath.c_str();

    // Match address range and filename
    // Maps file is a set of lines like this:
    // `55dbad57f000-55dbad642000 r-xp 00000000 fd:01 41943204                   /bin/zsh`
    // The first two numbers represent memory region address range for the process, also we need
    // the `r` flag to make sure this region is readable. This regular expression captures both
    // start and end addresses if a more sophisticated calculation is requires.
    std::regex addressRegex(R"(^([0-9a-f]+)-([0-9a-f]+) [-r].*$)");

    // Iterate `maps` file line by line until a readable region is found
    // This file typically has lots of lines that match this pattern, but we need only the first
    // one because it contains the lowest addressable range, which gives us the start address.
    std::ifstream mapsFile(mapsPath);
    for (std::string line; getline(mapsFile, line);) {
        m_logger.LogVerbose() << "Line read: " << line.c_str();
        std::smatch groups;
        if (std::regex_match(line, groups, addressRegex)) {
            // Groups 1 and 2 represent address range. We need the start address
            m_memoryRegionStart = std::stoull(groups[1], 0, 16);
            break;
        }
    }
}

LinuxMemoryAccessor::~LinuxMemoryAccessor() = default;

auto LinuxMemoryAccessor::ReadVariable(const Variable& variable) const
    -> LinuxMemoryAccessor::MemoryChunk
{
    int pid = std::stoi(m_pidString);
    auto address = GetVirtualAddress(variable.GetLoadAddress());

    // In case of indirect access (e.g. via a pointer), it is required to not read the requested
    // amount of bytes, but to get an address stored in this pointer itself. So, all the addresses
    // and offsets except the last one are interpreted as an address of a pointer, so the desired
    // read length is equivalent to a pointer size for the target platform.
    auto& offsets = variable.GetOffsets();
    for (size_t i = 0; i < offsets.size() - 1; ++i) {
        address = ChunkToAddress(ReadRawMemory(pid, address + offsets[i], sizeof(void*)));
    }

    // The last address and the corresponding last offset stand for the target variable, so now
    // the required amount of bytes is read.
    return ReadRawMemory(pid, address + offsets.back(), variable.GetSize());
}

auto LinuxMemoryAccessor::GetVirtualAddress(uintptr_t elfAddress) const -> uintptr_t
{
    uintptr_t virtualAddrValue = m_memoryRegionStart + elfAddress;

    m_logger.LogVerbose() << "PID " << m_pidString.c_str() << ": load address " << elfAddress
                          << " -> virtual address " << virtualAddrValue;

    return virtualAddrValue;
}

auto LinuxMemoryAccessor::ReadRawMemory(int pid, uintptr_t offset, size_t length) const -> MemoryChunk
{
    MemoryChunk buffer;
    buffer.reserve(length);

    struct iovec local {
        buffer.data(), length
    };
    struct iovec remote {
        reinterpret_cast<void*>(offset), length
    };

    auto rc = process_vm_readv(pid, &local, 1, &remote, 1, 0);
    if (rc < 0) {
        m_logger.LogWarn() << "Unable to read memory from the target process: " << errno;
    }

    return buffer;
}

auto LinuxMemoryAccessor::ChunkToAddress(const MemoryChunk& chunk) const -> uintptr_t
{
    uintptr_t result = 0;
    // If a 32-bit system is used, it is needed to make sure that the given chunk contains no more
    // than 4 bytes, for a 64-bit system no more than 8. `void*` is used because we are not
    // interested in the concrete type, we only need to know pointer size for the target platform.
    if (chunk.size() > sizeof(void*)) {
        m_logger.LogError() << "Cannot transform byte sequence into address";
    } else {
        memcpy(&result, chunk.data(), chunk.size());
    }
    return result;
}

} // namespace mt
