#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n, k;
int a[1111][1111];

#define all(x) begin(x), end(x)

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

int readAns(InStream& stream) {
    int c = stream.readInt();
    
    if (c == -1) {
        return c;
    }
    
    DSU D; D.init(n);
    int cost = 0;
    for (int i = 0; i < n - 1; i++) {
        int u = stream.readInt(1, n, "u_i");
        int v = stream.readInt(1, n, "v_i");
        int w = stream.readInt(0, 100, "w_i");
        
        if (a[u-1][v-1] != w) {
            stream.quitf(_wa, "invalid edge");
        }
        
        if (D.unite(u-1, v-1)) {
            cost += w;
        } else {
            stream.quitf(_wa, "graph can't contain a cycle");
        }
    }
    
    return cost;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    
    n = inf.readInt();
    k = inf.readInt();
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = inf.readInt();
        }
    }
    
    int jans = readAns(ans);
    int pans = readAns(ouf);
    
    if (jans == -1) {
        if (pans == -1) 
            quitp(_pc(100-16), "partial points");
    
        else
            quitp(_pc(-16), "invalid answer");
    } 
    
    int score = 100.0 * double(jans) / double(pans) - 16;
    
    quitp(_pc(score), "partial points");
}