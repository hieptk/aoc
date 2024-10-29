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

ll getParam(vector<ll> &a, int i, int mode) {
    ll res = a[i];
    if (mode == 0) res = a[res];
    return res;
}

void process(vector<ll> a, int input) {
    int i = 0;
    while (a[i] != 99) {
        int op = abs(a[i]) % 100;
        int mode1 = (abs(a[i]) / 100) % 10;
        int mode2 = (abs(a[i]) / 1000) % 10;
        if (op == 1 || op == 2) {
            ll u = getParam(a, i + 1, mode1);
            ll v = getParam(a, i + 2, mode2);
            int t = getParam(a, i + 3, 1);
            a[t] = op == 1 ? u + v : u * v;
            i += 4;
        } else if (op == 3) {
            int u = getParam(a, i + 1, 1);
            a[u] = input;
            i += 2;
        } else if (op == 4) {
            int u = getParam(a, i + 1, 1);
            cout << a[u] << "\n";
            i += 2;
        } else if (op == 5 || op == 6) {
            ll u = getParam(a, i + 1, mode1);
            ll v = getParam(a, i + 2, mode2);
            bool jump = (op == 5) ^ (u == 0);
            i = jump ? v : i + 3;
        } else if (op == 7 || op == 8) {
            ll u = getParam(a, i + 1, mode1);
            ll v = getParam(a, i + 2, mode2);
            int t = getParam(a, i + 3, 1);
            a[t] = op == 7 ? u < v : u == v;
            i += 4;
        } else {
            cout << "WRONG\n";
            exit(1);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    string token;
    vector<ll> a;
    while (getline(cin, token, ',')) a.push_back(stoll(token));

    process(a, 1);
    process(a, 5);
}
