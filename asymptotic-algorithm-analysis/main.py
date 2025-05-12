import random
import sys
import time
import copy

from algorithms import insertion_sort

def generate_random_data(size):
    return [random.randint(0, size * 10) for _ in range(size)]

def generate_worst_case_data(size):
    return list(range(size, 0, -1))

argv = sys.argv

max_size = int(argv[1])

start_size = 10
step = 10

num_repetitions = 100

sort_function = insertion_sort

for size in range(start_size, max_size + 1, step):
    data = generate_worst_case_data(size)
    #print(data)

    total_elapsed_time = 0

    for repetition in range(num_repetitions):
        data_to_sort = copy.deepcopy(data)

        start_time = time.time()
        sort_function(data_to_sort)
        end_time = time.time()

        total_elapsed_time += (end_time - start_time)

    average_elapsed_time = total_elapsed_time / num_repetitions

    print(size)
    print(average_elapsed_time)