#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <bit>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

#include <constexpr_for.h>
#include <inner_type.h>
#include <vector_dimension.h>
template <typename T>
struct add_t {
    constexpr T operator()(const T a, const T b) const {
        return a + b;
    }
};

template <typename T>
struct sub_t {
    constexpr T operator()(const T a, const T b) const {
        return a - b;
    }
};

template <typename container_t, typename T = inner_type_t<container_t>, typename op_t = add_t<T>, typename inv_t = sub_t<T>, T identity = T{}>
class range_query_t {
    constexpr static auto num_dimensions = vector_dimension_v<container_t>;
    static_assert(num_dimensions >= 1ull, "Range query type must have at least 1 dimension.");
    container_t data;
    constexpr static op_t op{};
    constexpr static inv_t inv{};
    static_assert(op(identity, identity) == identity, "Applying operation on two identities does not result in identity.");
    static_assert(inv(identity, identity) == identity, "Applying inverse operation on two identities does not result in identity.");

    constexpr static T apply_op(const T& a, const T& b) {
        return op(a, b);
    }

    template<typename S>
    constexpr static std::vector<S> apply_op(const std::vector<S>& a, const std::vector<S>& b) {
        assert(a.size() == b.size());
        std::vector<S> result;
        result.reserve(a.size());
        for (std::size_t i = 0; i < a.size(); i++) {
            result.push_back(apply_op(a[i], b[i]));
        }
        return result;
    }

    constexpr static std::vector<T> make_identity(const std::vector<T>& source) {
        return std::vector<T>(source.size() + 1, identity);
    }

    template <typename S>
    constexpr static std::vector<S> make_identity(const std::vector<S>& source) {
        return std::vector<S>(source.size() + 1, make_identity(source[0]));
    }
    
    constexpr static std::vector<T> compute_prefix(const std::vector<T>& source) {
        std::vector<T> dest;
        dest.reserve(source.size() + 1);
        dest.push_back(identity);
        for (const auto& val : source) {
            dest.push_back(dest.back());
            dest.back() = apply_op(dest.back(), val);
        }
        return dest;
    }

    template <typename S>
    constexpr static std::vector<S> compute_prefix(const std::vector<S>& source) {
        std::vector<S> dest = make_identity(source);
        for (std::size_t i = 0; i < source.size(); i++) {
            dest[i+1] = apply_op(compute_prefix(source[i]), dest[i]);
        }
        return dest;
    }

    constexpr static T at(const T& v, [[maybe_unused]] const std::array<size_t, num_dimensions>& indices, [[maybe_unused]]  const std::size_t counter = 0) {
        return v;
    }

    template<typename S>
    constexpr static T at(const std::vector<S>& v, const std::array<size_t, num_dimensions>& indices, const std::size_t counter = 0) {
        return at(v[indices[counter]], indices, counter + 1);
    }
    
public:
    range_query_t(const container_t& arr) {
        data = compute_prefix(arr);
    }

    constexpr T operator()(const std::array<std::size_t, num_dimensions>& lower, const std::array<std::size_t, num_dimensions>& upper) const {
        constexpr std::size_t limit{ 1ull << num_dimensions };
        T result{ identity };
        bool is_empty = false;
        constexpr_for<0ul, num_dimensions, 1ul>([&lower, &upper, &is_empty](auto j){
            if (lower[j] > upper[j]) {
                is_empty = true;
            }
        });
        if (is_empty) {
            return identity;
        }
        constexpr_for_bucketed<0ul, limit, 1ul, 512ul>([&lower, &upper, &result, this](auto i){
            constexpr std::size_t parity{ (num_dimensions - std::popcount<size_t>(i)) % 2 };
            std::array<size_t, num_dimensions> indices{};
            constexpr_for<0ul, num_dimensions, 1ul>([&indices, &upper, &lower, i](auto j){
                indices[j] = ((1ull << j) & i) ? upper[j] + 1 : lower[j];
            });
            result = parity ? inv(result, at(data, indices)) : op(result, at(data, indices));
        });
        return result;
    }
};
