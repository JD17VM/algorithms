def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i] 
        j = i - 1    

        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key 

    return arr 


def merge(A, p, q, r):
    nL = q - p + 1
    nR = r - q

    L = [0] * nL
    R = [0] * nR

    for i in range(nL):
        L[i] = A[p + i]
    for j in range(nR):
        R[j] = A[q + 1 + j]

    i = 0
    j = 0
    k = p

    while i < nL and j < nR:
        if L[i] <= R[j]:
            A[k] = L[i]
            i += 1
        else:
            A[k] = R[j]
            j += 1
        k += 1

    while i < nL:
        A[k] = L[i]
        i += 1
        k += 1

    while j < nR:
        A[k] = R[j]
        j += 1
        k += 1

def merge_sort_recursive(A, p, r):
    if p >= r:
        return

    q = (p + r) // 2

    merge_sort_recursive(A, p, q)
    merge_sort_recursive(A, q + 1, r)
    merge(A, p, q, r)

def merge_sort(arr):
    if not arr or len(arr) <= 1:
        return arr

    merge_sort_recursive(arr, 0, len(arr) - 1)
    return arr