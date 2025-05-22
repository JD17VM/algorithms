#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <sstream>
#include <cctype>
#include <cstdlib> 
#include <cstring> 
#include <cerrno>   

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
        cerr << "Error al ejecutar el script de Python para " << algorithm_name
             << " con popen: " << strerror(errno) << endl;
        return ""; 
    }

    ofstream temp_data_file(temp_data_filename);
    if (!temp_data_file.is_open()) {
        cerr << "Error al abrir el archivo de datos temporal: " << temp_data_filename << endl;
        pclose(python_pipe);
        return ""; 
    }

    cout << "Leyendo datos del script de Python para el algoritmo: " << algorithm_name << "..." << endl;
    char buffer_size[MAX_BUFFER_SIZE];
    char buffer_time[MAX_BUFFER_SIZE];
    int data_points_count = 0;

    while (fgets(buffer_size, sizeof(buffer_size), python_pipe) != nullptr) {
        if (fgets(buffer_time, sizeof(buffer_time), python_pipe) == nullptr) {
            cerr << "Advertencia: Se esperaba un tiempo después del tamaño para " << algorithm_name << "." << endl;
            break;
        }
        string line_size_str(buffer_size);
        string line_time_str(buffer_time);
        line_size_str.erase(line_size_str.find_last_not_of("\n\r") + 1);
        line_time_str.erase(line_time_str.find_last_not_of("\n\r") + 1);
        if (!line_size_str.empty() || !line_time_str.empty()) {
            temp_data_file << line_size_str << " " << line_time_str << endl;
            data_points_count++;
        }
    }

    temp_data_file.close();
    int python_status = pclose(python_pipe);

    if (python_status == -1) {
         cerr << "Error al cerrar la tubería de Python para " << algorithm_name << " (pclose falló)." << endl;
         remove(temp_data_filename.c_str());
         return "";
    }

    if (data_points_count == 0) {
        cerr << "No se leyeron datos del script de Python para " << algorithm_name << "." << endl;
        remove(temp_data_filename.c_str());
        return "";
    }

    cout << "Datos para " << algorithm_name << " guardados en " << temp_data_filename << endl;
    return temp_data_filename;
}



int main(int argc, char *argv[]) {
    if (argc < 4 || argc > 5) {
        cerr << "Uso para un solo algoritmo: " << argv[0] << " <script_python.py> <tamano_max> <nombre_algoritmo>" << endl;
        cerr << "Uso para comparar dos algoritmos: " << argv[0] << " <script_python.py> <tamano_max> <algoritmo1> <algoritmo2>" << endl;
        cerr << "Ejemplo un solo algoritmo: " << argv[0] << " main.py 200 insertion" << endl;
        cerr << "Ejemplo comparación: " << argv[0] << " main.py 200 insertion merge" << endl;
        return EXIT_FAILURE; 
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

    string plot_output_filename;
    string temp_data_file1_name;
    string temp_data_file2_name;


    string display_algorithm1_name = algorithm1_name_arg;
    if (!display_algorithm1_name.empty()) {
        display_algorithm1_name[0] = static_cast<char>(toupper(static_cast<unsigned char>(display_algorithm1_name[0])));
    }

    string display_algorithm2_name = ""; 
    if (comparison_mode) {
        display_algorithm2_name = algorithm2_name_arg;
        if (!display_algorithm2_name.empty()) {
            display_algorithm2_name[0] = static_cast<char>(toupper(static_cast<unsigned char>(display_algorithm2_name[0])));
        }
    }
    

    temp_data_file1_name = generarDatosParaAlgoritmo(python_script_name, max_size_arg, algorithm1_name_arg);
    if (temp_data_file1_name.empty()) {
        cerr << "No se pudieron generar los datos para " << algorithm1_name_arg << ". Abortando." << endl;
        return EXIT_FAILURE;
    }

    if (comparison_mode) {
        temp_data_file2_name = generarDatosParaAlgoritmo(python_script_name, max_size_arg, algorithm2_name_arg);
        if (temp_data_file2_name.empty()) {
            cerr << "No se pudieron generar los datos para " << algorithm2_name_arg << ". Abortando." << endl;
            remove(temp_data_file1_name.c_str()); // Limpiar el primer archivo si el segundo falla
            return EXIT_FAILURE;
        }
    }


    ostringstream gnuplot_commands_ss; 

    if (comparison_mode) {
        plot_output_filename = "comparison_" + algorithm1_name_arg + "_vs_" + algorithm2_name_arg + "_plot.png";
        gnuplot_commands_ss << "set title 'Comparación: " << display_algorithm1_name << " Sort vs " 
                            << display_algorithm2_name << " Sort (Worst-Case)'\n";
        gnuplot_commands_ss << "plot '" << temp_data_file1_name
                            << "' using 1:2 with linespoints title '" << display_algorithm1_name 
                            << "' lc rgb 'blue' pt 7 ps 1, \\\n     '" << temp_data_file2_name 
                            << "' using 1:2 with linespoints title '" 
                            << (algorithm1_name_arg == algorithm2_name_arg ? display_algorithm2_name + " (2)" : display_algorithm2_name) 
                            << "' lc rgb 'red' pt 5 ps 1\n";
    } else {
        plot_output_filename = algorithm1_name_arg + "_performance_plot.png";
        gnuplot_commands_ss << "set title '" << display_algorithm1_name << " Sort Performance (Worst-Case)'\n";
        gnuplot_commands_ss << "plot '" << temp_data_file1_name
                            << "' using 1:2 with linespoints title '" << display_algorithm1_name 
                            << "' lc rgb 'blue' pt 7 ps 1\n";
    }

    ostringstream gnuplot_common_setup_ss;
    gnuplot_common_setup_ss << "set terminal pngcairo size 1024,768 enhanced font 'Verdana,10'\n";
    gnuplot_common_setup_ss << "set output '" << plot_output_filename << "'\n";
    gnuplot_common_setup_ss << "set xlabel 'Tamaño de Entrada (N)'\n";
    gnuplot_common_setup_ss << "set ylabel 'Tiempo Promedio (segundos)'\n";
    gnuplot_common_setup_ss << "set grid\n";
    gnuplot_common_setup_ss << "set key top left\n";
    gnuplot_common_setup_ss << "set logscale y\n";
    
    string final_gnuplot_script = gnuplot_common_setup_ss.str() + gnuplot_commands_ss.str() + "exit\n";
    
    FILE* gnuplot_pipe = popen("gnuplot", "w");
    if (!gnuplot_pipe) {
        cerr << "Error al abrir gnuplot con popen: " << strerror(errno) << endl;
        remove(temp_data_file1_name.c_str());
        if (comparison_mode && !temp_data_file2_name.empty()) {
            remove(temp_data_file2_name.c_str());
        }
        return EXIT_FAILURE;
    }

    cout << "Generando gráfica con gnuplot (" << plot_output_filename <<")..." << endl;
    fprintf(gnuplot_pipe, "%s", final_gnuplot_script.c_str());
    fflush(gnuplot_pipe);
    
    int gnuplot_status = pclose(gnuplot_pipe);
    if (gnuplot_status == -1) {
        cerr << "Advertencia: gnuplot pudo haber tenido problemas (pclose status: " << gnuplot_status << ")." << endl;
    }

    cout << "Gráfica generada (o intentada): " << plot_output_filename << endl;

    remove(temp_data_file1_name.c_str());
    if (comparison_mode && !temp_data_file2_name.empty()) {
        remove(temp_data_file2_name.c_str());
    }

    return EXIT_SUCCESS; 
}