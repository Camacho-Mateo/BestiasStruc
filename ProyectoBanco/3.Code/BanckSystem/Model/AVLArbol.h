#ifndef AVLARBOL_H
#define AVLARBOL_H

#include <string>

class AVLArbol {
private:
    struct Nodo {
        std::string numeroCuenta;
        Nodo* izq;
        Nodo* der;
        int altura;
        Nodo(const std::string& num);
    };

    Nodo* raiz;

    int altura(Nodo* n);
    int balance(Nodo* n);
    Nodo* rotarDerecha(Nodo* y);
    Nodo* rotarIzquierda(Nodo* x);
    Nodo* insertar(Nodo* nodo, const std::string& num);
    void liberar(Nodo* nodo);

public:
    AVLArbol();
    ~AVLArbol();

    void insertar(const std::string& num);
    void cargarCuentasCorrientesDesdeBinario(const std::string& archivoBin);
    void imprimirArbolVertical();
};

#endif
