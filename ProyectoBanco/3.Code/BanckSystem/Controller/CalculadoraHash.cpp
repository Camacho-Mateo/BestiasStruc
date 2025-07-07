// CalculadoraHash.cpp
#include "CalculadoraHash.h"
#include "MD5.h"
#include <fstream>
#include <iostream>

CalculadoraHash::CalculadoraHash(CuentaAhorro* ca, CuentaCorriente* cc)
    : cuentaAhorro(ca), cuentaCorriente(cc) {}

void CalculadoraHash::generarArchivoHash(const std::string& nombreArchivo) {
    std::ofstream out(nombreArchivo);
    if (!out) {
        std::cerr << "No se pudo abrir el archivo de salida." << std::endl;
        return;
    }

    out << "--- Hashes de Cuentas de Ahorro ---\n";
    for (size_t i = 0; i < cuentaAhorro->getTotalCuentas(); ++i) {
        std::string datos = cuentaAhorro->getCedula(i) + ";" +
                            cuentaAhorro->getNombre(i) + ";" +
                            cuentaAhorro->getNumeroCuentaStr(i);
        out << MD5::md5(datos) << "\n";
    }

    out << "\n--- Hashes de Cuentas Corrientes ---\n";
    for (size_t i = 0; i < cuentaCorriente->getTotalCuentas(); ++i) {
        std::string datos = cuentaCorriente->getCedula(i) + ";" +
                            cuentaCorriente->getNombre(i) + ";" +
                            cuentaCorriente->getNumeroCuentaStr(i);
        out << MD5::md5(datos) << "\n";
    }

    out.close();
    std::cout << "Archivo de hashes generado exitosamente: " << nombreArchivo << std::endl;
}
