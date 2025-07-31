// main.cpp
#include "Polynomial.h"

int main() {
    Polynomial p1, p2, sum, product;

    cout << "Polynomial 1:\n";
    cin >> p1;
    cout << "Polynomial 2:\n";
    cin >> p2;

    sum = p1.Add(p2);
    product = p1.Mult(p2);

    cout << "\nP1 = " << p1 << endl;
    cout << "P2 = " << p2 << endl;
    cout << "Sum = " << sum << endl;
    cout << "Product = " << product << endl;

    float x;
    cout << "\nEnter a value for x to evaluate P1: ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Eval(x) << endl;

    return 0;
}

