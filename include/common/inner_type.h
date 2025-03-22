#pragma once
#include <vector>

template <typename T>
struct inner_type
{
    using type = T;
};

template <typename T>
struct inner_type<std::vector<T>>
{
    using type = typename inner_type<T>::type;
};

template<class T>
using inner_type_t = typename inner_type<T>::type;
