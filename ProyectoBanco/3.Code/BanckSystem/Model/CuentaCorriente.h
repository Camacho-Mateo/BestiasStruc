#ifndef CUENTACORRIENTE_H
#define CUENTACORRIENTE_H

#include <string>
using namespace std;

class CuentaCorriente {
private:
    string** datos;
    double* saldos;
    int filas;
    int columnas;

    void resize(int nuevaCantidad);

public:
    CuentaCorriente();
    ~CuentaCorriente();

    int getTotalCuentas();

    string getCedula(int fila);
    string getNombre(int fila);
    int getNumeroCuenta(int fila);
    double getSaldo(int fila);

    void setSaldo(int fila, double nuevoSaldo);

    void agregarCuenta(const string& cedula, const string& nombre, int numeroCuenta, double saldo);
};

#endif
