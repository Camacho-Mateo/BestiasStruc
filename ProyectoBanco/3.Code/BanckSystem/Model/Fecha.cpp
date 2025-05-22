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
    cout << "Ingrese la fecha de nacimiento (DD/MM/AAAA): ";
    char entrada[11] = "";
    int pos = 0;

    while (pos < 10) {
        char c = getch();

        // Validar posiciones específicas
        if ((pos == 2 || pos == 5) && c == '/') {
            cout << c;
            entrada[pos++] = c;
        } else if (isdigit(c) && pos != 2 && pos != 5) {
            cout << c;
            entrada[pos++] = c;
        } else if (c == 8 && pos > 0) {
            pos--;
            cout << "\b \b";
        }
    }

    entrada[10] = '\0';
    strcpy(fechaNacimiento, entrada);
}

const char* Fecha::getFecha() const {
    return fechaNacimiento;
}
