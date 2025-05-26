#ifndef LECTOR_H
#define LECTOR_H

#include <string>
#include <vector>
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "Buscador.h"

using namespace std;

struct Movimiento {
    string cedula;
    string tipoMovimiento;
    double monto;
    string fecha;
    double saldoFinal;
};

class Lector {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;
    Buscador* buscador;

public:
    Lector(CuentaAhorro* ca, CuentaCorriente* cc, Buscador* b);
    
    void mostrarDatosPorCuenta(const string& numeroCuenta, bool esAhorro);
    void mostrarDatosPorCedula(const string& cedula, bool esAhorro);

    vector<Movimiento> leerMovimientos();
    void mostrarMovimientos();
};

#endif
