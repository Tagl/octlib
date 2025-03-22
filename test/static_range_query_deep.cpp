#include <array>
#include <iostream>
#include <utility>
#include <vector>

#include <nested_vector.h>
#include <static_range_query.h>

using namespace std;
using int_t = int64_t;



template<size_t Dims>
constexpr void solve() {
    array<size_t, Dims> sizes{};

    constexpr_for<0ul, Dims, 1ul>([&sizes](auto i)
                                  { cin >> sizes[i]; });

    auto arr{make_nested_vector<int_t, Dims>(sizes)};

    int_t m;
    cin >> m;
    array<size_t, Dims> indices{};
    for (int_t i = 0; i < m; i++) {
        constexpr_for<0ul, Dims, 1ul>([&indices](auto i)
                                      { cin >> indices[i]; });
        int_t val;
        cin >> val;
        nested_element_at<int_t, Dims, Dims>(arr, indices) = val;
    }

    range_query_t range_query{arr};

    int_t q;
    cin >> q;
    for (int_t i = 0; i < q; i++)
    {
        array<size_t, Dims> indices_lower{}, indices_upper{};
        constexpr_for<0ul, Dims, 1ul>([&indices_lower](auto i)
                                      { cin >> indices_lower[i]; });
        constexpr_for<0ul, Dims, 1ul>([&indices_upper](auto i)
                                      { cin >> indices_upper[i]; });
        
        cout << range_query(indices_lower, indices_upper) << endl;
    }
}

int main()
{
    size_t dims;
    cin >> dims;
    switch (dims) {
        case 1ul:
            solve<1ul>();
            break;
        case 2ul:
            solve<2ul>();
            break;
        case 3ul:
            solve<3ul>();
            break;
        case 4ul:
            solve<4ul>();
            break;
        case 5ul:
            solve<5ul>();
            break;
        case 6ul:
            solve<6ul>();
            break;
        case 7ul:
            solve<7ul>();
            break;
        case 8ul:
            solve<8ul>();
            break;
        case 9ul:
            solve<9ul>();
            break;
        case 10ul:
            solve<10ul>();
            break;
        default:
            __builtin_unreachable();
            break;
    }

    return 0;
}
