#include <iostream>
using namespace std;

template<typename T>
ListaDoble<T>::ListaDoble() : cabeza(nullptr), cola(nullptr) {}

template<typename T>
ListaDoble<T>::~ListaDoble() {
    Nodo<T>* actual = cabeza;
    while (actual) {
        Nodo<T>* aux = actual;
        actual = actual->siguiente;
        delete aux;
    }
}

template<typename T>
void ListaDoble<T>::insertarFinal(const T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (!cola) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
}

template<typename T>
Nodo<T>* ListaDoble<T>::buscar(bool (*comparar)(const T& item, const T& valor), const T& valor) {
    Nodo<T>* actual = cabeza;
    while (actual) {
        if (comparar(actual->dato, valor))
            return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

template<typename T>
void ListaDoble<T>::eliminar(Nodo<T>* nodo) {
    if (!nodo) return;
    if (nodo->anterior)
        nodo->anterior->siguiente = nodo->siguiente;
    else
        cabeza = nodo->siguiente;
    if (nodo->siguiente)
        nodo->siguiente->anterior = nodo->anterior;
    else
        cola = nodo->anterior;
    delete nodo;
}

template<typename T>
void ListaDoble<T>::recorrer(void (*func)(const T&)) const {
    Nodo<T>* actual = cabeza;
    while (actual) {
        func(actual->dato);
        actual = actual->siguiente;
    }
}
