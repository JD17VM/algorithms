#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> generate_worst_case_data(int size) {
    vector<int> data;
    data.reserve(size);
    for (int i = size; i > 0; --i) {
        data.push_back(i);
    }
    return data;
}

int main() {
    int size = 200;

    vector<int> data = generate_worst_case_data(size);

    for (int number : data) {
        cout << number << " ";
    }

    return 0;
}