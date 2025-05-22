<p align="center">
<img alt="GitHub Repo stars" src="https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54" />
<img alt="GitHub Repo stars" src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
</p>

# **Execution**

## Compilation of the Plot Generator:
Create the executable program responsible for managing the benchmarking and plotting.

```Bash
g++ plot_generator.cpp -o plot_generator
```

## Program Invocation:
Execute the `plot_generator` program from the terminal. It requires specific command-line arguments: 

- The script that performs the algorithm testing, 
- The maximum data size for the benchmark
- The name of the algorithm being analyzed.

```Bash
./plot_generator main.py 100 insertion
```

Upon successful execution, a PNG graphimage graph will be generated in the current directory (`insertion_performance_plot.png`).