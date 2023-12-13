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

bool isReflectionRow(vector<string> &a, int row) {
    for (int i = row, j = row + 1; i >= 0 && j < a.size(); --i, ++j) {
        if (a[i] != a[j]) {
            return 0;
        }
    }
    return 1;
}

set<int> findReflections(vector<string> &a, vector<string> &b) {
    set<int> res;
    int m = a.size(), n = a[0].size();
    for (int i = 0; i + 1 < m; ++i) {
        if (isReflectionRow(a, i)) {
            res.insert(100ll * (i + 1));
        }
    }

    for (int i = 0; i + 1 < n; ++i) {
        if (isReflectionRow(b, i)) {
            res.insert(i + 1);
        }
    }
    return res;
}

void flip(char &x) {
    x = (x =='#' ? '.' : '#');
}

int part2(vector<string> &a, vector<string> &b, set<int> &p) {
    int m = a.size(), n = a[0].size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            flip(a[i][j]);
            flip(b[j][i]);
            auto p2 = findReflections(a, b);
            vector<int> diff;
            set_difference(p2.begin(), p2.end(), p.begin(), p.end(), back_inserter(diff));
            if (diff.size() == 1) return diff[0];
            flip(a[i][j]);
            flip(b[j][i]);
        }
    } 
    return 1e9;    
}

vector<string> rotate(vector<string> &a) {
    vector<string> b(a[0].size());
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) b[j] += a[i][j];
    }
    return b;
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    string line;
    ll res = 0, res2 = 0;
    while (getline(cin, line)) {
        vector<string> a;
        while (line != "") {
            a.eb(line);
            getline(cin, line);
        }
        auto b = rotate(a);

        auto p = findReflections(a, b);
        res += accumulate(p.begin(), p.end(), 0);

        res2 += part2(a, b, p);
    }
    cout << res << "\n";
    cout << res2 << "\n";
}    
