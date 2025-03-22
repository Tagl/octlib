#include <array>
#include <iostream>
#include <vector>

#include <static_range_query.h>

using namespace std;
using int_t = int64_t;

// Field testing on: https://open.kattis.com/problems/rust

int main() {
    int_t n, k;
    cin >> n >> k;
    vector<string> grid(n);
    vector<vector<int_t>> values(n, vector<int_t>(n, 0));
    vector<vector<int_t>> walls(n, vector<int_t>(n, 0));
    for (auto& row : grid) {
        cin >> row;
    }

    for (int_t i = 0; i < n; i++) {
        for (int_t j = 0; j < n; j++) {
            if (grid[i][j] == '#') {
                walls[i][j] = 1;
            }
            else if (grid[i][j] != '.') {
                walls[i][j] = 1;
                values[i][j] = grid[i][j] - '0';
            }
        }
    }

    range_query_t values_range{ values };
    range_query_t walls_range{ walls };

    int_t best = 0;
    for (size_t i = 0; i < n - k + 1; i++) {
        for (size_t j = 0; j < n - k + 1; j++) {
            if (walls_range({i, j}, {i+k-1, j+k-1}) - walls_range({i+1, j+1}, {i+k-2, j+k-2})  == 0) {
                best = max(best, values_range({i+1, j+1}, {i+k-2, j+k-2}));
            }
        }
    }
    cout << best << endl;
    
    return 0;
}
