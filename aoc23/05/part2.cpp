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

set<pair<ll, ll>> readSeeds() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    string tmp;
    ss >> tmp;
    set<pair<ll, ll>> seeds;
    ll begin, range;
    while (ss >> begin >> range) {
        seeds.emplace(begin, begin + range - 1);
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

void doMapping(ll &u, ll v, ll source, ll dest, ll range, set<pair<ll, ll>> &newSeeds) {
    ll u2 = max(u, source);
    ll v2 = min(v, source + range - 1);
    if (u2 > u) {
        newSeeds.emplace(u, source - 1);
    }
    if (u2 <= v2) {
        newSeeds.emplace(u2 + dest - source, v2 + dest - source);
    }
    
    u = v2 + 1;
}

void doAllMappings(ll u, ll v, set<tuple<ll, ll, ll>> &mapping, set<pair<ll, ll>> &newSeeds) {
    auto it = mapping.upper_bound({u + 1, -1, -1});
    if (it != mapping.begin()) {
        it--;
    }

    while (it != mapping.end()) {
        ll source, dest, range;
        tie(source, dest, range) = *it;
        if (source > v) break;

        doMapping(u, v, source, dest, range, newSeeds);
        ++it;
    }

    if (u < v) {
        newSeeds.emplace(u + 1, v);
    }
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

        set<pair<ll, ll>> newSeeds;
        for (auto &p: seeds) {
            doAllMappings(p.fi, p.se, mapping, newSeeds);
        }
        seeds = newSeeds;
    }

    ll res = 1e18;
    for (auto &p: seeds) res = min(res, p.fi);
    cout << res << "\n";
}
