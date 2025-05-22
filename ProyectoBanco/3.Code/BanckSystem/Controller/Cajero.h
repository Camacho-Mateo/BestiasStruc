#ifndef CAJERO_H
#define CAJERO_H

#include <string>
#include "../Model/Fecha.h"
#include "AdministradorBinario.h"

using namespace std;

class Cajero {
    AdministradorBinario& adminBinario;

public:
    Cajero(AdministradorBinario& admin);

    void depositar(const string& numeroCuenta, double cantidad, const Fecha& fecha);
    bool transferir(const string& cuentaOrigen, const string& cuentaDestino, double cantidad, const Fecha& fecha);
};

#endif
