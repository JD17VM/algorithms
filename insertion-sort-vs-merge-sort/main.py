import sys
import time
import random
import copy

from algorithms import insertion_sort, merge_sort

def generate_random_data(size):
    return [random.randint(0, size * 10) for _ in range(size)]

def generate_worst_case_data(size):
    return list(range(size, 0, -1))

argv = sys.argv
#argv = [0,1000,"insertion"]

if __name__ == "__main__":

    
    max_size = int(argv[1])
    algorithm_name = argv[2].lower()

    if algorithm_name == "insertion":
        sort_function = insertion_sort
    elif algorithm_name == "merge":
        sort_function = merge_sort

    start_size = 10
    step = 10 

    for size in range(start_size, max_size + 1, step):
        data = generate_worst_case_data(size)
        #print(data)

        data_to_sort = copy.deepcopy(data)

        start_time = time.time()
        sorted_data = sort_function(data_to_sort)
        end_time = time.time()

        elapsed_time = end_time - start_time #tr

        print(size)
        print(elapsed_time)