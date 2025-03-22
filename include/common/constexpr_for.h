#pragma once
#include <type_traits>

template <auto Start, auto End, auto Inc, class F>
constexpr void constexpr_for(F&& f)
{
    if constexpr (Start < End)
    {
        f(std::integral_constant<decltype(Start), Start>());
        constexpr_for<Start + Inc, End, Inc>(f);
    }
}

// The purpose of this is to prevent deep template recursion for larger for loops
template <auto Start, auto End, auto Inc, auto BucketSize, class F>
constexpr void constexpr_for_bucketed(F&& f)
{
    if constexpr (Start + BucketSize * Inc < End)
    {
        constexpr_for<Start, Start + BucketSize * Inc, Inc>(f);
        constexpr_for_bucketed<Start + BucketSize * Inc, End, Inc, BucketSize>(f);
    }
    else if constexpr (Start < End) {
        constexpr_for<Start, End, Inc>(f);
    }
}
