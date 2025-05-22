#ifndef CUENTAAHORRO_H
#define CUENTAAHORRO_H

#include <string>
using namespace std;

class CuentaAhorro {
private:
    string** datos;     // Matriz dinámica: cada fila una cuenta, columnas con datos
    double* saldos;     // Arreglo dinámico con saldos por cuenta
    int filas;          // Número de cuentas actuales
    int columnas;       // Número de columnas (atributos)

    void resize(int nuevaCantidad);

public:
    CuentaAhorro();
    ~CuentaAhorro();

    int getTotalCuentas();

    string getCedula(int fila);
    string getNombre(int fila);
    int getNumeroCuenta(int fila);
    double getSaldo(int fila);

    void setSaldo(int fila, double nuevoSaldo);

    void agregarCuenta(const string& cedula, const string& nombre, int numeroCuenta, double saldo);
};

#endif
