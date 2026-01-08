#include <bits/stdc++.h>
#include "../utils/checker.h"
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

    vector<vector<int>> adj(V);

    int res = INT32_MAX;
    if (sz(E) < 31) {
        for (int mask = 0; mask < (1 << sz(E)); mask++) {
            if (__builtin_popcount(mask) != V - 1) continue;

            int cost = 0;
            int e = 0;
            for (auto& [u, v, w] : E) {
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
    }
    else {
        while (true);
    }

    cout << res << "\n";
}