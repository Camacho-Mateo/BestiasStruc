#include "AdministradorBinario.h"
#include <iostream>
#include <fstream>

void AdministradorBinario::guardarCuentas(const CuentaAhorro& cuentaAhorro, const CuentaCorriente& cuentaCorriente) {
    std::ofstream archivo("./cuentas.bin", std::ios::binary);
    if (!archivo) {
        std::cerr << "Error al abrir archivo para guardar cuentas." << std::endl;
        return;
    }

    std::cout << "[DEBUG] Guardando cuentas en ./cuentas.bin..." << std::endl;

    size_t totalAhorro = cuentaAhorro.getTotalCuentas();
    archivo.write(reinterpret_cast<const char*>(&totalAhorro), sizeof(totalAhorro));
    for (size_t i = 0; i < totalAhorro; ++i) {
        std::string ced = cuentaAhorro.getCedula(i);
        size_t tam = ced.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(ced.c_str(), tam);

        std::string nom = cuentaAhorro.getNombre(i);
        tam = nom.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(nom.c_str(), tam);

        std::string num = cuentaAhorro.getNumeroCuentaStr(i);
        tam = num.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(num.c_str(), tam);

        double saldo = cuentaAhorro.getSaldo(i);
        archivo.write(reinterpret_cast<const char*>(&saldo), sizeof(saldo));
    }

    size_t totalCorriente = cuentaCorriente.getTotalCuentas();
    archivo.write(reinterpret_cast<const char*>(&totalCorriente), sizeof(totalCorriente));
    for (size_t i = 0; i < totalCorriente; ++i) {
        std::string ced = cuentaCorriente.getCedula(i);
        size_t tam = ced.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(ced.c_str(), tam);

        std::string nom = cuentaCorriente.getNombre(i);
        tam = nom.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(nom.c_str(), tam);

        std::string num = cuentaCorriente.getNumeroCuentaStr(i);
        tam = num.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(num.c_str(), tam);

        double saldo = cuentaCorriente.getSaldo(i);
        archivo.write(reinterpret_cast<const char*>(&saldo), sizeof(saldo));
    }

    archivo.close();
    std::cout << "[DEBUG] Archivo cuentas.bin guardado con éxito." << std::endl;
}

void AdministradorBinario::cargarCuentas(CuentaAhorro& cuentaAhorro, CuentaCorriente& cuentaCorriente) {
    std::ifstream archivo("./cuentas.bin", std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir archivo para cargar cuentas desde ./cuentas.bin." << std::endl;
        return;
    }

    std::cout << "[DEBUG] Cargando cuentas desde ./cuentas.bin..." << std::endl;

    cuentaAhorro = CuentaAhorro();
    cuentaCorriente = CuentaCorriente();

    size_t totalAhorro = 0;
    archivo.read(reinterpret_cast<char*>(&totalAhorro), sizeof(totalAhorro));
    for (size_t i = 0; i < totalAhorro; ++i) {
        std::string cedula, nombre, numeroCuenta;
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
        std::string cedula, nombre, numeroCuenta;
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
    std::cout << "[DEBUG] Archivo cuentas.bin cargado con éxito." << std::endl;
}
