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
 
using ll = long long;
using ld = long double;

using namespace std;

const ll minr = 200000000000000ll;
const ll maxr = 400000000000000ll;
const ld eps = 1e-9;

struct stone {
    ll x, y, z;
    ll vx, vy, vz;
};

vector<stone> a;

bool intersect(stone &a, stone &b) {
    ll A1 = a.vx, B1 = -b.vx, C1 = b.x - a.x;
    ll A2 = a.vy, B2 = -b.vy, C2 = b.y - a.y;
    ll D = A1 * B2 - A2 * B1;
    ll Dx = C1 * B2 - B1 * C2;
    ll Dy = A1 * C2 - A2 * C1;

    if (D != 0) {
        ld t1 = (ld) Dx / D, t2 =(ld) Dy / D;
        if (t1 < -eps || t2 < -eps) return 0;
        ld x = a.x + a.vx * t1, y = a.y + a.vy * t1;
        return x > minr - eps && x < maxr + eps && y > minr - eps && y < maxr + eps;
    }
    return 0;
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    stone tmp;
    while (cin >> tmp.x >> tmp.y >> tmp.z >> tmp.vx >> tmp.vy >> tmp.vz) a.emplace_back(tmp);

    int res = 0;
    for (int i = 0; i + 1 < a.size(); ++i) {
        for (int j = i + 1; j < a.size(); ++j) {
            if (intersect(a[i], a[j])) res++;
        }
    }
    cout << res << "\n";
}    