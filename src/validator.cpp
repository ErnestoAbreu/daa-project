#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int k = inf.readInt(1, n - 1, "k");
    inf.readEoln();
    
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != 0) inf.readSpace();
            int x = inf.readInt(0, 100, "a_ij");
            a[i][j] = x;
        }
        inf.readEoln();
    }
    
    inf.readEof();
    
    for (int i = 0; i < n; i++) {
        ensure(a[i][i] == 0);
        for (int j = i + 1; j < n; j++) {
            ensure(a[i][j] == a[j][i]);
        }
    }   
}