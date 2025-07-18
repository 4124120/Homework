#include <iostream>
#include <stack>
using namespace std;

// �D���j�� Ackermann ��ơA�ϥ� stack �������j
int ackermann_nonrecursive(int m, int n) {
    stack<int> s;
    s.push(m);

    while (!s.empty()) {
        m = s.top();
        s.pop();

        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            s.push(m - 1);
            n = 1;
        } else {
            s.push(m - 1);
            s.push(m);
            n = n - 1;
        }
    }

    return n;
}

int main() {
    int m, n;
    cout << "�п�J m �P n�G";
    cin >> m >> n;

    int result = ackermann_nonrecursive(m, n);
    cout << "Ackermann(" << m << ", " << n << ") = " << result << endl;

    return 0;
}
