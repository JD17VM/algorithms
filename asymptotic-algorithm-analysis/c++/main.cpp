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

void print_int_vector(const vector<int> vector){
    for (int number : vector) {
        cout << number << " ";
    }
}

int main() {

    int max_size = 100;
    int start_size = 10;
    int step = 10;
    int num_repetitions = 100;

    for (int size = start_size; size <= max_size; size += step) {
        vector<int> data = generate_worst_case_data(size);
        print_int_vector(data);
        cout<<endl;
    }

    return 0;
}