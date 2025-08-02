# 41241207

作業二

## 解題說明

你需要完成 Polynomial 類別，其功能包含：

(1)多項式的表示與儲存（係數與指數）

(2)建構多項式物件（預設為 0）

(3)加法與乘法操作（Add / Mult）

(4)給定 x 值，求多項式的結果（Eval）

(5)重載 << 和 >>，方便輸入與輸出

### 解題策略

1. 資料結構設計：
   
   使用 Term 結構儲存一項（包含 coef、exp）。

   使用 Term* termArray 儲存多項式所有項。

   使用 capacity 控制 termArray 大小；terms 表示目前有效項數。
2. 核心功能實作：

   Add：兩個有序陣列合併（類似 merge sort）。

   Mult：雙層迴圈乘法後合併同指數項。

   Eval：逐項代入 x 並加總。

   輸入輸出：使用 operator>> 和 operator<< 重載。
3. 記憶體管理：
   
   建構子初始化 termArray。

   解構子釋放記憶體。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Polynomial;

class Term {
public:
    float coef;  // coefficient
    int exp;     // exponent
};

class Polynomial {
private:
    Term* termArray;
    int capacity;
    int terms;

    void NewTerm(float c, int e) {
        if (terms == capacity) {
            capacity *= 2;
            Term* temp = new Term[capacity];
            for (int i = 0; i < terms; ++i)
                temp[i] = termArray[i];
            delete[] termArray;
            termArray = temp;
        }
        termArray[terms].coef = c;
        termArray[terms++].exp = e;
    }

public:
    Polynomial(int cap = 10) {
        capacity = cap;
        terms = 0;
        termArray = new Term[capacity];
    }

    ~Polynomial() {
        delete[] termArray;
    }

    Polynomial Add(Polynomial b) {
        Polynomial c;
        int aPos = 0, bPos = 0;
        while (aPos < terms && bPos < b.terms) {
            if (termArray[aPos].exp == b.termArray[bPos].exp) {
                float sum = termArray[aPos].coef + b.termArray[bPos].coef;
                if (sum != 0)
                    c.NewTerm(sum, termArray[aPos].exp);
                aPos++, bPos++;
            } else if (termArray[aPos].exp > b.termArray[bPos].exp) {
                c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
                aPos++;
            } else {
                c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
                bPos++;
            }
        }

        for (; aPos < terms; aPos++)
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
        for (; bPos < b.terms; bPos++)
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
        return c;
    }

    Polynomial Mult(Polynomial b) {
        Polynomial c;
        for (int i = 0; i < terms; i++) {
            for (int j = 0; j < b.terms; j++) {
                float coef = termArray[i].coef * b.termArray[j].coef;
                int exp = termArray[i].exp + b.termArray[j].exp;
                bool found = false;

                for (int k = 0; k < c.terms; k++) {
                    if (c.termArray[k].exp == exp) {
                        c.termArray[k].coef += coef;
                        found = true;
                        break;
                    }
                }
                if (!found) c.NewTerm(coef, exp);
            }
        }
        return c;
    }

    float Eval(float f) {
        float result = 0;
        for (int i = 0; i < terms; i++) {
            result += termArray[i].coef * pow(f, termArray[i].exp);
        }
        return result;
    }

