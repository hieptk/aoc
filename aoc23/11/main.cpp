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

vector<string> a;

vector<pair<ll, ll>> expand(vector<string> &a, int expansion) {
    int m = a.size(), n = a[0].size();
    vector<bool> expand_col(n);
    for (int i = 0; i < n; ++i) {
        bool alldot = 1;
        for (int j = 0; j < m; ++j) {
            if (a[j][i] != '.') {
                alldot = 0;
                break;
            }
        }
        expand_col[i] = alldot;
    }

    vector<pair<ll, ll>> res;
    ll cntrow = 0;
    for (int i = 0; i < m; ++i) {
        int cntcol = 0;
        bool alldot = 1;
        for (int j = 0; j < n; ++j) {
            if (a[i][j] != '.') {
                res.eb(cntrow, cntcol);
                alldot = 0;
            }
            if (expand_col[j]) cntcol += expansion;
            else cntcol++;
        }
        if (alldot) cntrow += expansion;
        else cntrow++;
    }

    return res;
}

ll getTotalDist(vector<pair<ll, ll>> pos) {
    ll res = 0;
    for (int i = 0; i  + 1 < pos.size(); ++i) {
        for (int j = i + 1; j < pos.size(); ++j) {
            res += abs(pos[i].fi - pos[j].fi) + abs(pos[i].se - pos[j].se);
        }
    }
    return res;
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
    
    cout << getTotalDist(expand(a, 2)) << "\n";
    cout << getTotalDist(expand(a, 1000000)) << "\n";
}    
