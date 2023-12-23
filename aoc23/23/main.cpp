#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <cstring>
#include <unordered_map>
#include <iomanip>
#include <queue>
#include <numeric>
#include <map>
#include <sstream>
#include <cassert>
 
using ll = long long;
using ld = double;
 
#define eb emplace_back
#define fi first
#define se second

using namespace std;

constexpr int nm = 300;
constexpr int x[] = {-1, 0, 1, 0};
constexpr int y[] = {0, 1, 0, -1};
constexpr bool part1 = 0;

vector<string> a;
int m, n;
bool vs[nm][nm];
int pathCnt;

int calc(int i, int j) {
    if (i == m - 1) {
        pathCnt++;
        return 0;
    }
    vs[i][j] = 1;
    int res = -1e9;
    if (part1 && a[i][j] != '.') {
        if (a[i][j] == '^' && !vs[i - 1][j]) res = calc(i - 1, j) + 1;
        else if (a[i][j] == 'v' && !vs[i + 1][j]) res = calc(i + 1, j) + 1;
        else if (a[i][j] == '<' && !vs[i][j - 1]) res = calc(i, j - 1) + 1;
        else if (a[i][j] == '>' && !vs[i][j + 1]) res = calc(i, j + 1) + 1;
    } else {
        for (int k = 0; k < 4; ++k) {
            int i2 = i + x[k], j2 = j + y[k];
            if (i2 >= 0 && a[i2][j2] != '#' && !vs[i2][j2]) {
                res = max(res, calc(i2, j2) + 1);
            }
        }
    }
    vs[i][j] = 0;
    return res;
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    auto begin = clock();
    ios::sync_with_stdio(0);
    cin.tie(0);
    string line;
    while (getline(cin, line)) {
        a.eb(line);
    }
    m = a.size();
    n = a[0].size();

    cout << calc(0, 1) << "\n";
    cout << "Time: " << (double) (clock() - begin) / CLOCKS_PER_SEC << "\n";
    cout << "Number of paths: " << pathCnt << "\n";
}    