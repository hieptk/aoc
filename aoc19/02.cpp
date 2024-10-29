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

ll process(vector<ll> a, int input1, int input2) {
    a[1] = input1;
    a[2] = input2;

    int i = 0;
    while (a[i] != 99) {
        int u = a[i + 1], v = a[i + 2], t = a[i + 3];
        if (a[i] == 1) {
            a[t] = a[u] + a[v];
        } else {
            a[t] = a[u] * a[v];
        }
        i += 4;
    }
    return a[0];
}

int main() {
    freopen("input.txt", "r", stdin);
    vector<ll> a;
    string token;
    while (getline(cin, token, ',')) {
        a.push_back(stoll(token));
    }

    cout << process(a, 12, 2) << "\n";

    for (int i = 0; i <= 99; ++i) {
        for (int j = 0; j <= 99; ++j) {
            if (process(a, i, j) == 19690720) {
                cout << 100 * i + j << "\n";
                return 0;
            }

        }
    }
}
