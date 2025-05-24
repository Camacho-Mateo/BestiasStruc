#ifndef CUENTAAHORRO_H
#define CUENTAAHORRO_H

#include <string>
#include <vector>

using namespace std;

class CuentaAhorro {
private:
    struct Cuenta {
        string cedula;
        string nombre;
        string numeroCuenta;
        double saldo;
    };
    
    vector<Cuenta> cuentas;
    static size_t contadorCuentas;

public:
    CuentaAhorro();
    
    size_t getTotalCuentas() const;
    string getCedula(size_t index) const;
    string getNombre(size_t index) const;
    string getNumeroCuentaStr(size_t index) const;
    double getSaldo(size_t index) const;
    
    void setSaldo(size_t index, double nuevoSaldo);
    void agregarCuenta(const string& cedula, const string& nombre, 
                      const string& numeroCuenta, double saldoInicial);
    
    string generarNumeroCuenta();
};

#endif