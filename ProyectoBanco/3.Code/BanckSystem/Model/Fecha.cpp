#include "Fecha.h"
#include <iostream>
#include <cstring>
#include <conio.h>
#include <cctype>

Fecha::Fecha() {
    fechaNacimiento = new char[11];
    strcpy(fechaNacimiento, "");
}

Fecha::~Fecha() {
    delete[] fechaNacimiento;
}

void Fecha::pedirFecha() {
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
        else if (c == 8 && pos > 0) { // Backspace
            pos--;
            std::cout << "\b \b";
        }
    }

    entrada[10] = '\0';
    strcpy(fechaNacimiento, entrada);
    std::cout << std::endl;
}

const char* Fecha::getFecha() const {
    return fechaNacimiento;
}