# 41241207

作業三

## 解題說明

本作業要求開發一個 Polynomial 類別，用以表示與操作整數係數的一元多項式，並使用**循環鏈結串列（circular linked list）**來儲存每一個項（term）。每個節點包含三個欄位：係數（coef）、指數（exp）、與下一個節點的指標（link）。並需實作多項式的建構、輸入輸出、加減乘法、賦值、複製、求值等操作。

### 解題策略

1. 資料結構設計：
   
   使用 Term 結構儲存一項（包含 coef、exp）。

   使用循環鏈結串列，以 Header node 作為起始點，避免空指標問題。

2. 操作設計：

   多項式輸入為項數 n，接著是 n 個 (coef, exp)。

   所有指數須為遞減排序。

   使用運算子多載進行操作（如 +, -, *, >>, <<, = 等）。

   實作 Evaluate 函式，計算某一點 x 對應的多項式值。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Term {
    friend class Polynomial;
private:
    int coef;
    int exp;
    Term* link;
};

class Polynomial {
public:
    Polynomial();
    Polynomial(const Polynomial& a);
    ~Polynomial();

    friend istream& operator>>(istream& is, Polynomial& x);
    friend ostream& operator<<(ostream& os, Polynomial& x);

    const Polynomial& operator=(const Polynomial& a);
    Polynomial operator+(const Polynomial& b) const;
    Polynomial operator-(const Polynomial& b) const;
    Polynomial operator*(const Polynomial& b) const;
    float Evaluate(float x) const;

private:
    Term* head;
    void Clear();
    void Attach(int coef, int exp);
};

// Constructor
Polynomial::Polynomial() {
    head = new Term;
    head->link = head;
}

// Copy Constructor
Polynomial::Polynomial(const Polynomial& a) {
    head = new Term;
    head->link = head;
    Term* curr = a.head->link;
    while (curr != a.head) {
        Attach(curr->coef, curr->exp);
        curr = curr->link;
    }
}

// Destructor
Polynomial::~Polynomial() {
    Clear();
    delete head;
}

// 清除節點
void Polynomial::Clear() {
    Term* curr = head->link;
    while (curr != head) {
        Term* temp = curr;
        curr = curr->link;
        delete temp;
    }
    head->link = head;
}

// 加入新項
void Polynomial::Attach(int coef, int exp) {
    Term* newTerm = new Term{coef, exp, head};
    Term* curr = head;
    while (curr->link != head) curr = curr->link;
    curr->link = newTerm;
}

// 輸入運算子多載
istream& operator>>(istream& is, Polynomial& x) {
    int n, coef, exp;
    is >> n;
    for (int i = 0; i < n; ++i) {
        is >> coef >> exp;
        x.Attach(coef, exp);
    }
    return is;
}

// 輸出運算子多載
ostream& operator<<(ostream& os, Polynomial& x) {
    Term* curr = x.head->link;
    while (curr != x.head) {
        os << curr->coef << "x^" << curr->exp;
        if (curr->link != x.head) os << " + ";
        curr = curr->link;
    }
    return os;
}

// 賦值運算子
const Polynomial& Polynomial::operator=(const Polynomial& a) {
    if (this != &a) {
        Clear();
        Term* curr = a.head->link;
        while (curr != a.head) {
            Attach(curr->coef, curr->exp);
            curr = curr->link;
        }
    }
    return *this;
}

// 多項式加法
Polynomial Polynomial::operator+(const Polynomial& b) const {
    Polynomial result;
    Term *a = head->link, *bTerm = b.head->link;
    while (a != head && bTerm != b.head) {
        if (a->exp > bTerm->exp) {
            result.Attach(a->coef, a->exp);
            a = a->link;
        } else if (a->exp < bTerm->exp) {
            result.Attach(bTerm->coef, bTerm->exp);
            bTerm = bTerm->link;
        } else {
            int sum = a->coef + bTerm->coef;
            if (sum != 0) result.Attach(sum, a->exp);
            a = a->link;
            bTerm = bTerm->link;
        }
    }
    while (a != head) {
        result.Attach(a->coef, a->exp);
        a = a->link;
    }
    while (bTerm != b.head) {
        result.Attach(bTerm->coef, bTerm->exp);
        bTerm = bTerm->link;
    }
    return result;
}

