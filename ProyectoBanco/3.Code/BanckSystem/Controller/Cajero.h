#ifndef CAJERO_H
#define CAJERO_H

#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "Buscador.h"
#include <string>

class Cajero {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;
    Buscador* buscador;

public:
    Cajero(CuentaAhorro* ca, CuentaCorriente* cc, Buscador* b);
    
    bool depositar(bool esAhorro, const std::string& numeroCuenta, double monto);
    bool retirar(bool esAhorro, const std::string& numeroCuenta, double monto);
    bool transferir(bool esAhorroOrigen, const std::string& cuentaOrigen, 
                   const std::string& cedula, bool esAhorroDestino, 
                   const std::string& cuentaDestino, double monto);
    double consultarSaldo(bool esAhorro, const std::string& numeroCuenta, const std::string& cedula);
};

#endif