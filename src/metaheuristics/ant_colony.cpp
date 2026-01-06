#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)((x).size())

using Edge = tuple<int, int, long double>;

struct DSU {
    vector<int> e; 
    void init(int N) { e = vector<int>(N, -1); }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool sameSet(int x, int y) { return get(x) == get(y); }
    int size(int x) { return -e[get(x)]; }
    bool unite(int x, int y) {
        x = get(x), y = get(y); if (x == y) return 0;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y]; e[y] = x; return 1;
    }
};

struct Instance { 
    int V, K; 
    vector<Edge> edges; 
    vector<vector<long double>> mat; 
};

mt19937 rng(time(nullptr));

long double drand(long double a, long double b) {
    uniform_real_distribution<long double> dist(a, b);
    return dist(rng);
}

int irand(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist(rng);
}

long double treeCost(const vector<Edge> &edges) {
    long double res = 0;
    for (auto &[u, v, w]: edges)
        res += w;
    return res;
}

bool isSpanningTree(const vector<Edge>& edges, int V) {
    if (sz(edges) != V - 1) return false;

    vector<vector<int>> adj(V);
    for (auto &[u, v, w]: edges)
        adj[u].push_back(v), adj[v].push_back(u);

    vector<bool> vis(V); int cntCC = 0;
    auto dfs = [&](auto &&self, int u) -> void {
        cntCC++; vis[u] = true;
        for (auto &v: adj[u]) {
            if (!vis[v]) self(self, v);
        }
    };

    dfs(dfs, 0); 
    
    return cntCC == V;
}

bool checkDegreeConstraint(const vector<Edge>& edges, int V, int K) {
    vector<int> deg(V, 0);
    for (auto &[u, v, w]: edges) {
        deg[u]++, deg[v]++;
        if (deg[u] > K || deg[v] > K)
            return false;
    }
    return true;
}

vector<Edge> randomTree(const Instance &I) {
    int V = I.V, K = I.K;
    vector<int> inTree(V, 0), deg(V, 0);
    int root = irand(0, V - 1); inTree[root] = 1;

    vector<Edge> tree;
    for (int step = 0; step < V - 1; step++) {
        vector<Edge> cand;
        for (int u = 0; u < V; u++) if (inTree[u] && deg[u] < K)
            for (int v = 0; v < V; v++) if (!inTree[v] && deg[v] < K)
                cand.push_back({u, v, I.mat[u][v]});

        if (cand.empty()) return {};

        shuffle(begin(cand), end(cand), rng);

        auto [u, v, w] = cand[0];
        tree.push_back(cand[0]);
        inTree[u] = inTree[v] = 1; deg[u]++, deg[v]++;
    } 
    return isSpanningTree(tree, V) ? tree : vector<Edge>{};
}

vector<Edge> antColony(const Instance& I, int ants = 50, int iter = 200, long double alpha = 1.0, long double beta = 2.0, long double rho = 0.1, long double q0 = 0.9) {
    int V = I.V, K = I.K, m = sz(I.edges);
    map<pair<int, int>, int> edgeIdx;
    for (int i = 0; auto &[u, v, w]: I.edges) {
        edgeIdx[{u, v}] = edgeIdx[{v, u}] = i;
    } 

    vector<long double> tau(m, 1.0);
    long double best = numeric_limits<long double>::max();
    vector<Edge> bestTree;

    for (int it = 0; it < iter; it++) {
        vector<pair<vector<Edge>, long double>> antsCost;
        for (int a = 0; a < ants; a++) {
            struct Cand {
                int u, v, idx;
                long double w, attr;
            };

            vector<Edge> tree;
            vector<int> deg(V, 0);
            DSU D; D.init(V);

            while (sz(tree) < V - 1) {
                vector<Cand> cands;
                for (int u = 0; u < V; u++) {
                    for (int v = u + 1; v < V; v++) {
                        if (deg[u] < K && deg[v] < K && !D.sameSet(u, v)) {
                            int idx = edgeIdx[{u, v}];
                            long double heuristic = powl(1.0L / (I.mat[u][v] + 1e-9), beta);
                            long double attr = powl(tau[idx], alpha) * heuristic;
                            cands.push_back({u, v, idx, I.mat[u][v], attr});
                        }
                    }
                }

                if (cands.empty()) {
                    tree = randomTree(I);
                    break;
                }

                sort(begin(cands), end(cands), [&](const Cand &l, const Cand &r) {
                    return l.attr > r.attr;
                });

                int idx = 0;
                if (drand(0.0, 1.0) >= q0) {
                    long double s = 0;
                    for (auto &c: cands) s += c.attr;
                    if (s <= 0) idx = irand(0, sz(cands) - 1);
                    else {
                        long double r = drand(0.0, s), cum = 0;
                        for (int i = 0; i < sz(cands); i++) {
                            cum += cands[i].attr;
                            if (r <= cum) {
                                idx = i; break;
                            }
                        }
                    }
                }

                auto ch = cands[idx];
                D.unite(ch.u, ch.v);
                tree.push_back({ch.u, ch.v, ch.w});
                deg[ch.u]++, deg[ch.v]++;
            }
            if (tree.empty()) continue;

            if (!isSpanningTree(tree, V) || !checkDegreeConstraint(tree, V, K)) {
                tree = randomTree(I);
            }

            long double cost = treeCost(tree);
            antsCost.push_back({tree, cost});
            if (cost < best) {
                best = cost; bestTree = tree;
            }
        }

        for (auto &x: tau) x *= (1.0 - rho);
        if (!antsCost.empty()) {
            auto localBest = *min_element(begin(antsCost), end(antsCost), [](auto &a, auto &b) { return a.second < b.second; });
            long double deposit = 1.0 / (localBest.second + 1e-9);
            for (auto &e: localBest.first) {
                int u = get<0>(e), v = get<1>(e);
                tau[edgeIdx[{u, v}]] += deposit;
            }
        }

        if (!bestTree.empty()) {
            long double deposit = 0.5/(best + 1e-9);
            for (auto &e: bestTree){ 
                int u = get<0>(e), v = get<1>(e); 
                tau[edgeIdx[{u,v}]] += deposit; 
            }
        }
    }
    
    return bestTree;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

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

    Instance I;
    I.V = V, I.K = K, I.edges = E, I.mat = mat;

    auto tree = antColony(I);
    
    if (sz(tree) != V - 1) {
        cout << setprecision(12) << fixed << numeric_limits<long double>::max();
    } else {
        cout << setprecision(12) << fixed << treeCost(tree) << "\n";
    }
}