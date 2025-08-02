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

class Polynomial; // forward declaration

class Term {
    friend class Polynomial;
    friend ostream& operator<<(ostream& os, Polynomial& x);
    friend istream& operator>>(istream& is, Polynomial& x);
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
    const Polynomial& operator=(const Polynomial& a);
    Polynomial operator+(const Polynomial& b) const;
    Polynomial operator-(const Polynomial& b) const;
    Polynomial operator*(const Polynomial& b) const;
    float Evaluate(float x) const;
    friend istream& operator>>(istream& is, Polynomial& x);
    friend ostream& operator<<(ostream& os, Polynomial& x);

private:
    Term* head;
    void Attach(int coef, int exp);
    void Clear();
};

Polynomial::Polynomial() {
    head = new Term;
    head->link = head;
}

Polynomial::Polynomial(const Polynomial& a) {
    head = new Term;
    head->link = head;
    Term* curr = a.head->link;
    while (curr != a.head) {
        Attach(curr->coef, curr->exp);
        curr = curr->link;
    }
}

Polynomial::~Polynomial() {
    Clear();
    delete head;
}

void Polynomial::Clear() {
    Term* curr = head->link;
    while (curr != head) {
        Term* temp = curr;
        curr = curr->link;
        delete temp;
    }
    head->link = head;
}

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

void Polynomial::Attach(int coef, int exp) {
    Term* newTerm = new Term;
    newTerm->coef = coef;
    newTerm->exp = exp;
    newTerm->link = head;

    Term* curr = head;
    while (curr->link != head) curr = curr->link;
    curr->link = newTerm;
}

Polynomial Polynomial::operator+(const Polynomial& b) const {
    Polynomial result;
    Term* aPtr = head->link;
    Term* bPtr = b.head->link;
    while (aPtr != head && bPtr != b.head) {
        if (aPtr->exp == bPtr->exp) {
            int sum = aPtr->coef + bPtr->coef;
            if (sum != 0)
                result.Attach(sum, aPtr->exp);
            aPtr = aPtr->link;
            bPtr = bPtr->link;
        } else if (aPtr->exp > bPtr->exp) {
            result.Attach(aPtr->coef, aPtr->exp);
            aPtr = aPtr->link;
        } else {
            result.Attach(bPtr->coef, bPtr->exp);
            bPtr = bPtr->link;
        }
    }
    while (aPtr != head) {
        result.Attach(aPtr->coef, aPtr->exp);
        aPtr = aPtr->link;
    }
    while (bPtr != b.head) {
        result.Attach(bPtr->coef, bPtr->exp);
        bPtr = bPtr->link;
    }
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& b) const {
    Polynomial result;
    Term* aPtr = head->link;
    Term* bPtr = b.head->link;
    while (aPtr != head && bPtr != b.head) {
        if (aPtr->exp == bPtr->exp) {
            int diff = aPtr->coef - bPtr->coef;
            if (diff != 0)
                result.Attach(diff, aPtr->exp);
            aPtr = aPtr->link;
            bPtr = bPtr->link;
        } else if (aPtr->exp > bPtr->exp) {
            result.Attach(aPtr->coef, aPtr->exp);
            aPtr = aPtr->link;
        } else {
            result.Attach(-bPtr->coef, bPtr->exp);
            bPtr = bPtr->link;
        }
    }
    while (aPtr != head) {
        result.Attach(aPtr->coef, aPtr->exp);
        aPtr = aPtr->link;
    }
    while (bPtr != b.head) {
        result.Attach(-bPtr->coef, bPtr->exp);
        bPtr = bPtr->link;
    }
    return result;
}

Polynomial Polynomial::operator*(const Polynomial& b) const {
    Polynomial result;
    for (Term* aPtr = head->link; aPtr != head; aPtr = aPtr->link) {
        Polynomial temp;
        for (Term* bPtr = b.head->link; bPtr != b.head; bPtr = bPtr->link) {
            temp.Attach(aPtr->coef * bPtr->coef, aPtr->exp + bPtr->exp);
        }
        result = result + temp;
    }
    return result;
}

float Polynomial::Evaluate(float x) const {
    float sum = 0;
    for (Term* curr = head->link; curr != head; curr = curr->link) {
        sum += curr->coef * pow(x, curr->exp);
    }
    return sum;
}

istream& operator>>(istream& is, Polynomial& x) {
    int n, coef, exp;
    is >> n;
    for (int i = 0; i < n; ++i) {
        is >> coef >> exp;
        x.Attach(coef, exp);
    }
    return is;
}

ostream& operator<<(ostream& os, Polynomial& x) {
    Term* curr = x.head->link;
    if (curr == x.head) {
        os << "0";
        return os;
    }
    bool first = true;
    while (curr != x.head) {
        if (!first && curr->coef > 0)
            os << " + ";
        else if (curr->coef < 0)
            os << " - ";
        else if (!first)
            os << " ";

        if (abs(curr->coef) != 1 || curr->exp == 0)
            os << abs(curr->coef);
        if (curr->exp != 0) {
            os << "x";
            if (curr->exp != 1)
                os << "^" << curr->exp;
        }
        first = false;
        curr = curr->link;
    }
    return os;
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
    Polynomial p1, p2, sum, diff, prod;
    cout << "Enter first polynomial (format: n c1 e1 c2 e2 ...): ";
    cin >> p1;
    cout << "Enter second polynomial (same format): ";
    cin >> p2;

    sum = p1 + p2;
    diff = p1 - p2;
    prod = p1 * p2;

    cout << "\nP1(x) = " << p1 << endl;
    cout << "P2(x) = " << p2 << endl;
    cout << "P1(x) + P2(x) = " << sum << endl;
    cout << "P1(x) - P2(x) = " << diff << endl;
    cout << "P1(x) * P2(x) = " << prod << endl;

    float x;
    cout << "Enter a value of x to evaluate P1(x): ";
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

