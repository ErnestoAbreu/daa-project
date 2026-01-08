#include <vector>

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
};