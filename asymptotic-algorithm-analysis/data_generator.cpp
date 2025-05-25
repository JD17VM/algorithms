#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <sstream>
#include <cctype>

using namespace std;

const int MAX_BUFFER_SIZE = 256;

string generateDataForAlgorithm(const string& system_command,
                                 const string& max_size_arg,
                                 const string& algorithm_name) {
                                    
    string temp_data_filename = "temp_data_" + algorithm_name + ".dat";

    ostringstream command_ss;
    command_ss << system_command << " " << max_size_arg << " " << algorithm_name;
    string command = command_ss.str();

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "";
    }

    ofstream temp_data_file(temp_data_filename);
    if (!temp_data_file.is_open()) {
        pclose(pipe);
        return "";
    }

    char buffer_size[MAX_BUFFER_SIZE];
    char buffer_time[MAX_BUFFER_SIZE];

    while (fgets(buffer_size, sizeof(buffer_size), pipe) != nullptr) {
        if (fgets(buffer_time, sizeof(buffer_time), pipe) == nullptr) {
            break;
        }
        string line_size_str(buffer_size);
        string line_time_str(buffer_time);
        line_size_str.erase(line_size_str.find_last_not_of("\n\r") + 1);
        line_time_str.erase(line_time_str.find_last_not_of("\n\r") + 1);
        
        if (!line_size_str.empty() || !line_time_str.empty()) {
            temp_data_file << line_size_str << " " << line_time_str << endl;
        }
    }

    temp_data_file.close();
    pclose(pipe);
    return temp_data_filename;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Use: " << argv[0] << " <system_command> <max_size> <algorithm_name>" << endl;
        cerr << "Example: " << argv[0] << " main.py 200 insertion" << endl;
        return 1; 
    }

    string system_command = argv[1];
    string max_size_arg = argv[2];
    string algorithm_name_arg = argv[3];
    
    string temp_data_filename;
    
    temp_data_filename = generateDataForAlgorithm(system_command, max_size_arg, algorithm_name_arg);
    if (temp_data_filename.empty()) {
        cerr << "Error generating data for " << algorithm_name_arg << endl;
        return 1;
    }
    cout << "Data file generated: " << temp_data_filename << endl;

    return 0; 
}