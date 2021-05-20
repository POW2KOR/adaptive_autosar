#pragma once

#ifdef __linux__
#include "linux_memory_accessor.h"
#else
#error "No accessors defined"
#endif

namespace mt {

/**
 * @brief Fabric class for creating memory accessors
 */
class MemoryAccessorFactory {
public:
    /**
     * @brief Creates an accessor instance for current platform
     *
     * @param args Parameter pack for the corresponding constructor
     *
     * @return Unique pointer to the created accessor
     */
    template<typename... Args>
    static auto CreateAccessor(Args&&... args) -> std::unique_ptr<MemoryAccessorInterface>
    {
#ifdef __linux__
        static_assert(std::is_constructible<LinuxMemoryAccessor, Args...>::value);
        return std::make_unique<LinuxMemoryAccessor>(std::forward<Args>(args)...);
#else
#error "No accessors defined"
#endif
    }
};

} // namespace mt
