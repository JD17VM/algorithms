<p align="center">
<img alt="GitHub Repo stars" src="https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54" />
<img alt="GitHub Repo stars" src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
<img alt="GitHub Repo stars" src="https://img.shields.io/badge/bash_script-%23121011.svg?style=for-the-badge&logo=gnu-bash&logoColor=white" />
</p>

# **Execution**

## Step 1: Generating Performance Data (.dat file)

### Compilation of the Data Generator:

```Bash
g++ data_generator.cpp -o data_generator
```

### Data Generation Invocation:

- The script that performs the algorithm testing, 
- The maximum data size for the benchmark
- The name of the algorithm being analyzed.

**Python**

```Bash
./data_generator "python python/main.py" 500 insertion
```

**C++**

```Bash
./data_generator "c++\main.exe" 500 insertion
```

## Step 2: Generating the Plot Image (Bash Script)

This step uses the Bash script plot_algorithm_performance.sh to take the `.dat` file generated in Step 1 and create a visual plot using Gnuplot.

### Script Invocation:

Execute the `plot_algorithm_performance.sh` script from the terminal. It requires two command-line arguments (or four if comparing two algorithms):

1. The path to the input .dat file (generated in Step 1).
2. The name of the algorithm (this helps in naming the output plot and its title).

```
./plot_algorithm_performance.sh temp_data_insertion.dat insertion
```

```
./plot_algorithm_performance.sh temp_data_insertion.dat insertion temp_data_merge.dat merge
```

Upon successful execution, a PNG image of the graph will be generated in the current directory (e.g., `insertion_performance_plot.png` or `comparison_insertion_vs_merge_plot.png`).

> [!CAUTION]
>**Bash Script (`.sh`) Execution**
>* **Linux & macOS:** Runs natively. Ensure it's executable (e.g., `chmod +x plot_algorithm_performance.sh`) before running.
>* **Windows:** This script will not run in the standard Command Prompt (CMD) or PowerShell. It requires a Bash environment.
> 
> **Recommended for Windows:** Use Git Bash (commonly bundled with Git for Windows) or Windows Subsystem for Linux (WSL).