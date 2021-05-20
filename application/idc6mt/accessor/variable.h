#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace mt {

/**
 * @Brief This class contains all the information regarding a variable under
 * observation.
 */
class Variable {
public:
    /**
     * @brief Creates a `Variable` instance
     *
     * @param baseAddress address Load address of the variable
     * @param dataSize Length of the variable in bytes
     * @param offsets Offset vector of the variable
     */
    Variable(std::string name, uintptr_t address, size_t dataSize, std::vector<uintptr_t> offsets)
        : m_name(std::move(name))
        , m_address(address)
        , m_size(dataSize)
        , m_offsets(std::move(offsets))
    {
    }

    /**
     * @brief Getter for the name of the variable
     *
     * @return Name of the variable
     */
    auto GetName() const -> const std::string&
    {
        return m_name;
    }

    /**
     * @brief Getter for the load address
     *
     * @return Load address of the variable
     */
    auto GetLoadAddress() const -> uintptr_t
    {
        return m_address;
    }

    /**
     * @brief Getter for the size of the variable
     *
     * @return Size of the variable in bytes
     */
    auto GetSize() const -> size_t
    {
        return m_size;
    }

    /**
     * @brief Getter for the offset vector
     *
     * @return Offset vector of the variable
     */
    auto GetOffsets() const -> const std::vector<uintptr_t>&
    {
        return m_offsets;
    }

    auto operator==(const Variable& rhs) const noexcept -> bool
    {
        return m_name == rhs.GetName();
    }

private:
    //!< Name of the variable
    std::string m_name;

    //!< Load address of the variable
    uintptr_t m_address;

    //!< Size of the variable in bytes
    size_t m_size;

    //!< Offset list for the variable
    std::vector<uintptr_t> m_offsets;
};

} // namespace mt

// Extend std namespace in order to use `Variable` with associative containers
namespace std {
template<>
struct hash<mt::Variable> {
    std::size_t operator()(const mt::Variable& v) const
    {
        return std::hash<std::string>()(v.GetName());
    }
};
} // namespace std
