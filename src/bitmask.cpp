#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)((x).size())

int main() {
    cin.tie(0)->sync_with_stdio(0);

    auto check = [&](int V, int K, const vector<vector<int>> &adj) {
        for (int i = 0; i < V; i++) {
            if (sz(adj[i]) > K) return false;
        }
        
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

    vector<vector<int>> adj(V); 

    long double res = numeric_limits<long double>::max();
    for (int mask = 0; mask < (1 << sz(E)); mask++) {
        if (__builtin_popcount(mask) != V - 1) continue;

        long double cost = 0;
        for (int e = 0; auto &[u, v, w]: E) {
            if (mask >> e & 1) {
                adj[u].push_back(v);
                adj[v].push_back(u);
                cost += w;
            }
            e++;
        }

        if (check(V, K, adj))
            res = min(res, cost);

        for (int i = 0; i < V; i++)
            adj[i].clear();
    }

    cout << setprecision(12) << fixed << res << "\n";
}