// 多項式減法
Polynomial Polynomial::operator-(const Polynomial& b) const {
    Polynomial result;
    Term *a = head->link, *bTerm = b.head->link;
    while (a != head && bTerm != b.head) {
        if (a->exp > bTerm->exp) {
            result.Attach(a->coef, a->exp);
            a = a->link;
        } else if (a->exp < bTerm->exp) {
            result.Attach(-bTerm->coef, bTerm->exp);
            bTerm = bTerm->link;
        } else {
            int diff = a->coef - bTerm->coef;
            if (diff != 0) result.Attach(diff, a->exp);
            a = a->link;
            bTerm = bTerm->link;
        }
    }
    while (a != head) {
        result.Attach(a->coef, a->exp);
        a = a->link;
    }
    while (bTerm != b.head) {
        result.Attach(-bTerm->coef, bTerm->exp);
        bTerm = bTerm->link;
    }
    return result;
}

// 多項式乘法
Polynomial Polynomial::operator*(const Polynomial& b) const {
    Polynomial result;
    for (Term* aTerm = head->link; aTerm != head; aTerm = aTerm->link) {
        Polynomial temp;
        for (Term* bTerm = b.head->link; bTerm != b.head; bTerm = bTerm->link) {
            temp.Attach(aTerm->coef * bTerm->coef, aTerm->exp + bTerm->exp);
        }
        result = result + temp;
    }
    return result;
}

// 多項式求值
float Polynomial::Evaluate(float x) const {
    float sum = 0;
    Term* curr = head->link;
    while (curr != head) {
        sum += curr->coef * pow(x, curr->exp);
        curr = curr->link;
    }
    return sum;
}

// 主程式
int main() {
    Polynomial p1, p2;
    cout << "Enter Polynomial 1: ";
    cin >> p1;
    cout << "Enter Polynomial 2: ";
    cin >> p2;

    cout << "P1: " << p1 << endl;
    cout << "P2: " << p2 << endl;

    Polynomial sum = p1 + p2;
    cout << "P1 + P2 = " << sum << endl;

    Polynomial diff = p1 - p2;
    cout << "P1 - P2 = " << diff << endl;

    Polynomial prod = p1 * p2;
    cout << "P1 * P2 = " << prod << endl;

    float x;
    cout << "Enter x to evaluate P1: ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Evaluate(x) << endl;

    return 0;
}

```
## 效能分析

時間複雜度：

      插入（Attach）：O(1)
   
      加法運算：O(m + n)（兩多項式項數總和）

      輸入輸出：O(n)
   
      Evaluate：O(n)，每一項計算一次

空間複雜度：

      O(n)，儲存 n 個節點
      
## 測試與驗證

### 測試案例

```cpp
int main() {
    Polynomial p1, p2;
    cout << "Enter Polynomial 1: ";
    cin >> p1;
    cout << "Enter Polynomial 2: ";
    cin >> p2;

    cout << "P1: " << p1 << endl;
    cout << "P2: " << p2 << endl;

    Polynomial sum = p1 + p2;
    cout << "P1 + P2 = " << sum << endl;

    float x;
    cout << "Enter x to evaluate P1: ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Evaluate(x) << endl;

    return 0;
}

```
預期輸出

P1: 4x^3 + 2x^2 + 1

P2: 5x^2 + -3

P1 + P2 = 4x^3 + 7x^2 - 2

P1(2) = 4*8 + 2*4 + 1 = 45

## 申論及開發報告

### 使用的資料結構與演算法說明


一、使用的資料結構
   
       採用Circular Linked List以節省記憶體並支援高效刪除與插入操作。

       每一個節點 Term 包含係數、指數與下一個節點指標。

二、使用的演算法 

    多項式相加：採類似 Merge Sort 的策略，將兩串列同步走訪。

    Evaluate：計算每項 coef * x^exp 並累加。

    輸入/輸出：遵循題目格式處理 >> 和 << 運算子。

