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

vector<ll> readSeeds() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    string tmp;
    ss >> tmp;
    vector<ll> seeds;
    ll num;
    while (ss >> num) {
        seeds.eb(num);
    }
    return seeds;
}

set<tuple<ll, ll, ll>> readMapping() {
    set<tuple<ll, ll, ll>> mapping;
    ll dest, source, range;
    string line;
    while (getline(cin, line) && line != "") {
        stringstream ss(line);
        ss >> dest >> source >> range;
        mapping.emplace(source, dest, range);
    }
    return mapping;
}

ll doMapping(ll u, set<tuple<ll, ll, ll>> &mapping) {
    auto it = mapping.upper_bound({u + 1, -1, -1});
    if (it == mapping.begin()) return u;
    it--;
    ll source, dest, range;
    tie(source, dest, range) = *it;
    return u < source + range ? u + dest - source : u;
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    auto seeds = readSeeds();

    string line;
    getline(cin, line);

    for (int i = 0; i < 7; ++i) {
        getline(cin, line);
        auto mapping = readMapping();

        for (auto &p: seeds) {
            p = doMapping(p, mapping);
        }
    }

    ll res = 1e18;
    for (auto &p: seeds) res = min(res, p);
    cout << res << "\n";
}
