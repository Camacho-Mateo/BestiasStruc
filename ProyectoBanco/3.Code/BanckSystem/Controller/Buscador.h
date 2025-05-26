#ifndef BUSCADOR_H
#define BUSCADOR_H

#include <string>
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"

using namespace std;

class Buscador {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;

public:
    Buscador(CuentaAhorro* ca, CuentaCorriente* cc);

    int buscarPorCedula(const string& cedula, bool esAhorro);
    int buscarPorNombre(const string& nombre, bool esAhorro);
    int buscarPorCuenta(const string& numeroCuenta, bool esAhorro);
};

#endif