#include "Cajero.h"
#include "AdministradorBinario.h"
#include <iostream>

using namespace std;

Cajero::Cajero(CuentaAhorro* ca, CuentaCorriente* cc, Buscador* b) 
    : cuentaAhorro(ca), cuentaCorriente(cc), buscador(b) {}

bool Cajero::depositar(bool esAhorro, const string& numeroCuenta, double monto) {
    int pos = buscador->buscarPorCuenta(numeroCuenta, esAhorro);
    if (pos == -1) {
        cerr << "Error: Cuenta no encontrada" << endl;
        return false;
    }
    
    if (esAhorro) {
        cuentaAhorro->setSaldo(pos, cuentaAhorro->getSaldo(pos) + monto);
    } else {
        cuentaCorriente->setSaldo(pos, cuentaCorriente->getSaldo(pos) + monto);
    }

    AdministradorBinario admin;
    admin.guardarCuentas(*cuentaAhorro, *cuentaCorriente);

    return true;
}

bool Cajero::retirar(bool esAhorro, const string& numeroCuenta, double monto) {
    int pos = buscador->buscarPorCuenta(numeroCuenta, esAhorro);
    if (pos == -1) {
        cerr << "Error: Cuenta no encontrada" << endl;
        return false;
    }

    double saldoActual = esAhorro ? cuentaAhorro->getSaldo(pos) : cuentaCorriente->getSaldo(pos);
    if (saldoActual < monto) {
        cerr << "Error: Saldo insuficiente" << endl;
        return false;
    }

    if (esAhorro) {
        cuentaAhorro->setSaldo(pos, saldoActual - monto);
    } else {
        cuentaCorriente->setSaldo(pos, saldoActual - monto);
    }

    AdministradorBinario admin;
    admin.guardarCuentas(*cuentaAhorro, *cuentaCorriente);

    return true;
}

bool Cajero::transferir(bool esAhorroOrigen, const string& cuentaOrigen, 
                       const string& cedula, bool esAhorroDestino, 
                       const string& cuentaDestino, double monto) {
    int posOrigen = buscador->buscarPorCuenta(cuentaOrigen, esAhorroOrigen);
    if (posOrigen == -1) {
        cerr << "Error: Cuenta origen no existe" << endl;
        return false;
    }

    string cedulaTitular = esAhorroOrigen ? 
        cuentaAhorro->getCedula(posOrigen) : 
        cuentaCorriente->getCedula(posOrigen);
    
    if (cedulaTitular != cedula) {
        cerr << "Error: La cedula no coincide con el titular" << endl;
        return false;
    }

    if (!retirar(esAhorroOrigen, cuentaOrigen, monto)) {
        return false;
    }

    if (!depositar(esAhorroDestino, cuentaDestino, monto)) {
        depositar(esAhorroOrigen, cuentaOrigen, monto);
        return false;
    }


    return true;
}

double Cajero::consultarSaldo(bool esAhorro, const string& numeroCuenta, const string& cedula) {
    int pos = buscador->buscarPorCuenta(numeroCuenta, esAhorro);
    if (pos == -1) {
        cerr << "Error: Cuenta no encontrada" << endl;
        return -1.0;
    }
    
    string cedulaTitular = esAhorro ? 
        cuentaAhorro->getCedula(pos) : 
        cuentaCorriente->getCedula(pos);
    
    if (cedulaTitular != cedula) {
        cerr << "Error: La cedula no coincide con el titular" << endl;
        return -1.0;
    }

    return esAhorro ? cuentaAhorro->getSaldo(pos) : cuentaCorriente->getSaldo(pos);
}