    friend istream& operator>>(istream& in, Polynomial& p) {
        cout << "Enter number of terms: ";
        in >> p.terms;
        p.termArray = new Term[p.terms];
        for (int i = 0; i < p.terms; i++) {
            cout << "Enter coef and exp: ";
            in >> p.termArray[i].coef >> p.termArray[i].exp;
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, Polynomial& p) {
        for (int i = 0; i < p.terms; i++) {
            out << p.termArray[i].coef << "x^" << p.termArray[i].exp;
            if (i != p.terms - 1)
                out << " + ";
        }
        return out;
    }
};

// ? 主函式：執行測試用例
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


```
## 效能分析

| 函數 | 時間複雜度 | 空間複雜度 | 分析說明 |
|----------|--------------|----------|----------|
| Add()  | O(n + m)     | O(n + m)        | 對兩個有序多項式進行合併，相當於 merge，最多產生 n + m 項結果。        |
| Mult()   | O(n × m)      | O(n × m)（最壞）        | 兩兩項相乘會產生 n × m 項，再合併同次方，最壞情況是所有次方不同。        |
| Eval(f)   | O(n)       | O(1)        | 每項都需做一次次方與乘法加總；空間上只需常數變數儲存結果與中間值。        |
| NewTerm()   | O(n)（擴容時）      | O(n)       | 若 termArray 滿，則需動態分配 2 倍大小，並複製所有項；否則是 O(1)       |
| operator>>   | O(n)     | O(n) | 使用者輸入 n 個項目時需建立新陣列儲存。 |
| Eval(f)   | O(n)       | O(1)        | 逐項輸出每個 term，不需額外儲存。        |
   
## 測試與驗證

### 測試案例

```cpp
int main() {
    Polynomial p1, p2;
    cout << "Enter first polynomial:\n";
    cin >> p1;
    cout << "Enter second polynomial:\n";
    cin >> p2;

    Polynomial sum = p1.Add(p2);
    Polynomial prod = p1.Mult(p2);

    cout << "P1: " << p1 << endl;
    cout << "P2: " << p2 << endl;
    cout << "Sum: " << sum << endl;
    cout << "Product: " << prod << endl;

    float x = 2.0;
    cout << "P1(" << x << ") = " << p1.Eval(x) << endl;
}
```
預期輸出

P1: 3x^2 + 2x^1

P2: 1x^2 + 4x^0

Sum: 4x^2 + 2x^1 + 4x^0

Product: 3x^4 + 2x^3 + 12x^2 + 8x^1

P1(2) = 16

## 申論及開發報告

### 使用的資料結構與演算法說明


一、使用的資料結構

(1)  結構化資料：Term 結構
   
       說明：每一項多項式由一個 Term 物件表示。

       欄位：

       float coef：係數（Coefficient）

       int exp：指數（Exponent）

       用途：便於儲存及操作多項式的每一項，例如：3x² 的 coef = 3，exp = 2。

(2)  動態陣列：Term* termsArray
   
       說明：使用動態記憶體配置的陣列來儲存所有項。

       優點：

       可動態擴充項數，節省記憶體。

       便於實作合併（加法）、搜尋、輸出等功能。
    
       注意事項：需控制容量與記憶體釋放以避免記憶體洩漏。

(3)  類別包裝：Polynomial 類別
   
       屬性：

       int terms：實際項數

       int capacity：目前陣列容量

       Term* termsArray：儲存所有項的指標

       用途：封裝所有多項式邏輯操作，方便管理與擴充。

二、使用的演算法

(1)  多項式加法（Add() 方法） 

    核心想法：類似合併排序中的 Merge 步驟。

    流程：

    初始化兩個指標 i, j 分別指向兩個多項式的第一項。

    比較 exp 大小，較大者直接加入結果。

    若 exp 相同，則合併係數後加入結果（若係數和非 0）。

    繼續直到兩方都走完。

    時間複雜度：O(n + m)（n 與 m 為兩個多項式的項數）

(2)  新增項（newTerm() 方法）
    用途：新增一項多項式項目至陣列。

    流程：

    檢查是否超出容量，若超出則擴充記憶體（double capacity）。

    將新項加入 termsArray。

    時間複雜度：O(1) 均攤（Amortized）

(3)  多項式輸出（output() 方法）
    用途：印出所有項次，格式化為數學表示。

    演算法：依照陣列順序逐項印出，特別處理正負號與指數為 0 或 1 的情況。

    時間複雜度：O(n)

(4)  多項式求值（Eval() 方法）
    用途：代入變數 x 值，求整體多項式的值。

    演算法：

    每一項套用公式：coef * pow(x, exp)

    累加結果

    時間複雜度：O(n)，但注意 pow() 本身時間複雜度為 O(log e)
    
三、

| 設計原則 | 實作對應                     |
| ---- | ------------------------ |
| 資料封裝 | `Polynomial` 類別封裝所有操作與資料 |
| 空間效率 | 使用動態陣列，避免固定大小浪費空間        |
| 時間效率 | 採 Merge 策略進行加法，加快處理      |
| 可擴充性 | 支援更多操作（如乘法、微分）可持續擴展      |
    
