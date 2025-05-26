#ifndef CAJERO_H
#define CAJERO_H

#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "Buscador.h"
#include "AdministradorBinario.h"
#include <string>

using namespace std;

class Cajero {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;
    Buscador* buscador;

public:
    Cajero(CuentaAhorro* ca, CuentaCorriente* cc, Buscador* b);

    bool depositar(bool esAhorro, const string& numeroCuenta, double monto);
    bool retirar(bool esAhorro, const string& numeroCuenta, double monto);
    bool transferir(bool esAhorroOrigen, const string& cuentaOrigen, 
                   const string& cedula, bool esAhorroDestino, 
                   const string& cuentaDestino, double monto);
    double consultarSaldo(bool esAhorro, const string& numeroCuenta, const string& cedula);
};

#endif
