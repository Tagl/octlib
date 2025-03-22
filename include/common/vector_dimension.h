#pragma once
#include <type_traits>
#include <vector>

template <std::size_t Count, typename T>
struct vector_dimension_impl
  : std::integral_constant<std::size_t, Count> {};

template <std::size_t Count, typename T, typename Allocator>
struct vector_dimension_impl<Count, std::vector<T, Allocator>>
  : vector_dimension_impl<Count + 1u, T> {};

template <typename T>
struct vector_dimension : vector_dimension_impl<0u, T> {};

template <typename T>
inline constexpr auto vector_dimension_v = vector_dimension<T>::value;
