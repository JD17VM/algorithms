#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

vector<int> generate_random_data(int size) {
    srand(time(0));

    vector<int> data;
    data.reserve(size);
    for (int i = 0; i < size; ++i) {
        data.push_back(rand() % (size * 10 + 1));
    }
    return data;
}

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
    //vector<int> data = generate_worst_case_data(size);
    vector<int> data = generate_random_data(size);

    for (int number : data) {
        cout << number << " ";
    }

    return 0;
}