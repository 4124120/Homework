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

class Term;

class Polynomial;

class Term {
    friend class Polynomial;
    friend ostream& operator<<(ostream&, Polynomial&);
    friend istream& operator>>(istream&, Polynomial&);

private:
    int coef;
    int exp;
    Term* link;
};

class Polynomial {
private:
    Term* head;

    void Attach(int coef, int exp) {
        Term* newTerm = new Term;
        newTerm->coef = coef;
        newTerm->exp = exp;
        newTerm->link = nullptr;

        Term* curr = head;
        while (curr->link && curr->link->exp > exp)
            curr = curr->link;

        newTerm->link = curr->link;
        curr->link = newTerm;
    }

public:
    Polynomial() {
        head = new Term;
        head->link = nullptr;
    }

    Polynomial(const Polynomial& a) {
        head = new Term;
        head->link = nullptr;
        Term* curr = a.head->link;
        while (curr) {
            Attach(curr->coef, curr->exp);
            curr = curr->link;
        }
    }

    ~Polynomial() {
        Term* curr = head;
        while (curr) {
            Term* temp = curr;
            curr = curr->link;
            delete temp;
        }
    }

    const Polynomial& operator=(const Polynomial& a) {
        if (this == &a) return *this;

        this->~Polynomial();
        head = new Term;
        head->link = nullptr;

        Term* curr = a.head->link;
        while (curr) {
            Attach(curr->coef, curr->exp);
            curr = curr->link;
        }
        return *this;
    }

    float Evaluate(float x) const {
        float result = 0.0;
        Term* curr = head->link;
        while (curr) {
            result += curr->coef * pow(x, curr->exp);
            curr = curr->link;
        }
        return result;
    }

    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        Term* aTerm = this->head->link;
        Term* bTerm = b.head->link;

        while (aTerm && bTerm) {
            if (aTerm->exp == bTerm->exp) {
                int sum = aTerm->coef + bTerm->coef;
                if (sum != 0) result.Attach(sum, aTerm->exp);
                aTerm = aTerm->link;
                bTerm = bTerm->link;
            } else if (aTerm->exp > bTerm->exp) {
                result.Attach(aTerm->coef, aTerm->exp);
                aTerm = aTerm->link;
            } else {
                result.Attach(bTerm->coef, bTerm->exp);
                bTerm = bTerm->link;
            }
        }

        while (aTerm) {
            result.Attach(aTerm->coef, aTerm->exp);
            aTerm = aTerm->link;
        }

        while (bTerm) {
            result.Attach(bTerm->coef, bTerm->exp);
            bTerm = bTerm->link;
        }

        return result;
    }

    Polynomial operator-(const Polynomial& b) const {
        Polynomial negB;
        Term* bTerm = b.head->link;
        while (bTerm) {
            negB.Attach(-bTerm->coef, bTerm->exp);
            bTerm = bTerm->link;
        }
        return *this + negB;
    }

    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        for (Term* aTerm = head->link; aTerm; aTerm = aTerm->link) {
            Polynomial temp;
            for (Term* bTerm = b.head->link; bTerm; bTerm = bTerm->link) {
                temp.Attach(aTerm->coef * bTerm->coef, aTerm->exp + bTerm->exp);
            }
            result = result + temp;
        }
        return result;
    }

    friend istream& operator>>(istream& is, Polynomial& x) {
        int n, coef, exp;
        is >> n;
        for (int i = 0; i < n; ++i) {
            is >> coef >> exp;
            x.Attach(coef, exp);
        }
        return is;
    }

    friend ostream& operator<<(ostream& os, Polynomial& x) {
        Term* curr = x.head->link;
        if (!curr) return os << "0";
        bool first = true;
        while (curr) {
            if (!first && curr->coef > 0)
                os << " + ";
            else if (curr->coef < 0)
                os << " - ";

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
};

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

