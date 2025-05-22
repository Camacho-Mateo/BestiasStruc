#ifndef CUENTAAHORRO_H
#define CUENTAAHORRO_H

#include <string>
#include <fstream>
using namespace std;

template<typename T>
class Cuenta {
protected:
    string numeroCuenta;
    T saldo;

public:
    Cuenta();
    Cuenta(string num, T saldoInicial);

    void depositar(T cantidad);
    bool retirar(T cantidad);

    T getSaldo() const;
    string getNumeroCuenta() const;

    void setNumeroCuenta(string num);

    void escribir(ofstream& out) const;
    void leer(ifstream& in);
};

class CuentaAhorro : public Cuenta<double> {
public:
    CuentaAhorro();
    CuentaAhorro(string num);
};

#endif
