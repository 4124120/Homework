#include <iostream>
using namespace std;

// ���j�� Ackermann ���
int ackermann_recursive(int m, int n) {
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return ackermann_recursive(m - 1, 1);
    else
        return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
}

int main() {
    int m, n;
    cout << "�п�J m �P n�G";
    cin >> m >> n;

    int result = ackermann_recursive(m, n);
    cout << "Ackermann(" << m << ", " << n << ") = " << result << endl;

    return 0;
}
