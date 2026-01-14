#include <bits/stdc++.h>
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
using namespace std;

#define sz(x) (int)((x).size())

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int V, K; cin >> V >> K;

    vector<tuple<int, int, int>> E;

    vector mat(V + 1, vector(V + 1, 0.0L));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            string val; cin >> val;
            mat[i][j] = stold(val);

            if (i < j) E.push_back({ i, j, mat[i][j] });
        }
    }

    int res = INT32_MAX;

    vector<vector<int>> adj(V);

    string state = string(sz(E) - (V - 1), '0') + string(V - 1, '1');
    do {
        int cost = 0;
        int e = 0;
        for (auto& [u, v, w] : E) {
            if (state[e] == '1') {
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
    } while (next_permutation(begin(state), end(state)));

    cout << res << "\n";
}