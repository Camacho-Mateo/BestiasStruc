#ifndef BUSCADOR_H
#define BUSCADOR_H

#include <string>
#include <vector>
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"

class Buscador {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;

public:
    Buscador(CuentaAhorro* ca, CuentaCorriente* cc);

    int buscarPorCedula(const std::string& cedula, bool esAhorro);
    int buscarPorNombre(const std::string& nombre, bool esAhorro);
    int buscarPorCuenta(const std::string& numeroCuenta, bool esAhorro);
    std::vector<int> buscarPorFecha(const std::string& fecha, bool esAhorro);
};

#endif // BUSCADOR_H
