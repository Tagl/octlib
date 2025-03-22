#include <type_traits>
#include <vector>

#include <nested_vector.h>
using std::vector;
using std::is_same_v;
static_assert(is_same_v<int, nested_vector<int, 0>>);
static_assert(is_same_v<vector<char>, nested_vector<char, 1>>);
static_assert(is_same_v<vector<vector<bool>>, nested_vector<bool, 2>>);
static_assert(is_same_v<vector<vector<vector<long>>>, nested_vector<long, 3>>);
int main() {
    return 0;
};
