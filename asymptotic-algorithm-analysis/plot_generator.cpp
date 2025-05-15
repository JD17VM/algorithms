#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>   // Para popen, pclose, fprintf
#include <sstream>  // Para ostringstream
#include <cctype>   // Para toupper

using namespace std;

const string TEMP_DATA_FILENAME = "temp_plot_data.dat";
const int MAX_BUFFER_SIZE = 256;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "Uso: " << argv[0] << " <script_python.py> <tamano_max> <nombre_algoritmo>" << endl;
        cerr << "Ejemplo: " << argv[0] << " main.py 200 insertion" << endl;
        return 0;
    }

    string python_script_name = argv[1];
    string max_size_arg = argv[2];
    string algorithm_name_arg = argv[3];

    string plot_output_filename = algorithm_name_arg + "_performance_plot.png";

    // 1. Construir y ejecutar el comando de Python
    ostringstream python_command_ss;
    python_command_ss << "python " << python_script_name << " " << max_size_arg << " " << algorithm_name_arg;
    string python_command = python_command_ss.str();

    FILE* python_pipe = popen(python_command.c_str(), "r");

    // 2. Abrir archivo temporal para los datos
    ofstream temp_data_file(TEMP_DATA_FILENAME);

    cout << "Reading data from Python script..." << endl;
    char buffer_size[MAX_BUFFER_SIZE];
    char buffer_time[MAX_BUFFER_SIZE];

    // Leer la salida del script de Python (tamaño y tiempo en líneas alternas)
    while (fgets(buffer_size, sizeof(buffer_size), python_pipe) != nullptr) {
        fgets(buffer_time, sizeof(buffer_time), python_pipe);

        string line_size_str(buffer_size);
        string line_time_str(buffer_time);

        // Eliminar caracteres de nueva línea
        line_size_str.erase(line_size_str.find_last_not_of("\n\r") + 1);
        line_time_str.erase(line_time_str.find_last_not_of("\n\r") + 1);

        temp_data_file << line_size_str << " " << line_time_str << endl;
    }

    temp_data_file.close();
    pclose(python_pipe);

    cout << "Formatted data saved to " << TEMP_DATA_FILENAME << endl;

    // 3. Llamar a gnuplot para generar la gráfica
    FILE* gnuplot_pipe = popen("gnuplot", "w");

    cout << "Generating graph with gnuplot..." << endl;

    ostringstream gnuplot_commands_ss;
    gnuplot_commands_ss << "set terminal pngcairo size 1024,768 enhanced font 'Verdana,10'\n";
    gnuplot_commands_ss << "set output '" << plot_output_filename << "'\n";

    string display_algorithm_name = algorithm_name_arg;
    // Comprobación para que el nombre del algoritmo tenga la primera letra en mayúscula.
    if (!display_algorithm_name.empty()) {
        display_algorithm_name[0] = static_cast<char>(toupper(static_cast<unsigned char>(display_algorithm_name[0])));
    }
    gnuplot_commands_ss << "set title '" << display_algorithm_name << "Sort Performance (Wors-Case)'\n";

    gnuplot_commands_ss << "set xlabel 'Input Size (N)'\n";
    gnuplot_commands_ss << "set ylabel 'Average Time (seconds)'\n";
    gnuplot_commands_ss << "set grid\n";
    gnuplot_commands_ss << "set key top left\n";
    gnuplot_commands_ss << "set logscale y\n";
    gnuplot_commands_ss << "plot '" << TEMP_DATA_FILENAME
                        << "' using 1:2 with linespoints title 'Measured Time' lc rgb 'blue' pt 7 ps 1\n";
    gnuplot_commands_ss << "exit\n";

    fprintf(gnuplot_pipe, "%s", gnuplot_commands_ss.str().c_str());
    fflush(gnuplot_pipe);
    pclose(gnuplot_pipe);

    cout << "Graph Generated: " << plot_output_filename << endl;

    return 0;
}