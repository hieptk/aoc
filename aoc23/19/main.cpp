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

struct Rule {
    char var;
    bool smaller;
    ll val;
    string forward;
};

map<string, vector<Rule>> a;

vector<Rule> parseRule(istringstream &ss) {
    string s;
    vector<Rule> res;
    while (ss >> s) {
        Rule rule;
        auto i = s.find(':');
        if (i == string::npos) {
            rule.var = '*';
            rule.forward = s;
            res.eb(rule);
            return res;
        }
        rule.var = s[0];
        rule.smaller = s[1] == '<';
        rule.val = stoll(s.substr(2, i - 2));
        rule.forward = s.substr(i + 1);
        res.eb(rule);
    }
    return res;
}

bool check(map<char, ll> &vals, Rule &r) {
    if (r.var == '*') return 1;
    if (r.smaller) {
        return vals[r.var] < r.val;
    } else {
        return vals[r.var] > r.val;
    }
}

string check(map<char, ll> &vals, vector<Rule> &rules) {
    for (Rule &r: rules) {
        if (check(vals, r)) return r.forward;
    }
    return "?";
}

bool check(map<char, ll> &vals) {
    string name = "in";
    while (1) {
        string tmp = check(vals, a[name]);
        if (tmp == "A") return 1;
        if (tmp == "R") return 0;
        name = tmp;
    }
    return 0;
}

bool updateBounds(map<char, pair<ll, ll>> &bounds, Rule &r) {
    if (r.var == '*') return 1;
    if (r.smaller) {
        if (bounds[r.var].fi >= r.val) return 0;
        bounds[r.var].se = r.val - 1;
        return 1;
    } else {
        if (bounds[r.var].se <= r.val) return 0;
        bounds[r.var].fi = r.val + 1;
        return 1;
    }
}

bool updateBoundsInv(map<char, pair<ll, ll>> &bounds, Rule &r) {
    if (r.var == '*') return 0;
    if (r.smaller) {
        if (bounds[r.var].se < r.val) return 0;
        bounds[r.var].fi = r.val;
        return 1;
    } else {
        if (bounds[r.var].fi > r.val) return 0;
        bounds[r.var].se = r.val;
        return 1;
    }
}

ll dfs(string name, map<char, pair<ll, ll>> bounds) {
    if (name == "A" || name == "R") {
        if (name == "A") {
            ll res = 1;
            for (auto &p: bounds) {
                res *= (p.se.se - p.se.fi + 1);
            }
            return res;
        }
        return 0;
    }
    ll res = 0;
    for (auto &r: a[name]) {
        auto newBounds = bounds;
        if (updateBounds(newBounds, r)) res += dfs(r.forward, newBounds);
        if (!updateBoundsInv(bounds, r)) break;
    }
    return res;
}

ll part1() {
    ll res = 0;
    string line;
    while (getline(cin, line)) {
        istringstream ss(line);
        string token;
        map<char, ll> vals;
        ll sum = 0;
        for (int i = 0; i < 4; ++i) {
            ss >> token;
            ll val = stoll(token.substr(2));
            sum += val;
            vals[token[0]] = val;
        }
        if (check(vals)) res += sum;
    }
    return res;
}

ll part2() {
    map<char, pair<ll, ll>> bounds;
    for (char c: string("xmas")) {
        bounds[c] = {1, 4000};
    }
    return dfs("in", bounds);
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    string line;
    while (getline(cin, line)) {
        if (line == "") break;
        istringstream ss(line);
        string name;
        ss >> name;
        a[name] = parseRule(ss);
    }
    cout << part1() << "\n";
    cout << part2() << "\n";
}    