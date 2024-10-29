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
#include <map>
#include <sstream>
#include <stack>
#include <bitset>
 
using ll = long long;   
using ld = long double;
 
using namespace std;

bool check(int n) {
    string s = to_string(n);
    bool eq = 0;
    for (int i = 0; i + 1 < s.size(); ++i) {
        if (s[i + 1] < s[i]) {
            return 0;
        } else if (s[i + 1] == s[i]) {
            eq = 1;
        }
    }
    return eq;
}

bool check2(int n) {
    string s = to_string(n);
    int cur = 0;
    bool has2 = 0;
    for (int i = 0; i + 1 < s.size(); ++i) {
        if (s[i + 1] < s[i]) {
            return 0;
        } else if (s[i + 1] == s[i]) {
            cur++;
        } else {
            if (cur == 1) has2 = 1;
            cur = 0;
        }
    }
    if (cur == 1) has2 = 1;
    return has2;
}

int main() {
    freopen("input.txt", "r", stdin);
    int res = 0, res2 = 0;
    for (int i = 152085; i <= 670283; ++i) {
        res += check(i);
        res2 += check2(i);
    }
    cout << res << "\n";
    cout << res2 << "\n";
}
