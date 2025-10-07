#include <iostream>
#include <vector>

using namespace std;

int busquedaBinaria(const vector<int>& v, int item, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (item == v[mid]) {
            return mid + 1;
        } else if (item > v[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low;
}

void insertionSortBinario(vector<int>& v) {
    int n = v.size();
    for (int j = 1; j < n; ++j) {
        int key = v[j];
        
        int loc = busquedaBinaria(v, key, 0, j - 1); // Encuentra la posición de inserción usando búsqueda binaria
        
        int i = j - 1; // Desplaza los elementos para hacer espacio
        while (i >= loc) {
            v[i + 1] = v[i];
            i--;
        }
    
        v[loc] = key; // Inserta el elemento en su posición correcta
    }
}


int main() {
    vector<int> numeros = {37, 23, 0, 17, 12, 72, 31, 46, 100, 88, 54};

    cout << "Vector original: ";
    for (int num : numeros) {
        cout << num << " ";
    }
    cout << endl;

    insertionSortBinario(numeros);

    cout << "Vector ordenado: ";
    for (int num : numeros) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}