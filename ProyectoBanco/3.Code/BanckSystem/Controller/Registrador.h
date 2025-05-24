#ifndef REGISTRADOR_H
#define REGISTRADOR_H

#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"

class Registrador {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;

public:
    Registrador(CuentaAhorro* ca, CuentaCorriente* cc);
    void registrar();
};

#endif