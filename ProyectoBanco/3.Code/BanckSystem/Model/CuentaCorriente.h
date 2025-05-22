#ifndef CUENTACORRIENTE_H
#define CUENTACORRIENTE_H

#include <string>
#include <fstream>
#include "CuentaAhorro.h"
using namespace std;

class CuentaCorriente : public Cuenta<double> {
public:
    CuentaCorriente();
    CuentaCorriente(string num);
};

#endif
