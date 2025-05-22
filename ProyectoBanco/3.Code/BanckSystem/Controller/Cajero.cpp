#include "Cajero.h"
#include <iostream>

Cajero::Cajero(Buscador* buscador) : buscador(buscador) {}

bool Cajero::depositar(const string& cedula, bool esAhorro, double monto) {
    int pos = buscador->buscarPorCedula(cedula, esAhorro);
    if (pos == -1) {
        cout << "Cuenta no encontrada para deposito." << endl;
        return false;
    }
    double saldoActual = esAhorro ? buscador->cuentaAhorro->getSaldo(pos) : buscador->cuentaCorriente->getSaldo(pos);
    double nuevoSaldo = saldoActual + monto;

    if (esAhorro) {
        buscador->cuentaAhorro->setSaldo(pos, nuevoSaldo);
    } else {
        buscador->cuentaCorriente->setSaldo(pos, nuevoSaldo);
    }
    return true;
}

bool Cajero::retirar(const string& cedula, bool esAhorro, double monto) {
    int pos = buscador->buscarPorCedula(cedula, esAhorro);
    if (pos == -1) {
        cout << "Cuenta no encontrada para retiro." << endl;
        return false;
    }
    double saldoActual = esAhorro ? buscador->cuentaAhorro->getSaldo(pos) : buscador->cuentaCorriente->getSaldo(pos);
    if (saldoActual < monto) {
        cout << "Saldo insuficiente." << endl;
        return false;
    }

    double nuevoSaldo = saldoActual - monto;
    if (esAhorro) {
        buscador->cuentaAhorro->setSaldo(pos, nuevoSaldo);
    } else {
        buscador->cuentaCorriente->setSaldo(pos, nuevoSaldo);
    }
    return true;
}

bool Cajero::transferir(const string& cedulaOrigen, bool esAhorroOrigen, const string& cedulaDestino, bool esAhorroDestino, double monto) {
    if (!retirar(cedulaOrigen, esAhorroOrigen, monto)) {
        cout << "No se pudo retirar el dinero para la transferencia." << endl;
        return false;
    }
    if (!depositar(cedulaDestino, esAhorroDestino, monto)) {
        cout << "No se pudo depositar el dinero en la cuenta destino. Revirtiendo." << endl;
        depositar(cedulaOrigen, esAhorroOrigen, monto);
        return false;
    }
    return true;
}

double Cajero::consultarSaldo(const string& cedula, bool esAhorro) {
    int pos = buscador->buscarPorCedula(cedula, esAhorro);
    if (pos == -1) {
        cout << "Cuenta no encontrada para consulta." << endl;
        return -1;
    }
    return esAhorro ? buscador->cuentaAhorro->getSaldo(pos) : buscador->cuentaCorriente->getSaldo(pos);
}

