#include <iostream>
#include <vector>

using namespace std;

// ���j�禡
void generatePowerSet(const vector<char>& set, vector< vector<char> >& result, vector<char>& current, int index) {
    if (index == set.size()) {
        result.push_back(current);
        return;
    }

    // ���]�t��e����
    generatePowerSet(set, result, current, index + 1);

    // �]�t��e����
    current.push_back(set[index]);
    generatePowerSet(set, result, current, index + 1);
    current.pop_back(); // �^��
}

// �ʸ˨��
vector< vector<char> > powerSet(const vector<char>& set) {
    vector< vector<char> > result;
    vector<char> current;
    generatePowerSet(set, result, current, 0);
    return result;
}

// �D�{��
int main() {
    char arr[] = {'a', 'b', 'c'};
    vector<char> input(arr, arr + 3);  // �ΰ}�C�� vector�A�ݮe C++98

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

