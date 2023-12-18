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

const string dirs = "RDLU";
const bool part2 = 1;

ll area(vector<pair<ll, ll>>& fig) {
    ll res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        auto p = i ? fig[i - 1] : fig.back();
        auto q = fig[i];
        res += (p.fi - q.fi) * (p.se + q.se);
    }
    return abs(res) / 2;
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    char dir;
    string color;
    ll step;
    ll x = 0, y = 0;
    vector<pair<ll, ll>> points;
    ll cnt = 0;
    while (cin >> dir >> step >> color) {
        if (part2) {
            step = stoll(color.substr(2, 5), 0, 16);
            dir = dirs[color[7] - '0'];
        }
        cnt += step;

        switch (dir) {
            case 'U':
                y += step;
                break;
            case 'D':
                y -= step;
                break;
            case 'L':
                x -= step;
                break;
            case 'R':
                x += step;
                break;
        }
        points.eb(x, y);
    }
    cout << area(points) + cnt / 2 + 1 << "\n";
}    