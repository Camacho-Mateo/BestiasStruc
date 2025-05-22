#include "Cajero.h"
#include <iostream>

using namespace std;

Cajero::Cajero(AdministradorBinario& admin) : adminBinario(admin) {}

void Cajero::depositar(const string& numeroCuenta, double cantidad, const Fecha& fecha) {
    adminBinario.registrarEvento("Deposito en cuenta " + numeroCuenta + " cantidad: " + to_string(cantidad), fecha);
}

bool Cajero::transferir(const string& cuentaOrigen, const string& cuentaDestino, double cantidad, const Fecha& fecha) {
    adminBinario.registrarEvento("Transferencia de " + to_string(cantidad) + " de cuenta " + cuentaOrigen + " a " + cuentaDestino, fecha);
    return true;
}
