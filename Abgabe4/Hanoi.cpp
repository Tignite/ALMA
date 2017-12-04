#include <iostream>;
using namespace std;

int ausgabe (unsigned int m, int A [], int B [], int C []) {
    unsigned int j = 0;
    cout << "A: ";
    while (j < m) {
        cout << A [j];
        j++;
    }
    cout << endl;
    j = 0;
    cout << "B: ";
    while (j < m) {
        cout << B [j];
        j++;
    }
    cout << endl;
    j = 0;
    cout << "C: ";
    while (j < m) {
        cout << C [j];
        j++;
    }
    cout << endl << endl;
    return 0;
}

int bewege (unsigned int m, unsigned int n, int X [], int Y [], int Z [], int A [], int B [], int C []) {
    if (m == 1) {
        unsigned int k = 0;
        while (X [k] == 0) k++;
        unsigned int l = n - 1;
        while (Z [l] != 0) l--;
        Z [l] = X [k];
        X [k] = 0;
        ausgabe (n, A, B, C);
    }
    else {
        bewege (m - 1, n, X, Z, Y, A, B, C);
        bewege (1, n, X, Y, Z, A, B, C);
        bewege (m - 1, n, Y, X, Z, A, B, C);
    }
    return 0;
}

int main() {
    unsigned int n = 4;
    int A [n - 1];
    int B [n - 1];
    int C [n - 1];
    unsigned int i = 0;
    for (i = 0; i < n; i++) {
        A [i] = i + 1;
        B [i] = 0;
        C [i] = 0;
    }
    ausgabe (n, A, B, C);
    unsigned int m = n;
    bewege (m, n, A, B, C, A, B, C);
    return 0;
}
