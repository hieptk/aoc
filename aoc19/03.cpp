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
#include <map>
#include <sstream>
#include <stack>
#include <bitset>
 
using ll = long long;   
using ld = long double;
 
using namespace std;

map<char, pair<int, int>> dirs = {
    {'U', {0, 1}},
    {'D', {0, -1}},
    {'L', {-1, 0}},
    {'R', {1, 0}}
};

map<pair<ll, ll>, ll> toPoints(string &line) {
    string token;
    stringstream ss(line);
    map<pair<ll, ll>, ll> res;
    ll x = 0, y = 0, n = 0;
    while (getline(ss, token, ',')) {
        char dir = token[0];
        auto [dx, dy] = dirs[dir];
        int steps = stoi(token.substr(1));
        for (int i = 0; i < steps; ++i) {
            n++;
            x += dx;
            y += dy;
            if (!res.count({x, y})) res[{x, y}] = n;
        }
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    string line, line2;
    getline(cin, line);
    getline(cin, line2);

    auto s1 = toPoints(line), s2 = toPoints(line2);
    ll res = 9e18, res2 = 9e18;
    for (auto &[p, n]: s1) {
        if (p != make_pair(0, 0) && s2.count(p)) {
            res = min(res, abs(p.first) + abs(p.second));
            res2 = min(res2, n + s2[p]);
        }
    }
    cout << res << "\n";
    cout << res2 << "\n";
}
