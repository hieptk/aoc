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

// up, right, down, left
const int x[] = {-1, 0, 1, 0};
const int y[] = {0, 1, 0, -1};
const int nm = 300;

vector<string> a;
int m, n;
bool energized[nm][nm];
bool visited[nm][nm][4];

void move(int i, int j, int dir) {
    if (i < 0 || i >= m || j < 0 || j >= n) return;
    if (visited[i][j][dir]) return;
    visited[i][j][dir] = energized[i][j] = 1;
    switch (a[i][j]) {
        case '.':
            move(i + x[dir], j + y[dir], dir);
            break;
        case '/':
            dir ^= 1;
            move(i + x[dir], j + y[dir], dir);
            break;
         case '\\':
            dir ^= 3;
            move(i + x[dir], j + y[dir], dir);
            break;
        case '|':
            if (dir == 0 || dir == 2) move(i + x[dir], j + y[dir], dir);
            else {
                move(i + x[0], j + y[0], 0);
                move(i + x[2], j + y[2], 2);
            }
            break;
        case '-':
            if (dir == 1 || dir == 3) move(i + x[dir], j + y[dir], dir);
            else {
                move(i + x[1], j + y[1], 1);
                move(i + x[3], j + y[3], 3);
            }
            break;
    }
}

int check(int u, int v, int dir) {
    memset(visited, 0, sizeof(visited));
    memset(energized, 0, sizeof(energized));
    move(u, v, dir);
    int res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) res += energized[i][j];
    }
    return res;
}

int main() {
    #ifdef LOCAL
    freopen("input2.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    string line;
    while (getline(cin, line)) {
        a.eb(line);
    }
    m = a.size();
    n = a[0].size();
    
    cout << check(0, 0, 1) << "\n";

    int res = 0;
    for (int i = 0; i < m; ++i) {
        res = max(res, check(i, 0, 1));
        res = max(res, check(i, n - 1, 3));
    }
    for (int j = 0; j < n; ++j) {
        res = max(res, check(0, j, 2));
        res = max(res, check(m - 1, 0, 0));
    }
    cout << res << "\n";
}    