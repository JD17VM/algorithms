#include <iostream>
#include <vector>

using namespace std;

// Prototipo de la función auxiliar para insertar
void insert(vector<int>& v, int n);

// Función recursiva principal de ordenación por inserción
void insertionSortRecursivo(vector<int>& v, int n) {
    if (n <= 1) { return; } // Caso base
    
    // Ordena recursivamente los primeros n-1 elementos.
    insertionSortRecursivo(v, n - 1); 
    
    // Inserta el último elemento en el subvector ya ordenado.
    insert(v, n); 
}

// Función auxiliar para insertar
void insert(vector<int>& v, int n) {
    int key = v[n - 1];
    int i = n - 2;

    while (i >= 0 && v[i] > key) {
        v[i + 1] = v[i];
        i = i - 1;
    }
    v[i + 1] = key;
}

int main() {

    vector<int> numeros = {12, 11, 13, 5, 6, 7, 2};

    cout << "Vector original: ";
    for (int num : numeros) {
        cout << num << " ";
    }
    cout << endl;

    insertionSortRecursivo(numeros, numeros.size());

    cout << "Vector ordenado: ";
    for (int num : numeros) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}