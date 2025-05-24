#ifndef BUSCADOR_H
#define BUSCADOR_H

#include <string>
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"

class Buscador {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;

public:
    Buscador(CuentaAhorro* ahorro, CuentaCorriente* corriente);
    
    int buscarPorCedula(const std::string& cedula, bool esAhorro);
    int buscarPorNombre(const std::string& nombre, bool esAhorro);
    int buscarPorCuenta(const std::string& numeroCuenta, bool esAhorro);
};

#endif