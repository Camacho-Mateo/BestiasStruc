#ifndef CAJERO_H
#define CAJERO_H

#include <string>
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "Buscador.h"
#include "AdministradorBinario.h"

class Cajero {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;
    Buscador* buscador;
    AdministradorBinario* adminBinario;

    void registrarAccion(const std::string& accion, const std::string& cuenta, double monto);
    std::string obtenerTimestamp() const;

public:
    Cajero(CuentaAhorro* ca, CuentaCorriente* cc, Buscador* b, AdministradorBinario* admin);

    bool depositar(bool esAhorro, const std::string& numeroCuenta, double monto);
    bool retirar(bool esAhorro, const std::string& numeroCuenta, double monto);
    bool transferir(bool esAhorroOrigen, const std::string& cuentaOrigen, const std::string& cedula,
                    bool esAhorroDestino, const std::string& cuentaDestino, double monto);
    double consultarSaldo(bool esAhorro, const std::string& numeroCuenta, const std::string& cedula);
};

#endif
