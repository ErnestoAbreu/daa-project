#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);

    string mode = argv[1];
    string modek = argv[2];

    int V, K;
    if (mode == "fixed") {
        V = atoi(argv[2]);
        K = atoi(argv[3]);
    } else if (mode == "random1") {
        V = rnd.next(16, 30);
        K = rnd.next(1, V - 1);
    } else if (mode == "random2") {
        V = rnd.next(31, 50);
        K = rnd.next(1, V - 1);
    } else if (mode == "random3") {
        V = rnd.next(51, 70);
        K = rnd.next(1, V - 1);
    } else if (mode == "random4") {
        V = rnd.next(71, 100);
        K = rnd.next(1, V - 1);
    }

    if (K >= V) K = rnd.next(1, V - 1);
    
    if (K == 1 && V > 2) {
        K = 2;
    }

    vector mat(V + 1, vector(V + 1, 0));
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            mat[i][j] = mat[j][i] = rnd.next(1, 100);
        }
    }

    println(V, K);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << mat[i][j] << " \n"[j == V - 1];
        }
    }
}
