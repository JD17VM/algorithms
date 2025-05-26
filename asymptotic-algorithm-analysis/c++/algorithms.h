#include <vector>
#include <cstddef>

using namespace std;

void insertion_sort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && key < arr[j]) {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}

void merge(vector<int>& a, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = a[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[q + 1 + j];

    int i = 0;
    int j = 0;
    int k = p;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort_recursive(vector<int>& a, int p, int r) {
    if (p < r) {
        int q_mid = p + (r - p) / 2;
        merge_sort_recursive(a, p, q_mid);
        merge_sort_recursive(a, q_mid + 1, r);
        merge(a, p, q_mid, r);
    }
}

void merge_sort(vector<int>& arr) {
    if (arr.empty() || arr.size() <= 1) {
        return;
    }
    merge_sort_recursive(arr, 0, arr.size() - 1);
}