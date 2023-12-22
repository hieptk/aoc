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

struct rec {
    int id, x1, y1, z1, x2, y2, z2;
};

vector<rec> a;
int used[20][20][400];
vector<set<int>> above, below;

void mark(rec &r) {
    for (int i = r.x1; i <= r.x2; ++i) {
        for (int j = r.y1; j <= r.y2; ++j) {
            for (int k = r.z1; k <= r.z2; ++k) used[i][j][k] = r.id;
        }
    }
}

void fall(rec &r) {
    int step = r.z1 - 1;
    for (int i = r.x1; i <= r.x2; ++i) {
        for (int j = r.y1; j <= r.y2; ++j) {
            int k = 0;
            while (r.z1 - k >= 2 && used[i][j][r.z1 - k - 1] == -1) k++;
            step = min(step, k);
        }
    }

    for (int i = r.x1; i <= r.x2; ++i) {
        for (int j = r.y1; j <= r.y2; ++j) {
            for (int k = 1; k <= step; ++k) {
                used[i][j][r.z1 - k] = r.id;
                used[i][j][r.z2 + 1 - k] = -1;
            }
        }
    }

    r.z1 -= step;
    r.z2 -= step;
}

void findAbove(rec &r) {
    for (int i = r.x1; i <= r.x2; ++i) {
        for (int j = r.y1; j <= r.y2; ++j) {
            if (used[i][j][r.z2 + 1] != -1) {
                above[r.id].insert(used[i][j][r.z2 + 1]);
                below[used[i][j][r.z2 + 1]].insert(r.id);
            }
        }
    }
}

int bfs(int s) {
    vector<int> belowCnt(a.size());
    for (int i = 0; i < a.size(); ++i) belowCnt[i] = below[i].size();
    queue<int> q;
    q.emplace(s);
    int res = 0;

    while (!q.empty()) {
        int i = q.front();
        q.pop();
        for (int j: above[i]) {
            if (--belowCnt[j] == 0) {
                res++;
                q.emplace(j);
            }
        }
    }
    return res;
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    memset(used, -1, sizeof(used));
    rec tmp;
    
    while (cin >> tmp.x1 >> tmp.y1 >> tmp.z1 >> tmp.x2 >> tmp.y2 >> tmp.z2) {
        tmp.id = a.size();
        a.eb(tmp);
        mark(tmp);
    }

    sort(a.begin(), a.end(), [](auto &r1, auto &r2) {
        return r1.z1 < r2.z1;
    });
    
    for (rec &r: a) fall(r);

    above.resize(a.size());
    below.resize(a.size());
    for (rec &r: a) findAbove(r);

    int res = 0;
    int res2 = 0;
    for (rec &r: a) {
        int tmp = bfs(r.id);
        res += (tmp == 0);
        res2 += tmp;
    }
    cout << res << " " << res2 << "\n";
}    