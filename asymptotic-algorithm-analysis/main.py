import random

def generate_random_data(size):
    return [random.randint(0, size * 10) for _ in range(size)]

def generate_worst_case_data(size):
    return list(range(size, 0, -1))

print(generate_random_data(10))
print(generate_worst_case_data(10))