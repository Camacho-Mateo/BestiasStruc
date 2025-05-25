#ifndef REGISTRADOR_H
#define REGISTRADOR_H

#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "AdministradorBinario.h"

class Registrador {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;
    AdministradorBinario administradorBinario;

public:
    Registrador(CuentaAhorro* ca, CuentaCorriente* cc);
    void registrar();
};

#endif
