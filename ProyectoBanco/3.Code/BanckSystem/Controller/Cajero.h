#ifndef CAJERO_H
#define CAJERO_H

#include <string>
#include "Buscador.h"

using namespace std;

class Cajero {
private:
    Buscador* buscador;

public:
    Cajero(Buscador* buscador);

    bool depositar(const string& cedula, bool esAhorro, double monto);
    bool retirar(const string& cedula, bool esAhorro, double monto);
    bool transferir(const string& cedulaOrigen, bool esAhorroOrigen, const string& cedulaDestino, bool esAhorroDestino, double monto);

    double consultarSaldo(const string& cedula, bool esAhorro);
};

#endif

