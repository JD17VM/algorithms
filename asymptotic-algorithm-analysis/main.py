import random

def generate_random_data(size):
    return [random.randint(0, size * 10) for _ in range(size)]

def generate_worst_case_data(size):
    return list(range(size, 0, -1))

max_size = 100

start_size = 10
step = 10

num_repetitions = 100

for size in range(start_size, max_size + 1, step):
    data = generate_worst_case_data(size)
    print(data)