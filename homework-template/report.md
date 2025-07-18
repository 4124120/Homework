# 41241207

作業一

## 解題說明

本題要求撰寫一個遞迴函數來計算這個函數的值，和撰寫一個非遞迴演算法來計算 Ackermann 函數。

### 解題策略

1. 先實作「簡單的遞迴」確認邏輯正確。
2. 再設計「非遞迴」版本，利用 stack 模擬遞迴呼叫流程。  
3. 測試小數字，再測試極限輸入值。
4. 比較執行時間與效能差異。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
using namespace std;

// 遞迴版 Ackermann 函數
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
    cout << "請輸入 m 與 n：";
    cin >> m >> n;

    int result = ackermann_recursive(m, n);
    cout << "Ackermann(" << m << ", " << n << ") = " << result << endl;

    return 0;
}
```

```
#include <iostream>
#include <stack>
using namespace std;

// 非遞迴版 Ackermann 函數，使用 stack 模擬遞迴
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
    cout << "請輸入 m 與 n：";
    cin >> m >> n;

    int result = ackermann_nonrecursive(m, n);
    cout << "Ackermann(" << m << ", " << n << ") = " << result << endl;

    return 0;
}
```
## 效能分析

1. 時間複雜度：O(n)，其中 n 為 nums 陣列的長度。
2. 空間複雜度：O(1)，為常數空間。
   
## 測試與驗證

### 測試案例

| 測試案例 | 輸入m n | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | 0 0     | 1        | 1        |
| 測試二   | 1 2      | 4        | 4        |
| 測試三   | 2 2       | 7        | 7        |
| 測試四   | 3 2      | 29       | 29       |
| 測試五   | 4 1     | 程式在 8 秒後錯誤結束，錯誤碼為 3221225725 | 程式在 8 秒後錯誤結束，錯誤碼為 3221225725 |

### 編譯與執行指令

```shell
# 編譯遞迴版
g++ ackermann_recursive.cpp -o ack_r
./ack_r

# 編譯非遞迴版
g++ ackermann_nonrecursive.cpp -o ack_nr
./ack_nr

```

### 結論

1. 遞迴版若 m 與 n 較大，會造成 stack overflow。  
2. 非遞迴版可以處理更深層數，但運算時間仍會爆炸成長。  
3. 測試 m ≤ 3，n ≤ 5。

## 申論及開發報告

### 使用的資料結構與演算法說明


1. **遞迴版 Ackermann 函數**  
   ```cpp
   int ackermann_recursive(int m, int n) {
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return ackermann_recursive(m - 1, 1);
    else
        return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
   }
   ```
   使用的演算法：純遞迴，符合數學定義
    
   程式簡潔，邏輯清楚
     使用 if-else 直接實作數學公式。
     每一層呼叫對應數學公式的一層嵌套。

   缺點：容易爆堆疊
     例如 A(4,1) 就需要數千次遞迴，容易導致 stack overflow 錯誤。

2. **非遞迴版 Ackermann 函數**  
   ```cpp
   int ackermann_nonrecursive(int m, int n) {
    stack<int> s;
    s.push(m);
    while (!s.empty()) {
        m = s.top(); s.pop();
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

   ```
   使用的演算法：堆疊（Stack）模擬遞迴
    
   模擬系統呼叫堆疊
     使用 stack<int> 來模擬遞迴過程中函數的呼叫順序。

   避免 Stack Overflow
     對於較大 m, n 的輸入能更好地防止記憶體爆掉。

   實作難度較高

   
   
作業二

## 解題說明

本題要求輸入一個集合 S，請以遞迴方式計算其 Power Set，也就是所有子集合的集合。

### 解題策略

遞迴包含/不包含

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>

using namespace std;

// 遞迴函式
void generatePowerSet(const vector<char>& set, vector< vector<char> >& result, vector<char>& current, int index) {
    if (index == set.size()) {
        result.push_back(current);
        return;
    }

    // 不包含當前元素
    generatePowerSet(set, result, current, index + 1);

    // 包含當前元素
    current.push_back(set[index]);
    generatePowerSet(set, result, current, index + 1);
    current.pop_back(); // 回溯
}

// 封裝函數
vector< vector<char> > powerSet(const vector<char>& set) {
    vector< vector<char> > result;
    vector<char> current;
    generatePowerSet(set, result, current, 0);
    return result;
}

// 主程式
int main() {
    char arr[] = {'a', 'b', 'c'};
    vector<char> input(arr, arr + 3);  // 用陣列轉 vector，兼容 C++98

    vector< vector<char> > subsets = powerSet(input);

    cout << "Power Set:\n";
    for (int i = 0; i < subsets.size(); ++i) {
        cout << "{";
        for (int j = 0; j < subsets[i].size(); ++j) {
            cout << subsets[i][j];
        }
        cout << "}\n";
    }

    return 0;
}

```

## 效能分析

1. 時間複雜度：O(2n) 子集合數量為 2^n，每個都需要構建。
2. 空間複雜度：O(n⋅2 n) 儲存所有子集合（每個最多 n 元素）。
   
## 測試與驗證

### 測試案例

| 測試輸入| 輸出子集合數 | 子集合（部分） |
|----------|--------------|----------|
| { }   | 1     | { }       |
| {'a'}   | 2      | { }  {'a'}      | 
| {'a', 'b'}   | 4       | { }  {'a'} {'b'} {'a', 'b'}      | 
| {'x', 'y', 'z'}  |8      | 共 8 種組合       | 

### 編譯與執行指令

```
g++ -std=c++11 powerset.cpp -o powerset
./powerse

```

## 申論及開發報告

### 使用的資料結構與演算法說明

1. 問題定義與需求說明

   輸入格式：一個集合（例如 {'a', 'b', 'c'}）
   
   輸出格式：所有可能子集合，包含空集合與完整集合

2. 使用的資料結構
   
   std::vector<char>：表示輸入集合
   
   std::vector< std::vector<char> >：儲存所有子集合

   輔助變數 current（vector<char>）

3. 使用的演算法：遞迴 + 回溯法

   這是一個典型的遞迴樹狀結構問題，產生一棵二元遞迴決策樹
```
         []
       /    \
     [a]    []
    /   \   /  \
  [a,b] [a] [b] []
```

```
 [void generatePowerSet(set, result, current, index)
    if index == set.size:
        result.push_back(current)
        return

    // 不選擇當前元素
    generatePowerSet(set, result, current, index + 1)

    // 選擇當前元素
    current.push_back(set[index])
    generatePowerSet(set, result, current, index + 1)
    current.pop_back() // 回溯

```    
