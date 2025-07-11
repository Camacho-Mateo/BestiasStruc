#ifndef MENU_AYUDA_H
#define MENU_AYUDA_H

#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <filesystem>

class MenuAyuda {
public:
    void mostrarAyuda() {
        std::string ruta = "ayuda\\Sistema Bancario BANKSYSTEM.chm";

        if (std::filesystem::exists(ruta)) {
            ShellExecuteA(NULL, "open", ("\"" + ruta + "\"").c_str(), NULL, NULL, SW_SHOWNORMAL);
        } else {
            std::cout << "Archivo de ayuda no encontrado:\n" << ruta << std::endl;
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
        std::cout << "- Agendar citas y generar reportes\n";
        std::cout << "\nPresione ENTER para continuar...";
        std::cin.get();
    }
};

#endif
