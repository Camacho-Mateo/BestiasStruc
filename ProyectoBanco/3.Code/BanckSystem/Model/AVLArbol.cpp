#include "AVLArbol.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <functional>

// Nodo constructor
AVLArbol::Nodo::Nodo(const std::string& num) : numeroCuenta(num), izq(nullptr), der(nullptr), altura(1) {}

AVLArbol::AVLArbol() : raiz(nullptr) {}

AVLArbol::~AVLArbol() {
    liberar(raiz);
}

int AVLArbol::altura(Nodo* n) {
    return n ? n->altura : 0;
}

int AVLArbol::balance(Nodo* n) {
    return n ? altura(n->izq) - altura(n->der) : 0;
}

AVLArbol::Nodo* AVLArbol::rotarDerecha(Nodo* y) {
    Nodo* x = y->izq;
    Nodo* T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = 1 + std::max(altura(y->izq), altura(y->der));
    x->altura = 1 + std::max(altura(x->izq), altura(x->der));

    return x;
}

AVLArbol::Nodo* AVLArbol::rotarIzquierda(Nodo* x) {
    Nodo* y = x->der;
    Nodo* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = 1 + std::max(altura(x->izq), altura(x->der));
    y->altura = 1 + std::max(altura(y->izq), altura(y->der));

    return y;
}

AVLArbol::Nodo* AVLArbol::insertar(Nodo* nodo, const std::string& num) {
    if (!nodo)
        return new Nodo(num);

    if (num < nodo->numeroCuenta)
        nodo->izq = insertar(nodo->izq, num);
    else if (num > nodo->numeroCuenta)
        nodo->der = insertar(nodo->der, num);
    else
        return nodo; // duplicados no permitidos

    nodo->altura = 1 + std::max(altura(nodo->izq), altura(nodo->der));
    int bal = balance(nodo);

    // Rotaciones AVL
    if (bal > 1 && num < nodo->izq->numeroCuenta)
        return rotarDerecha(nodo);

    if (bal < -1 && num > nodo->der->numeroCuenta)
        return rotarIzquierda(nodo);

    if (bal > 1 && num > nodo->izq->numeroCuenta) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (bal < -1 && num < nodo->der->numeroCuenta) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

void AVLArbol::insertar(const std::string& num) {
    raiz = insertar(raiz, num);
}

void AVLArbol::liberar(Nodo* nodo) {
    if (!nodo) return;
    liberar(nodo->izq);
    liberar(nodo->der);
    delete nodo;
}

void AVLArbol::cargarCuentasCorrientesDesdeBinario(const std::string& archivoBin) {
    std::ifstream archivo(archivoBin, std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo binario.\n";
        return;
    }

    size_t totalAhorro = 0, totalCorriente = 0, tam = 0;

    // Saltar cuentas de ahorro
    archivo.read(reinterpret_cast<char*>(&totalAhorro), sizeof(totalAhorro));
    for (size_t i = 0; i < totalAhorro; ++i) {
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam)); archivo.seekg(tam, std::ios::cur); // cédula
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam)); archivo.seekg(tam, std::ios::cur); // nombre
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam)); archivo.seekg(tam, std::ios::cur); // num cuenta
        archivo.seekg(sizeof(double), std::ios::cur); // saldo
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam)); archivo.seekg(tam, std::ios::cur); // teléfono
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam)); archivo.seekg(tam, std::ios::cur); // correo
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam)); archivo.seekg(tam, std::ios::cur); // sucursal
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam)); archivo.seekg(tam, std::ios::cur); // fecha registro
    }

    // Leer cuentas corrientes y agregar números de cuenta al árbol AVL
    archivo.read(reinterpret_cast<char*>(&totalCorriente), sizeof(totalCorriente));
    for (size_t i = 0; i < totalCorriente; ++i) {
        // Cédula
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam)); 
        archivo.seekg(tam, std::ios::cur);

        // Nombre
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam)); 
        archivo.seekg(tam, std::ios::cur);

        // Número de cuenta (leer para insertar)
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam)); 
        std::string numCuenta(tam, '\0');
        archivo.read(&numCuenta[0], tam);

        // Saldo
        archivo.seekg(sizeof(double), std::ios::cur);

        // Teléfono
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        archivo.seekg(tam, std::ios::cur);

        // Correo
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        archivo.seekg(tam, std::ios::cur);

        // Sucursal
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        archivo.seekg(tam, std::ios::cur);

        // Fecha de registro
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        archivo.seekg(tam, std::ios::cur);

        insertar(numCuenta);
    }

    archivo.close();
}

void AVLArbol::imprimirArbolVertical() {
    if (!raiz) {
        std::cout << "[arbol vacio]\n";
        return;
    }

    std::function<int(Nodo*)> getAltura = [&](Nodo* nodo) -> int {
        if (!nodo) return 0;
        return 1 + std::max(getAltura(nodo->izq), getAltura(nodo->der));
    };

    int altura = getAltura(raiz);
    int maxWidth = (int)std::pow(2, altura) - 1;

    struct NodoPos {
        Nodo* nodo;
        int pos;
    };

    std::vector<NodoPos> nivelActual = { {raiz, maxWidth / 2} };
    int espacioBase = 3;

    for (int nivel = 0; nivel < altura; nivel++) {
        int nivelSize = (int)nivelActual.size();

        int prevPos = -1;
        for (int i = 0; i < nivelSize; i++) {
            NodoPos &np = nivelActual[i];
            int espacios = (prevPos == -1) ? np.pos : (np.pos - prevPos - 1);
            std::cout << std::string(espacios * espacioBase, ' ');

            if (np.nodo)
                std::cout << np.nodo->numeroCuenta;
            else
                std::cout << "-----";

            prevPos = np.pos;
        }
        std::cout << "\n\n";

        std::vector<NodoPos> siguienteNivel;
        for (const NodoPos& np : nivelActual) {
            int offset = (int)std::pow(2, altura - nivel - 2);
            if (np.nodo) {
                siguienteNivel.push_back({ np.nodo->izq, np.pos - offset });
                siguienteNivel.push_back({ np.nodo->der, np.pos + offset });
            } else {
                siguienteNivel.push_back({ nullptr, np.pos - offset });
                siguienteNivel.push_back({ nullptr, np.pos + offset });
            }
        }

        nivelActual = siguienteNivel;
    }
}
