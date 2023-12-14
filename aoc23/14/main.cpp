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

constexpr bool part1 = 0;

vector<string> a;
int m, n;

void moveUp() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[j][i] == 'O') {
                int j2 = j;
                while (j2 > 0 && a[j2 - 1][i] == '.') j2--;
                swap(a[j2][i], a[j][i]);
            }
        }
    }
}

void moveLeft() {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 'O') {
                int j2 = j;
                while (j2 > 0 && a[i][j2 - 1] == '.') j2--;
                swap(a[i][j2], a[i][j]);
            }
        }
    }
}

void moveDown() {
    for (int i = 0; i < n; ++i) {
        for (int j = m; j >= 0; --j) {
            if (a[j][i] == 'O') {
                int j2 = j;
                while (j2 + 1 < m && a[j2 + 1][i] == '.') j2++;
                swap(a[j2][i], a[j][i]);
            }
        }
    }
}

void moveRight() {
    for (int i = 0; i < m; ++i) {
        for (int j = n - 1; j >= 0; --j) {
            if (a[i][j] == 'O') {
                int j2 = j;
                while (j2 + 1 < n && a[i][j2 + 1] == '.') j2++;
                swap(a[i][j2], a[i][j]);
            }
        }
    }
}

ll load() {
    ll res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 'O') {
                res += m - i;
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
    string line;
    while (getline(cin, line)) {
        a.eb(line);
    }
    m = a.size();
    n = a[0].size();

    if (part1) {
        moveUp();
        cout << load() << "\n";
    } else {
        for (int i = 0; i < 155; ++i) {
            moveUp();
            moveLeft();
            moveDown();
            moveRight();
        }
        cout << load() << "\n";
    }
}    
