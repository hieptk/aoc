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
 
using ll = long long;
using ld = double;
 
#define eb emplace_back
#define fi first
#define se second
 
using namespace std;

constexpr int nm = 142;

vector<string> a;
int m, n;
map<pair<int, int>, vector<int>> adjmap;

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    string tmp;
    while (getline(cin, tmp)){
        a.push_back(tmp);
    }

    m = a.size();
    n = a[0].size();

    int res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (isdigit(a[i][j])) {
                int j2 = j - 1, cur = 0;
                set<pair<int, int>> adj;
                while (j2 + 1 < n && isdigit(a[i][j2 + 1])) {
                    j2++;
                    cur = cur * 10 + a[i][j2] - '0';
                    for (int ia = i - 1; ia <= i + 1; ++ia) {
                        for (int ja = j2 - 1; ja <= j2 + 1; ++ja) {
                            if (ia >= 0 && ia < m && ja >= 0 && ja < n && a[ia][ja] != '.' && !isdigit(a[ia][ja])) {
                                adj.emplace(ia, ja);
                            }
                        }
                    }
                }
                if (adj.size()) {
                    res += cur;
                    for (auto &p: adj) {
                        if (a[p.fi][p.se] == '*') adjmap[p].eb(cur);
                    }
                }
                j = j2;
            }
        }
    }

    int res2 = 0;
    for (auto &p: adjmap) {
        if (p.se.size() == 2) {
            res2 += p.se[0] * p.se[1];
        }
    }

    cout << res << "\n";
    cout << res2 << "\n";
}
