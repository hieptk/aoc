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

ll f(vector<ll> &a, bool part1) {
    bool all0 = 1;
    for (ll x: a) if (x) {
        all0 = 0;
        break;
    }
    if (all0) return 0;
    vector<ll> diff;
    for (int i = 0; i + 1 < a.size(); ++i) diff.eb(a[i + 1] - a[i]);
    return part1 ? a.back() + f(diff, 1) : a[0] - f(diff, 0);
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
        stringstream ss(line);
        vector<ll> a;
        ll tmp;
        while (ss >> tmp) a.eb(tmp);
        res += f(a, 1);
        res2 += f(a, 0);
    }
    cout << res << " " << res2 << "\n";
}
