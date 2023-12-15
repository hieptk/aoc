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

const int mod = 256;

vector<pair<string, int>> a[mod];

int getHash(string &s) {
    int res = 0;
    for (char x: s) {
        res = ((res + x) * 17) % mod;
    }
    return res;
}

void remove(string &key) {
    int id = getHash(key);
    for (auto it = a[id].begin(); it != a[id].end(); ++it) {
        if (it->fi == key) {
            a[id].erase(it);
            break;
        }
    }
}

void update(string &key, int val) {
    int id = getHash(key);
    for (auto &p: a[id]) {
        if (p.fi == key) {
            p.se = val;
            return;
        }
    }
    a[id].eb(key, val);
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    string line;
    int res = 0;
    while (getline(cin, line, ',')) {
        res += getHash(line);
        
        auto pos = line.find('=');
        if (pos == string::npos) {
            line.pop_back();
            remove(line);
        } else {
            string key = line.substr(0, pos);
            int val = stoi(line.substr(pos + 1));
            update(key, val);
        }
    }
    cout << res << "\n";

    int res2 = 0;
    for (int i = 0; i < mod; ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            res2 += (i + 1) * (j + 1) * a[i][j].se;
        }
    }
    cout << res2 << "\n";
}    
