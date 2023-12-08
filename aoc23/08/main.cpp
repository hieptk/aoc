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

string s;
map<pair<string, char>, string> adj;

int f(string cur) {
    int res = 0;
    while (cur != "ZZZ") {
        cur = adj[{cur, s[res % s.length()]}];
        res++;
    }
    return res;
}

int f2(string cur) {
    int res = 0;
    while (cur.back() != 'Z') {
        cur = adj[{cur, s[res % s.length()]}];
        res++;
    }
    return res;
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> s;
    string node;
    string tmp, tmp2;

    vector<string> q;
    while (cin >> node) {
        cin >> tmp >> tmp >> tmp2;
        adj[{node, 'L'}] = tmp.substr(1, 3);
        adj[{node, 'R'}] = tmp2.substr(0, 3);
        if (node.back() == 'A') {
            q.eb(node);
        }
    }

    cout << f("AAA") << "\n";

    ll res = 0;
    for (auto &p: q) {
        ll tmp = f2(p);
        res = (res == 0 ? tmp : res / gcd(res, tmp) * tmp);
    }
    cout << res << "\n";
}
