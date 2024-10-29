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

map<string, int> id;
vector<vector<int>> adj(1);
vector<int> d;

int dfs(int i, int par = -1, int depth = 0) {
    d[i] = depth;
    int res = depth;
    for (int j: adj[i]) {
        if (j != par) {
            res += dfs(j, i, depth + 1);
        }
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    string line;
    while (getline(cin, line)) {
        int pos = line.find(')');
        string a = line.substr(0, pos), b = line.substr(pos + 1);
        if (!id.count(a)) {
            id[a] = id.size() + 1;
            adj.emplace_back();
        }
        if (!id.count(b)) {
            id[b] = id.size() + 1;
            adj.emplace_back();
        }
        adj[id[a]].push_back(id[b]);
        adj[id[b]].push_back(id[a]);
    }

    d.resize(adj.size());
    cout << dfs(id["COM"]) << "\n";
    dfs(id["YOU"]);
    cout << d[id["SAN"]] - 2 << "\n";
}
