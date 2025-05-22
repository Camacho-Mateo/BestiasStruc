#ifndef FECHA_H
#define FECHA_H

#include <string>
#include <ctime>
#include <stdexcept>

using namespace std;

class Fecha {
private:
    int dia;
    int mes;
    int anio;

    bool validarFecha(int dia, int mes, int anio);
    bool esBisiesto(int anio);

public:
    Fecha();
    Fecha(int dia, int mes, int anio);

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    string toString() const;
};

#endif
