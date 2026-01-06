#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)((x).size())

int main() {
    cin.tie(0)->sync_with_stdio(0);

    auto check = [&](int V, const vector<vector<int>> &adj) { 
        vector<bool> vis(V); int cntCC = 0;
        auto dfs = [&](auto &&self, int u) -> void {
            cntCC++; vis[u] = true;
            for (auto &v: adj[u]) {
                if (!vis[v]) self(self, v);
            }
        };

        dfs(dfs, 0); 
        
        return cntCC == V;
    };

    int V, K; cin >> V >> K;

    vector<tuple<int, int, long double>> E;

    vector mat(V + 1, vector(V + 1, 0.0L));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            string val; cin >> val;
            mat[i][j] = stold(val);

            if (i < j) E.push_back({i, j, mat[i][j]});
        }
    }

    long double res = numeric_limits<long double>::max();
    
    long double cost = 0; 
    vector<vector<int>> adj(V); 
    auto solve = [&](auto &&self, int n, int k, int idx, bool rev) -> void {
        if (k > n || k < 0) return;

        if (n == 0) {
            if (check(V, adj))
                res = min(res, cost);
            return;
        }

        auto &[u, v, w] = E[idx];
 
        {
            if (rev) {
                adj[u].push_back(v);
                adj[v].push_back(u);
                cost += w;
            }

            if (sz(adj[u]) <= K && sz(adj[v]) <= K)
                self(self, n - 1, k - rev, idx + 1, false);
            
            if (rev) {
                adj[u].pop_back();
                adj[v].pop_back();
                cost -= w;
            }
        }
        
        {
            if (!rev) {
                adj[u].push_back(v);
                adj[v].push_back(u);
                cost += w;
            }

            if (sz(adj[u]) <= K && sz(adj[v]) <= K)
                self(self, n - 1, k - !rev, idx + 1, true);
            
            if (!rev) {
                adj[u].pop_back();
                adj[v].pop_back();
                cost -= w;
            } 
        }
    };

    solve(solve, sz(E), V - 1, 0, false);

    cout << setprecision(12) << fixed << res << "\n";
}