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

