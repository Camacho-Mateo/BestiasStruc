#ifndef MENU_INTERACTIVO_H
#define MENU_INTERACTIVO_H

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>

class MenuInteractivo {
private:
    std::vector<std::string> opciones;
    int seleccion = 0;

    void mostrarMenu() const {
        system("cls");
        std::cout << "=== SISTEMA BANCARIO ===\n\n";
        for (size_t i = 0; i < opciones.size(); ++i) {
            if ((int)i == seleccion) {
                std::cout << " > " << opciones[i] << "\n";
            } else {
                std::cout << "   " << opciones[i] << "\n";
            }
        }
    }

public:
    MenuInteractivo(const std::vector<std::string>& opcionesMenu)
        : opciones(opcionesMenu) {}

    int ejecutar() {
        char tecla;
        do {
            mostrarMenu();
            tecla = _getch();
            switch (tecla) {
                case 72:
                    if (seleccion > 0) seleccion--;
                    break;
                case 80:
                    if (seleccion < (int)opciones.size() - 1) seleccion++;
                    break;
            }
        } while (tecla != 13);
        return seleccion + 1;
    }
};

#endif

