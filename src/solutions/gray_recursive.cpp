#include <bits/stdc++.h>
#include "../utils/checker.h"
using namespace std;

#define sz(x) (int)((x).size())

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int V, K; cin >> V >> K;

    vector<tuple<int, int, int>> E;

    vector mat(V + 1, vector(V + 1, 0));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            string val; cin >> val;
            mat[i][j] = stold(val);

            if (i < j) E.push_back({i, j, mat[i][j]});
        }
    }

    int res = INT32_MAX;
    
    int cost = 0; 
    vector<vector<int>> adj(V); 
    auto solve = [&](auto &&self, int n, int k, int idx, bool rev) -> void {
        if (k > n || k < 0) return;

        if (n == 0) {
            if (check(V, K, adj))
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

    cout << res << "\n";
}