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

ll count(ll time, ll dist) {
    ll cnt = 0;
    for (ll t = 1; t <= time; ++t) {
        if ((time - t) > dist / t) cnt++;
    }
    return cnt;
}

ll solve(vector<ll> &time, vector<ll> &dist) {
    ll res = 1;
    for (int i = 0; i < time.size(); ++i) {
        res *= count(time[i], dist[i]);
    }
    return res;
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<ll> time = {46, 68, 98, 66};
    vector<ll> dist = {358, 1054, 1807, 1080};
    cout << solve(time, dist) << "\n";
    time = {46689866};
    dist = {358105418071080ll};
    cout << solve(time, dist) << "\n";
}
