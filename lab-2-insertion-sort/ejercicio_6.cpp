#include <iostream>
#include <vector>

using namespace std;

struct Nodo {
    int val;
    Nodo *siguiente;
    Nodo(int x) : val(x), siguiente(nullptr) {}
};

Nodo* insertionSortList(Nodo* head) {
    if (!head || !head->siguiente) {
        return head;
    }

    Nodo* headOrdenado = nullptr; 
    Nodo* nodoActual = head;

    while (nodoActual != nullptr) {
        Nodo* nodoSiguiente = nodoActual->siguiente;

        if (headOrdenado == nullptr || headOrdenado->val >= nodoActual->val) {
            nodoActual->siguiente = headOrdenado;
            headOrdenado = nodoActual;
        } else {
            Nodo* temp = headOrdenado;
            while (temp->siguiente != nullptr && temp->siguiente->val < nodoActual->val) {
                temp = temp->siguiente;
            }
            nodoActual->siguiente = temp->siguiente;
            temp->siguiente = nodoActual;
        }
        
        nodoActual = nodoSiguiente;
    }

    return headOrdenado;
}


void imprimirLista(Nodo* nodo_p) {
    while (nodo_p != nullptr) {
        cout << nodo_p->val << " -> ";
        nodo_p = nodo_p->siguiente;
    }
    cout << "nullptr" << endl;
}

int main() {
    Nodo* head = new Nodo(4);
    head->siguiente = new Nodo(2);
    head->siguiente->siguiente = new Nodo(1);
    head->siguiente->siguiente->siguiente = new Nodo(3);

    cout << "Lista original:   ";
    imprimirLista(head);

    head = insertionSortList(head);

    cout << "Lista ordenada: ";
    imprimirLista(head);

    return 0;
}