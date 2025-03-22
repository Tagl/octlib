#include <vector>
#include <vector_dimension.h>
using std::vector;
using dim_0 = int;
using dim_1 = vector<dim_0>;
using dim_2 = vector<dim_1>;
using dim_3 = vector<dim_2>;
using dim_4 = vector<dim_3>;
using dim_5 = vector<dim_4>;
using dim_6 = vector<dim_5>;
using dim_7 = vector<dim_6>;
using dim_8 = vector<dim_7>;
using dim_9 = vector<dim_8>;
using dim_10 = vector<dim_9>;
static_assert(vector_dimension_v<dim_0> == 0);
static_assert(vector_dimension_v<dim_1> == 1);
static_assert(vector_dimension_v<dim_2> == 2);
static_assert(vector_dimension_v<dim_3> == 3);
static_assert(vector_dimension_v<dim_4> == 4);
static_assert(vector_dimension_v<dim_5> == 5);
static_assert(vector_dimension_v<dim_6> == 6);
static_assert(vector_dimension_v<dim_7> == 7);
static_assert(vector_dimension_v<dim_8> == 8);
static_assert(vector_dimension_v<dim_9> == 9);
static_assert(vector_dimension_v<dim_10> == 10);

int main() {
    return 0;
};
