#ifndef LISTADOBLE_H
#define LISTADOBLE_H

template<typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

    Nodo(const T& d) : dato(d), siguiente(nullptr), anterior(nullptr) {}
};

template<typename T>
class ListaDoble {
    Nodo<T>* cabeza;
    Nodo<T>* cola;

public:
    ListaDoble();
    ~ListaDoble();

    void insertarFinal(const T& dato);
    Nodo<T>* buscar(bool (*comparar)(const T& item, const T& valor), const T& valor);
    void eliminar(Nodo<T>* nodo);

    void recorrer(void (*func)(const T&)) const;
};

#include "ListaDoble.tpp"

#endif
