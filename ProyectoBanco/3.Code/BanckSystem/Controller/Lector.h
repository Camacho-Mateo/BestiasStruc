#ifndef LECTOR_H
#define LECTOR_H

#include <string>
#include "Buscador.h"

using namespace std;

class Lector {
private:
    Buscador* buscador;

public:
    Lector(Buscador* buscador);
    void mostrarDatosPorCuenta(const string& numeroCuenta);
    void mostrarDatosPorCedula(const string& cedula);
};

#endif

