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

vector<string> a;
int m, n;
int s, t;
int d[nm][nm];

vector<pair<int, int>> neighbors(int i, int j) {
    switch (a[i][j]) {
        case '|':
            return {{i - 1, j}, {i + 1, j}};
        case '-':
            return {{i, j - 1}, {i, j + 1}};
        case 'L':
            return {{i - 1, j}, {i, j + 1}};
        case 'J':
            return {{i - 1, j}, {i, j- 1}};
        case '7':
            return {{i + 1, j}, {i, j - 1}};
        case 'F':
            return {{i + 1, j}, {i, j + 1}};
        default:
            throw exception();
    }
}

bool isPipe(int i, int j) {
    return i >= 0 && i < m && j >= 0 && j < n && a[i][j] != '.';
}

void part1() {
    queue<pair<int, int>> q;
    q.emplace(s, t);
    memset(d, 0x3f, sizeof(d));
    d[s][t] = 0;
    int res = 0;
    while (!q.empty()) {
        int i = q.front().fi;
        int j = q.front().se;
        q.pop();
        res = max(res, d[i][j]);
        for (auto &p: neighbors(i, j)) {
            if (isPipe(p.fi, p.se) && d[p.fi][p.se] > d[i][j] + 1) {
                d[p.fi][p.se] = d[i][j] + 1;
                q.emplace(p);
            }
        }
    }
    cout << res << "\n";
}

void part2() {
    int res = 0;
    for (int i = 0; i < m; ++i) {
        int prev = 0;
        for (int j = 0; j < n; ++j) {
            res += (d[i][j] > 1e9 && (prev % 2));
            prev += d[i][j] < 1e9 && (a[i][j] == '|' || a[i][j] == 'J' || a[i][j] == 'L');
        }
    }
    cout << res << "\n";
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    string line;
    while (getline(cin, line)) {
        a.eb(line);
    }

    m = a.size();
    n = a[0].size();
    s = t = -1;
    for (int i = 0; i < m && s == -1; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 'S') {
                s = i;
                t = j;
                a[i][j] = '-';
                break;
            }
        }
    }

    part1();
    part2();
}
