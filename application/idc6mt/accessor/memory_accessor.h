#pragma once

namespace mt {

/**
 * @brief Interface for the memory accessors
 */
class MemoryAccessorInterface {
public:
    using MemoryChunk = std::vector<uint8_t>;

    /**
     * @brief Read variable from the observer process
     *
     * @param variable Variable object representing a variable
     *
     * @return A memory chunk read from the observed process
     */
    virtual auto ReadVariable(const Variable& variable) const -> MemoryChunk = 0;
};

} // namespace mt
