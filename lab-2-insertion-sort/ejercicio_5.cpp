#include <iostream>
#include <vector>
#include <string>

using namespace std;

void insertionSortStrings(vector<string>& v) {
    int n = v.size();
    for (int j = 1; j < n; ++j) {
        string key = v[j];
        int i = j - 1;

        
        // La comparación v[i] > key funciona para ordenar alfabéticamente
        while (i >= 0 && v[i] > key) { // Desplaza las palabras que son mayores que la 'key'
            v[i + 1] = v[i];
            i--;
        }
        
        v[i + 1] = key; // Inserta la palabra en su posición correcta
    }
}

int main() {
    vector<string> palabras = {"arequipa", "algoritmo", "zebra", "datos", "computacion", "texto"};

    cout << "Vector original: ";
    for (const string& palabra : palabras) {
        cout << palabra << " ";
    }
    cout << endl;

    insertionSortStrings(palabras);

    cout << "Vector ordenado: ";
    for (const string& palabra : palabras) {
        cout << palabra << " ";
    }
    cout << endl;

    return 0;
}