#include <iostream>
#include "Polynomial.cpp"  // 直接 include 實作檔（若未拆成 .h/.cpp）

using namespace std;

int main() {
    Polynomial p1, p2, result;

    cout << "Enter first polynomial (format: n c1 e1 c2 e2 ... cn en): ";
    cin >> p1;

    cout << "Enter second polynomial (format: n c1 e1 c2 e2 ... cn en): ";
    cin >> p2;

    cout << "P1(x) = " << p1 << endl;
    cout << "P2(x) = " << p2 << endl;

    result = p1 + p2;
    cout << "P1(x) + P2(x) = " << result << endl;

    result = p1 - p2;
    cout << "P1(x) - P2(x) = " << result << endl;

    result = p1 * p2;
    cout << "P1(x) * P2(x) = " << result << endl;

    float x;
    cout << "Enter x to evaluate P1(x): ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Evaluate(x) << endl;

    return 0;
}

