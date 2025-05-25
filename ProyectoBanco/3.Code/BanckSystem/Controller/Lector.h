#ifndef LECTOR_H
#define LECTOR_H

#include <string>
#include <vector>
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "Buscador.h"

struct Movimiento {
    std::string cedula;
    std::string tipoMovimiento;
    double monto;
    std::string fecha;
    double saldoFinal;
};

class Lector {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;
    Buscador* buscador;

public:
    Lector(CuentaAhorro* ca, CuentaCorriente* cc, Buscador* b);
    
    void mostrarDatosPorCuenta(const std::string& numeroCuenta, bool esAhorro);
    void mostrarDatosPorCedula(const std::string& cedula, bool esAhorro);

    // Nuevo método para leer y mostrar movimientos guardados en archivo binario
    std::vector<Movimiento> leerMovimientos();
    void mostrarMovimientos();
};

#endif
