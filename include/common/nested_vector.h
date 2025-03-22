#pragma once
#include <array>
#include <vector>

template <typename T, std::size_t Dims>
struct nested_vector_impl;

template <typename T, std::size_t Dims>
struct nested_vector_impl
{
    using type = std::vector<typename nested_vector_impl<T, Dims - 1>::type>;
};

template <typename T>
struct nested_vector_impl<T, 0ul>
{
    using type = T;
};

template <typename T, std::size_t Dims>
using nested_vector = typename nested_vector_impl<T, Dims>::type;

template <typename T, std::size_t Dims, std::size_t Sz = Dims>
constexpr nested_vector<T, Dims> make_nested_vector(const std::array<size_t, Sz> &sizes, const std::size_t ind = 0)
{
    if constexpr (Dims > 0)
    {
        return nested_vector<T, Dims>(sizes[ind], make_nested_vector<T, Dims - 1, Sz>(sizes, ind + 1));
    }
    if constexpr (Dims == 0) {
        return {};
    }
}

template<typename T, size_t Dims, size_t Sz = Dims>
constexpr T& nested_element_at(nested_vector<T, Dims>& v, const std::array<size_t, Sz>& indices, const std::size_t ind = 0) {
    if constexpr (Dims > 0) {
        return nested_element_at<T, Dims-1, Sz>(v[indices[ind]], indices, ind+1);
    }
    if constexpr (Dims == 0) {
        return v;
    }
}
