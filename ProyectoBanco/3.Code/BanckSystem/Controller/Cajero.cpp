#include "Cajero.h"
#include "AdministradorBinario.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

Cajero::Cajero(CuentaAhorro* ca, CuentaCorriente* cc, Buscador* b, AdministradorBinario* admin)
    : cuentaAhorro(ca), cuentaCorriente(cc), buscador(b), adminBinario(admin) {}

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

    adminBinario->guardarCuentas(*cuentaAhorro, *cuentaCorriente);

    registrarAccion("Depósito", numeroCuenta, monto);
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

    adminBinario->guardarCuentas(*cuentaAhorro, *cuentaCorriente);

    registrarAccion("Retiro", numeroCuenta, monto);
    return true;
}

bool Cajero::transferir(bool esAhorroOrigen, const string& cuentaOrigen, const string& cedula,
                        bool esAhorroDestino, const string& cuentaDestino, double monto) {
    int posOrigen = buscador->buscarPorCuenta(cuentaOrigen, esAhorroOrigen);
    if (posOrigen == -1) {
        cerr << "Error: Cuenta origen no existe" << endl;
        return false;
    }

    string cedulaTitular = esAhorroOrigen ?
        cuentaAhorro->getCedula(posOrigen) :
        cuentaCorriente->getCedula(posOrigen);

    if (cedulaTitular != cedula) {
        cerr << "Error: La cédula no coincide con el titular" << endl;
        return false;
    }

    if (!retirar(esAhorroOrigen, cuentaOrigen, monto)) {
        return false;
    }

    if (!depositar(esAhorroDestino, cuentaDestino, monto)) {
        // Revertir retiro si depósito falla
        depositar(esAhorroOrigen, cuentaOrigen, monto);
        return false;
    }

    registrarAccion("Transferencia origen", cuentaOrigen, monto);
    registrarAccion("Transferencia destino", cuentaDestino, monto);
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
        cerr << "Error: La cédula no coincide con el titular" << endl;
        return -1.0;
    }

    registrarAccion("Consulta", numeroCuenta, 0.0);
    return esAhorro ? cuentaAhorro->getSaldo(pos) : cuentaCorriente->getSaldo(pos);
}

void Cajero::registrarAccion(const string& accion, const string& cuenta, double monto) {
    ofstream archivo("registro_cajero.bin", ios::binary | ios::app);
    if (!archivo) {
        cerr << "Error: No se pudo abrir archivo de registro." << endl;
        return;
    }

    string timestamp = obtenerTimestamp();

    size_t tam = accion.size();
    archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
    archivo.write(accion.c_str(), tam);

    tam = cuenta.size();
    archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
    archivo.write(cuenta.c_str(), tam);

    archivo.write(reinterpret_cast<const char*>(&monto), sizeof(monto));

    tam = timestamp.size();
    archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
    archivo.write(timestamp.c_str(), tam);

    archivo.close();
}

string Cajero::obtenerTimestamp() const {
    auto ahora = chrono::system_clock::now();
    time_t tiempo = chrono::system_clock::to_time_t(ahora);
    tm tm;
#ifdef _WIN32
    localtime_s(&tm, &tiempo);
#else
    localtime_r(&tiempo, &tm);
#endif

    stringstream ss;
    ss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}