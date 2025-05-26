#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <functional>

#include "algorithms.h"

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

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <max_size> <algorithm_name>" << endl;
        return 1;
    }

    int max_size = stoi(argv[1]);
    string algorithm_name_str = argv[2];
    int start_size = 10;
    int step = 10;
    int num_repetitions = 100;

    function<void(vector<int>&)> sort_function;

    if (algorithm_name_str == "insertion") {
        sort_function = insertion_sort;
    } else if (algorithm_name_str == "merge") {
        sort_function = merge_sort;
    } else {
        cerr << "Unknown algorithm: " << argv[2] << endl;
        return 1;
    }

    for (int size = start_size; size <= max_size; size += step) {
        vector<int> data = generate_worst_case_data(size);
        
        double total_elapsed_time = 0;

        for (int repetition = 0; repetition < num_repetitions; ++repetition) {
            vector<int> data_to_sort = data;

            auto start_time = chrono::high_resolution_clock::now();
            sort_function(data_to_sort);
            auto end_time = chrono::high_resolution_clock::now();

            chrono::duration<double> elapsed = end_time - start_time;
            total_elapsed_time += elapsed.count();
        }

        double average_elapsed_time = total_elapsed_time / num_repetitions;

        cout << size << endl;
        cout << average_elapsed_time << endl;
    }

    return 0;
}