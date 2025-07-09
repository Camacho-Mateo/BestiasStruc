#include "CalculadoraHash.h"
#include "MD5.h"
#include <fstream>
#include <iostream>

using namespace std;

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

void CalculadoraHash::buscarPorHash(const std::string& hash) {
    bool encontrado = false;

    // Buscar en cuentas de ahorro
    for (size_t i = 0; i < cuentaAhorro->getTotalCuentas(); ++i) {
        std::string datos = cuentaAhorro->getCedula(i) + ";" +
                            cuentaAhorro->getNombre(i) + ";" +
                            cuentaAhorro->getNumeroCuentaStr(i);
        if (MD5::md5(datos) == hash) {
            std::cout << "\nHash encontrado en cuenta de ahorro:\n";
            std::cout << "Cedula: " << cuentaAhorro->getCedula(i) << "\n";
            std::cout << "Nombre: " << cuentaAhorro->getNombre(i) << "\n";
            std::cout << "Numero de cuenta: " << cuentaAhorro->getNumeroCuentaStr(i) << "\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        // Buscar en cuentas corrientes
        for (size_t i = 0; i < cuentaCorriente->getTotalCuentas(); ++i) {
            std::string datos = cuentaCorriente->getCedula(i) + ";" +
                                cuentaCorriente->getNombre(i) + ";" +
                                cuentaCorriente->getNumeroCuentaStr(i);
            if (MD5::md5(datos) == hash) {
                std::cout << "\nHash encontrado en cuenta corriente:\n";
                std::cout << "Cedula: " << cuentaCorriente->getCedula(i) << "\n";
                std::cout << "Nombre: " << cuentaCorriente->getNombre(i) << "\n";
                std::cout << "Numero de cuenta: " << cuentaCorriente->getNumeroCuentaStr(i) << "\n";
                encontrado = true;
                break;
            }
        }
    }

    if (!encontrado) {
        std::cout << "\nHash no encontrado en ninguna cuenta.\n";
    }
}
