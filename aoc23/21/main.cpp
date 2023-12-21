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

const int x[] = {-1, 0, 1, 0};
const int y[] = {0, 1, 0, -1};
const int maxSteps = 64;

vector<string> a;
int m, n;
int s, t;
queue<tuple<int, int, int>> q;
set<tuple<int, int, int>> vs;

void findS() {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 'S') {
                s = i;
                t = j;
                a[i][j] = '.';
                break;
            }
        }
    }
}

int bfs() {
    q.emplace(0, s, t);
    int res = 0;

    while (!q.empty()) {
        int step, i, j;
        tie(step, i, j) = q.front();
        q.pop();
        
        for (int k = 0; k < 4; ++k) {
            int i2 = i + x[k], j2 = j + y[k];
            int i3 = (i2 % m + m) % m, j3 = (j2 % n + n) % n;
            if (a[i3][j3] == '.' && !vs.count({step + 1, i2, j2})) {
                vs.emplace(step + 1, i2, j2);
                if (step + 1 == maxSteps) res++;
                else q.emplace(step + 1, i2, j2);
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
    findS();
    cout << bfs() << "\n";

    // cnt[x], cnt[x + m], cnt[x + 2*m], ... form a quadratic function
    // cnt[65], cnt[196], cnt[327], ..., cnt[26501365]
    ll A = 14584, B = -14498, C = 3617;
    ll x = (26501365 - 65) / 131 + 1;
    cout << A * x * x + B * x + C << "\n";
}    