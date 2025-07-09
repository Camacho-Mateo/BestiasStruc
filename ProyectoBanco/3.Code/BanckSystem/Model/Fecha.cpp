#include "Fecha.h"
#include <iostream>
#include <cstring>
#include <conio.h>
#include <cctype>

using namespace std;

Fecha::Fecha() {
    fechaNacimiento = new char[11];
    strcpy(fechaNacimiento, "");
}

Fecha::~Fecha() {
    delete[] fechaNacimiento;
}

void Fecha::pedirFecha() {
    while (true) {
        std::cout << "Formato DD/MM/AAAA: ";
        char entrada[11] = "";
        int pos = 0;

        while (pos < 10) {
            char c = _getch();

            if ((pos == 2 || pos == 5) && c == '/') {
                std::cout << c;
                entrada[pos++] = c;
            } 
            else if (isdigit(c) && pos != 2 && pos != 5) {
                std::cout << c;
                entrada[pos++] = c;
            }
            else if (c == 8 && pos > 0) { // retroceso
                if (pos == 3 || pos == 6) { // borrar también el '/' automáticamente
                    std::cout << "\b \b";
                    pos--;
                }
                std::cout << "\b \b";
                pos--;
            }
        }

        entrada[10] = '\0';

        // Extraer el año
        int dia = atoi(std::string(entrada, entrada + 2).c_str());
        int mes = atoi(std::string(entrada + 3, entrada + 5).c_str());
        int anio = atoi(std::string(entrada + 6, entrada + 10).c_str());

        if (anio >= 1950 && anio <= 2025 && dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12) {
            strcpy(fechaNacimiento, entrada);
            std::cout << std::endl;
            break;
        } else {
            std::cout << "\nFecha inválida. Año debe estar entre 1950 y 2025. Intente nuevamente.\n";
        }
    }
}

const char* Fecha::getFecha() const {
    return fechaNacimiento;
}
