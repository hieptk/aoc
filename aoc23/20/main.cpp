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

const string start = "roadcaster";
const string lastNode = "jz";

struct Node {
    string name;
    char type;
    vector<string> adj;
    bool on;
    map<string, bool> input;
};

map<string, Node*> name2node;

tuple<bool, int, int> bfs(string target = "?") {
    queue<tuple<string, bool, string>> q;
    q.emplace(start, 1, "");
    int cntLow = 0, cntHigh = 0;
    while (q.size()) {
        string name, prev;
        bool low;
        tie(name, low, prev) = q.front();
        q.pop();
        if (low) cntLow++;
        else cntHigh++;
        if (name == lastNode && prev == target && !low) {
            return {1, 0, 0};
        }
        if (!name2node.count(name)) continue;
        Node *node = name2node[name];
        if (node->type == 'b') {
            for (string &n: node->adj) {
                q.emplace(n, low, name);
            }
        } else if (node->type == '%') {
            if (low) {
                node->on = !node->on;
                for (string &n: node->adj) {
                    q.emplace(n, !node->on, name);
                }
            }
        } else {
            node->input[prev] = !low;
            bool allHigh = all_of(node->input.begin(), node->input.end(), [](auto &p){
                return p.second;
            });
            for (string &n: node->adj) {
                q.emplace(n, allHigh, name);
            }
        }
    }
    return {0, cntLow, cntHigh};
}

void readNode(string &line) {
    istringstream ss(line);
    Node* node = new Node();
    ss >> node->name;
    node->type = node->name[0];
    node->name = node->name.substr(1);
    
    string neigh;
    ss >> neigh;
    while (ss >> neigh) {
        if (neigh.back() == ',') neigh.pop_back();
        node->adj.eb(neigh);
    }
    name2node[node->name] = node;
}

void init(const string &name, set<string> &visited) {
    visited.insert(name);
    auto node = name2node[name];
    if (node->type == '%') node->on = 0;;
    for (auto &n: node->adj) {
        if (!name2node.count(n)) continue;
        if (name2node[n]->type == '&') {
            name2node[n]->input[name] = 0;
        }
        if (!visited.count(n)) init(n, visited);
    }
}

void part1() {
    set<string> visited;
    init(start, visited);
    bool found;
    int low, high;
    ll sumLow = 0, sumHigh = 0;
    for (int i = 1; i <= 1000; ++i) {
        tie(found, low, high) = bfs();
        sumLow += low;
        sumHigh += high;
    }
    cout << sumLow * sumHigh << "\n";
}

void part2() {
    ll res = 1;
    for (auto &name: {"dh", "mk", "rn", "vf"}) {
        set<string> visited;
        init(start, visited);
        int cnt = 0;
        while (!get<0>(bfs(name))) cnt++;
        res *= cnt + 1;
    }
    cout << res << "\n";
}

int main() {
    #ifdef LOCAL
    freopen("input2.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    string line;
    while (getline(cin, line)) readNode(line);

    part1();
    part2();
}    