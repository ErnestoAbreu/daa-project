#include "utils/testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    
    string mode = argv[1];
    
    int V, K;
    if (mode == "fixed") {
        V = atoi(argv[2]);
        K = atoi(argv[3]);
    } else if (mode == "small") {
        V = rnd.next(1, 6);
        K = rnd.next(1, max(1, V - 1));
    } else if (mode == "medium") {
        V = rnd.next(1, 10);
        K = rnd.next(1, max(1, V - 1)); 
    } else if (mode == "big") {
        V = rnd.next(1, 1000);
        K = rnd.next(1, max(1, V - 1)); 
    } else {
        assert(false);
    }

    vector mat(V + 1, vector(V + 1, 0.0L));
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            mat[i][j] = mat[j][i] = rnd.next(1e9);
        }
    }

    println(V, K);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << setprecision(12) << fixed << mat[i][j] << " \n"[j == V - 1];
        }
    }
}
