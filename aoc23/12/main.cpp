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

const int nm = 202;

string s;
vector<int> a;
ll dp[nm][nm][nm];

ll calc(int i, int j, int k) {
    ll &res = dp[i][j][k];
    if (res != -1) return res;
    if (i == s.length()) {
        if (j >= a.size()) return res = (k == 0);
        if (j + 1 == a.size()) {
            return res = (k == a.back());
        }
        return res = 0;
    }
    if (s[i] == '.') {
        if (k) {
            if (j < a.size() && k == a[j]) return res = calc(i + 1, j + 1, 0);        
            else return res = 0;
        } else {
            return res = calc(i + 1, j, 0);
        }
    }
    if (s[i] == '#') {
        return res = calc(i + 1, j, k + 1);
    }
    res = calc(i + 1, j, k + 1);
    if (k) {
        if (j < a.size() && k == a[j]) res += calc(i + 1, j + 1, 0);
    } else {
        res += calc(i + 1, j, 0);
    }
    return res;
}

ll f() {
    memset(dp, -1, sizeof(dp));
    return calc(0, 0, 0);
}

void unfold() {
    string tmp = s;
    for (int i = 0; i < 4; ++i) tmp += "?" + s;
    s = tmp;
    int n = a.size();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < n; ++j) a.eb(a[j]);
    }
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    string line;
    int tmp;
    ll res = 0, res2 = 0;
    while (getline(cin, line)) {
        cout << line << "\n";
        istringstream ss(line);
        ss >> s;
        a.clear();
        while (ss >> tmp) a.eb(tmp);
        res += f();
        unfold();
        res2 += f();
    }
    cout << res << "\n";
    cout << res2 << "\n";
}    
