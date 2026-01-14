#include <bits/stdc++.h>
#include "../utils/checker.h"
using namespace std;

using ll = long long;

#define sz(x) (int)((x).size())

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int V, K; cin >> V >> K;

    vector<tuple<int, int, int>> E;

    vector mat(V + 1, vector(V + 1, 0));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> mat[i][j];

            if (i < j) E.push_back({ i, j, mat[i][j] });
        }
    }

    int res = INT32_MAX;

    if (sz(E) >= 60) assert(false);

    vector<vector<int>> adj(V);
    vector<array<int, 3>> best;
    ll mask = (1LL << (V-1)) - 1, r, c;
    while(mask <= (1LL << sz(E)) - (1LL << (sz(E)-(V-1)))) {
        int cost = 0;
        int j = 0;
        vector<array<int, 3>> edges;
        for (auto [u, v, w] : E) {
            if (mask & (1LL << j)) {
                adj[u].push_back(v);
                adj[v].push_back(u);
                edges.push_back({u, v, w});
                cost += w;
            }
            j++;
        }
        
        if (check(V, K, adj)) {
            if (res > cost) {
                res = cost;
                best = edges;
            }
        }

        for (j = 0; j < V; j++)
            adj[j].clear();
        
        c = mask & -mask, r = mask+c, mask = r | (((r ^ mask) >> 2LL)/c);
    }

    cout << res << "\n";
    for (auto &[x, y, w]: best)
        cout << x+1 << " " << y+1 << " " << w << "\n";
}