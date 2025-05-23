#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <sstream>
#include <cctype>

using namespace std;

const int MAX_BUFFER_SIZE = 256;

string generarDatosParaAlgoritmo(const string& python_script_name,
                                 const string& max_size_arg,
                                 const string& algorithm_name) {
    string temp_data_filename = "temp_data_" + algorithm_name + ".dat";

    ostringstream python_command_ss;
    python_command_ss << "python " << python_script_name << " " << max_size_arg << " " << algorithm_name;
    string python_command = python_command_ss.str();

    FILE* python_pipe = popen(python_command.c_str(), "r");
    if (!python_pipe) {
        return "";
    }

    ofstream temp_data_file(temp_data_filename);
    if (!temp_data_file.is_open()) {
        pclose(python_pipe);
        return "";
    }

    char buffer_size[MAX_BUFFER_SIZE];
    char buffer_time[MAX_BUFFER_SIZE];

    while (fgets(buffer_size, sizeof(buffer_size), python_pipe) != nullptr) {
        if (fgets(buffer_time, sizeof(buffer_time), python_pipe) == nullptr) {
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
    pclose(python_pipe);
    return temp_data_filename;
}

int main(int argc, char *argv[]) {
    if (argc < 4 || argc > 5) {
        cerr << "Uso para un solo algoritmo: " << argv[0] << " <script_python.py> <tamano_max> <nombre_algoritmo>" << endl;
        cerr << "Uso para comparar dos algoritmos: " << argv[0] << " <script_python.py> <tamano_max> <algoritmo1> <algoritmo2>" << endl;
        cerr << "Ejemplo un solo algoritmo: " << argv[0] << " main.py 200 insertion" << endl;
        cerr << "Ejemplo comparación: " << argv[0] << " main.py 200 insertion merge" << endl;
        return 1; 
    }

    string python_script_name = argv[1];
    string max_size_arg = argv[2];
    
    string algorithm1_name_arg = argv[3];
    string algorithm2_name_arg = "";
    bool comparison_mode = false;

    if (argc == 5) {
        algorithm2_name_arg = argv[4];
        comparison_mode = true;
    }

    string temp_data_file1_name;
    string temp_data_file2_name;
    
    temp_data_file1_name = generarDatosParaAlgoritmo(python_script_name, max_size_arg, algorithm1_name_arg);
    if (temp_data_file1_name.empty()) {
        cerr << "Error generando datos para " << algorithm1_name_arg << endl;
        return 1;
    }
    cout << "Archivo de datos generado: " << temp_data_file1_name << endl;

    if (comparison_mode) {
        temp_data_file2_name = generarDatosParaAlgoritmo(python_script_name, max_size_arg, algorithm2_name_arg);
        if (temp_data_file2_name.empty()) {
            cerr << "Error generando datos para " << algorithm2_name_arg << endl;
            return 1;
        }
        cout << "Archivo de datos generado: " << temp_data_file2_name << endl;
    }

    return 0; 
}