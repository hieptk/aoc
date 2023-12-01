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

using ll = long long;
using ld = double;
 
#define eb emplace_back
#define fi first
#define se second
 
using namespace std;

const string digits[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int parse(string &s, bool task2) {
    int first = 1e9, last = -1;
    int firstv = -1, lastv = -1;
    for (char c = '1'; c <= '9'; ++c) {
        int id = s.find(c);
        if (id >= 0 && id < s.length()) {
            if (id < first) {
                first = id;
                firstv = c - '0';
            }
            id = s.rfind(c);
            if (id > last) {
                last = id;
                lastv = c - '0';
            }
        }
    }
    if (task2) {
        for (int i = 1; i < 10; ++i) {
            int id = s.find(digits[i]);
            if (id >= 0 && id < s.length()) {
                if (id < first) {
                    first = id;
                    firstv = i;
                }
                id = s.rfind(digits[i]);
                if (id > last) {
                    last = id;
                    lastv = i;
                }
            }
        }
    }
    return firstv * 10 + lastv;
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    string s;
    int res = 0, res2 = 0;
    while (getline(cin, s)) {
        res += parse(s, 0);
        res2 += parse(s, 1);
    }   
    cout << res << " " << res2 << "\n";
}