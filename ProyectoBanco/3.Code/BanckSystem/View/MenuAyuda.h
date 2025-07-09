#ifndef MENU_AYUDA_H
#define MENU_AYUDA_H

#include <iostream>
#include <filesystem>
#include <windows.h>
#include <shellapi.h> 

class MenuAyuda {
public:
    void mostrarAyuda() {
        std::string ruta = "..BanckSystem/bin/ayuda/index.html";

        if (std::filesystem::exists(ruta)) {
            ShellExecute(NULL, "open", ruta.c_str(), NULL, NULL, SW_SHOWNORMAL);
        } else {
            std::cout << "Archivo de ayuda no encontrado: " << ruta << std::endl;
            mostrarAyudaTexto();
        }
    }

private:
    void mostrarAyudaTexto() {
        std::cout << "\n=== MENÚ DE AYUDA ===\n";
        std::cout << "Este sistema bancario permite:\n";
        std::cout << "- Registrar clientes\n";
        std::cout << "- Buscar cuentas por cédula o número\n";
        std::cout << "- Depositar, retirar y transferir fondos\n";
        std::cout << "- Consultar saldo de cuentas\n";
        std::cout << "- Crear y restaurar respaldos\n";
        std::cout << "- Ordenar cuentas por nombre o número\n";
        std::cout << "- Generar códigos QR y hashes MD5\n";
        std::cout << "\nConsulte el archivo 'ayuda/index.html' para más detalles.\n";
        std::cout << "\nPresione cualquier tecla para continuar...";
        std::cin.get();
    }
};

#endif
