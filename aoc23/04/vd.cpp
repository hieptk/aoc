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

unordered_set<int> readWinning(stringstream &ss) {
    unordered_set<int> winning;
    string tmp;
    while (ss >> tmp) {
        if (tmp == "|") break;
        winning.insert(stoi(tmp));
    }
    return winning;
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    string line;
    int res = 0, res2 = 0;
    unordered_map<int, int> numberOfCopies;
    while (getline(cin, line)) {
        stringstream ss(line);
        string id;
        ss >> id >> id;
        int idnum = stoi(id);
        res2 += numberOfCopies[idnum] + 1;

        auto winning = readWinning(ss);
        int cnt = 0;
        int guess;
        while (ss >> guess) {
            cnt += winning.count(guess);
        }
        res += (cnt > 0 ? (1 << (cnt - 1)) : 0);

        for (int i = 1; i <= cnt; ++i) {
            numberOfCopies[idnum + i] += numberOfCopies[idnum] + 1;
        }
    }
    cout << res << "\n";
    cout << res2 << "\n";
}
