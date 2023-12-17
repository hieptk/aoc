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

const int nm = 300;
// up, right, down, left
const int x[] = {-1, 0, 1, 0};
const int y[] = {0, 1, 0, -1};
const int inf = 1e9;

vector<string> a;
int m, n;
int d[nm][nm][4][12];

int dijkstra(int minStraight, int maxStraight) {
    memset(d, 0x3f, sizeof(d));
    priority_queue<tuple<int, int, int, int, int>> q;
    for (int i = 0; i < 4; ++i) {
        q.emplace(0, 0, 0, i, 0);
        d[0][0][i][0] = 0;
    }

    int res = inf;
    while (!q.empty()) {
        int d0, i, j, dir, straight;
        tie(d0, i, j, dir, straight) = q.top();
        d0 = -d0;
        q.pop();
        if (d0 != d[i][j][dir][straight]) continue;
        if (i == m - 1 && j == n - 1 && straight >= minStraight) {
            res = min(res, d0);
            continue;
        }
        for (int d2 = 0; d2 < 4; ++d2) {
            if (abs(dir - d2) == 2) continue;
            int i2 = i + x[d2], j2 = j + y[d2];
            if (i2 >= 0 && i2 < m && j2 >= 0 && j2 < n) {
                int s2 = d2 == dir ? straight + 1 : 1;
                if (s2 <= maxStraight && (d2 == dir || straight >= minStraight)) {
                    if (d[i2][j2][d2][s2] > d0 + a[i2][j2] - '0') {
                        d[i2][j2][d2][s2] = d0 + a[i2][j2] - '0';
                        q.emplace(-d[i2][j2][d2][s2], i2, j2, d2, s2);
                    }
                }
            }
        }
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

    cout << dijkstra(0, 3) << "\n";
    cout << dijkstra(4, 10) << "\n";
}    