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

const string cards = "23456789TJQKA";
const string cards2 = "J23456789TQKA";

vector<pair<string, ll>> hands;

int getRank(string &a) {
    map<char, int> cnt;
    for (char c: a) cnt[c]++;
    // 5 of a kind
    if (cnt.size() == 1) return 6;
    if (cnt.size() == 2) {
        // 4 of a kind
        if (cnt[a[0]] == 4 || cnt[a[1]] == 4) return 5;
        // full house
        return 4;
    }
    // 3 of a kind
    if (cnt[a[0]] == 3 || cnt[a[1]] == 3 || cnt[a[2]] == 3) return 3;
    // 2 pairs
    if (cnt.size() == 3) return 2;
    // 1 pair
    if (cnt.size() == 4) return 1;
    return 0;
}

int tryit(string &a, int i) {
    if (i == 5) return getRank(a);
    if (a[i] != 'J') return tryit(a, i + 1);
    int res = -1;
    for (int j = 1; j < cards2.length(); ++j) {
        a[i] = cards2[j];
        res = max(res, tryit(a, i + 1));
    }
    a[i] = 'J';
    return res;
}

bool cmpCards(string &a, string &b, const string &cards) {
    for (int i = 0; i < 5; ++i) {
        if (a[i] != b[i]) {
            return cards.find(a[i]) < cards.find(b[i]);
        }
    }
    return 0;
}

bool cmp(pair<string, ll> &a, pair<string, ll> & b) {
    int ta = getRank(a.fi), tb = getRank(b.fi);
    return ta != tb ? ta < tb : cmpCards(a.fi, b.fi, cards);
}

bool cmp2(pair<string, ll> &a, pair<string, ll> & b) {
    int ta = tryit(a.fi, 0), tb = tryit(b.fi, 0);
    return ta != tb ? ta < tb : cmpCards(a.fi, b.fi, cards2);
}

ll score() {
    ll res = 0;
    for (int i = 0; i < hands.size(); ++i) {
        res += hands[i].se * (i + 1);
    }
    return res;
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    string tmp;
    ll tmpnum;
    while (cin >> tmp >> tmpnum) {
        hands.eb(tmp, tmpnum);
    }

    sort(hands.begin(), hands.end(), cmp);
    cout << score() << "\n";

    sort(hands.begin(), hands.end(), cmp2);
    cout << score() << "\n";
}
