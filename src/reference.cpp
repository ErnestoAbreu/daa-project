#include <bits/stdc++.h>
using namespace std;
 
#define all(x) begin(x), end(x)
#define sz(x) (int)((x).size())

const int LIM = 9;

struct DSU {
    vector<int> par, sz;
    void init(int N) {
        sz.assign(N, 1);
        par.resize(N); iota(all(par), 0);
    } 
    int get(int x) {
        return x == par[x] ? x : par[x] = get(par[x]);
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        par[y] = x; sz[x] += sz[y];
        return true;
    }
};

bool check(int V, int K, const std::vector<std::vector<int>>& adj) {
    for (int i = 0; i < V; i++) {
        if ((int)adj[i].size() > K) return false;
    }
 
    std::vector<bool> vis(V); int cntCC = 0;
    auto dfs = [&](auto&& self, int u) -> void {
        cntCC++; vis[u] = true;
        for (auto& v : adj[u]) {
            if (!vis[v]) self(self, v);
        }
    };
 
    dfs(dfs, 0);
    
    return cntCC == V;
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int V, K; cin >> V >> K;

    vector<tuple<int, int, int>> E;

    vector mat(V + 1, vector(V + 1, 0));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            string val; cin >> val;
            mat[i][j] = stoi(val);

            if (i < j) E.push_back({i, j, mat[i][j]});
        }
    }
    
    if (K == 1 && V != 2) {
        cout << -1 << "\n";
        return 0;
    }

    if (K == V - 1 || V > LIM) {
        sort(all(E), [&](auto x, auto y) {
            return get<2>(x) < get<2>(y);
        });
        // take as reference the value of standard mst
        DSU D; D.init(V);
        int cost = 0;
        vector<array<int, 3>> edges;
        for (auto &[u, v, w]: E) {
            if (D.unite(u, v)) {
                edges.push_back({u, v, w});
                cost += w;
            }
        }
        cout << cost << "\n";
        for (auto &[u, v, w]: edges)
            cout << u+1 << " " << v+1 << " " << w << "\n";
        return 0;
    }

    int res = INT32_MAX;
    
    int cost = 0; 
    vector<vector<int>> adj(V); 
    vector<array<int, 3>> edges, best;
    auto solve = [&](auto &&self, int n, int k, int idx, bool rev) -> void {
        if (k > n || k < 0) return;

        if (n == 0) {
            if (check(V, K, adj)) {
                if (cost < res) {
                    best = edges;
                    res = cost;
                }
            }
            return;
        }

        auto &[u, v, w] = E[idx];
 
        {
            if (rev) {
                adj[u].push_back(v);
                adj[v].push_back(u);
                edges.push_back({u, v, w});
                cost += w;
            }

            if (sz(adj[u]) <= K && sz(adj[v]) <= K)
                self(self, n - 1, k - rev, idx + 1, false);
            
            if (rev) {
                adj[u].pop_back();
                adj[v].pop_back();
                edges.pop_back();
                cost -= w;
            }
        }
        
        {
            if (!rev) {
                adj[u].push_back(v);
                adj[v].push_back(u);
                edges.push_back({u, v, w});
                cost += w;
            }

            if (sz(adj[u]) <= K && sz(adj[v]) <= K)
                self(self, n - 1, k - !rev, idx + 1, true);
            
            if (!rev) {
                adj[u].pop_back();
                adj[v].pop_back();
                edges.pop_back();
                cost -= w;
            } 
        }
    };

    solve(solve, sz(E), V - 1, 0, false);

    if (best.empty()) {
        cout << -1 << "\n";
        return 0;
    }

    cout << res << "\n";

    for (auto &[u, v, w]: best)
        cout << u+1 << " " << v+1 << " " << w << "\n";
}
