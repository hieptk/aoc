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

ll f(ll mass) {
    return mass / 3 - 2;
}

ll f2(ll mass) {
    ll res = f(mass);
    if (res <= 0) return 0;
    return res + f2(res);
}

int main() {
    freopen("input.txt", "r", stdin);
    ll mass, res = 0, res2 = 0;
    while (cin >> mass) {
        res += f(mass);
        res2 += f2(mass);
    }
    cout << res << "\n";
    cout << res2 << "\n";
}
