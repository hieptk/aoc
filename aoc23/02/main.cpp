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

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    string line;
    int res = 0, res2 = 0;

    while (getline(cin, line)) {
        stringstream ss(line);
        string id, color;
        int cnt;
        ss >> id >> id;
        map<string, int> maxcnt;
        while (ss >> cnt >> color) {
            if (color.back() == ',' || color.back() == ';') color.pop_back();
            maxcnt[color] = max(maxcnt[color], cnt);
        }
        if (maxcnt["red"] <= 12 && maxcnt["green"] <= 13 && maxcnt["blue"] <= 14) {
            res += stoi(id);
        }
        res2 += maxcnt["red"] * maxcnt["green"] * maxcnt["blue"];
    }
    cout << res << "\n";
    cout << res2 << "\n";
}
