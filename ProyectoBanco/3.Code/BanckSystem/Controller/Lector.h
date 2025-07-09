#ifndef LECTOR_H
#define LECTOR_H

#include <string>
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "Buscador.h"

using namespace std;

class Lector {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;
    Buscador* buscador;

public:
    Lector(CuentaAhorro* ca, CuentaCorriente* cc, Buscador* b);
    
    void mostrarDatosPorCuenta(const string& numeroCuenta, bool esAhorro);
    void mostrarDatosPorCedula(const string& cedula, bool esAhorro);
};

#endif
