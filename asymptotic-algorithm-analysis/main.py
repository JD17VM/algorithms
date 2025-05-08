import random
import sys

def generate_random_data(size):
    return [random.randint(0, size * 10) for _ in range(size)]

def generate_worst_case_data(size):
    return list(range(size, 0, -1))

argv = sys.argv

max_size = int(argv[1])

start_size = 10
step = 10

num_repetitions = 100

for size in range(start_size, max_size + 1, step):
    data = generate_worst_case_data(size)
    print(data)