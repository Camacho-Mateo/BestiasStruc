#include "AdministradorBinario.h"
#include <iostream>
#include <fstream>

using namespace std;

void AdministradorBinario::guardarCuentas(const CuentaAhorro& cuentaAhorro, const CuentaCorriente& cuentaCorriente) {
    ofstream archivo("./cuentas.bin", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir archivo para guardar cuentas." << endl;
        return;
    }

    cout << "[DEBUG] Guardando cuentas en ./cuentas.bin..." << endl;

    size_t totalAhorro = cuentaAhorro.getTotalCuentas();
    archivo.write(reinterpret_cast<const char*>(&totalAhorro), sizeof(totalAhorro));
    for (size_t i = 0; i < totalAhorro; ++i) {
        string ced = cuentaAhorro.getCedula(i);
        size_t tam = ced.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(ced.c_str(), tam);

        string nom = cuentaAhorro.getNombre(i);
        tam = nom.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(nom.c_str(), tam);

        string num = cuentaAhorro.getNumeroCuentaStr(i);
        tam = num.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(num.c_str(), tam);

        double saldo = cuentaAhorro.getSaldo(i);
        archivo.write(reinterpret_cast<const char*>(&saldo), sizeof(saldo));
    }

    size_t totalCorriente = cuentaCorriente.getTotalCuentas();
    archivo.write(reinterpret_cast<const char*>(&totalCorriente), sizeof(totalCorriente));
    for (size_t i = 0; i < totalCorriente; ++i) {
        string ced = cuentaCorriente.getCedula(i);
        size_t tam = ced.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(ced.c_str(), tam);

        string nom = cuentaCorriente.getNombre(i);
        tam = nom.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(nom.c_str(), tam);

        string num = cuentaCorriente.getNumeroCuentaStr(i);
        tam = num.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(num.c_str(), tam);

        double saldo = cuentaCorriente.getSaldo(i);
        archivo.write(reinterpret_cast<const char*>(&saldo), sizeof(saldo));
    }

    archivo.close();
    cout << "[DEBUG] Archivo cuentas.bin guardado con éxito." << endl;
}

void AdministradorBinario::cargarCuentas(CuentaAhorro& cuentaAhorro, CuentaCorriente& cuentaCorriente) {
    ifstream archivo("./cuentas.bin", ios::binary);
    if (!archivo) {
        cerr << "No se pudo abrir archivo para cargar cuentas desde ./cuentas.bin." << endl;
        return;
    }

    cout << "[DEBUG] Cargando cuentas desde ./cuentas.bin..." << endl;

    cuentaAhorro = CuentaAhorro();
    cuentaCorriente = CuentaCorriente();

    size_t totalAhorro = 0;
    archivo.read(reinterpret_cast<char*>(&totalAhorro), sizeof(totalAhorro));
    for (size_t i = 0; i < totalAhorro; ++i) {
        string cedula, nombre, numeroCuenta;
        double saldo;

        size_t tam;
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        cedula.resize(tam);
        archivo.read(&cedula[0], tam);

        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        nombre.resize(tam);
        archivo.read(&nombre[0], tam);

        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        numeroCuenta.resize(tam);
        archivo.read(&numeroCuenta[0], tam);

        archivo.read(reinterpret_cast<char*>(&saldo), sizeof(saldo));

        cuentaAhorro.agregarCuenta(cedula, nombre, numeroCuenta, saldo);
    }

    size_t totalCorriente = 0;
    archivo.read(reinterpret_cast<char*>(&totalCorriente), sizeof(totalCorriente));
    for (size_t i = 0; i < totalCorriente; ++i) {
        string cedula, nombre, numeroCuenta;
        double saldo;

        size_t tam;
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        cedula.resize(tam);
        archivo.read(&cedula[0], tam);

        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        nombre.resize(tam);
        archivo.read(&nombre[0], tam);

        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        numeroCuenta.resize(tam);
        archivo.read(&numeroCuenta[0], tam);

        archivo.read(reinterpret_cast<char*>(&saldo), sizeof(saldo));

        cuentaCorriente.agregarCuenta(cedula, nombre, numeroCuenta, saldo);
    }

    archivo.close();
    cout << "[DEBUG] Archivo cuentas.bin cargado con éxito." << endl;
}