#ifndef REGISTRADOR_H
#define REGISTRADOR_H

#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "../Model/AdministradorBanco.h"
#include "AdministradorBinario.h"

class Registrador {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;
    AdministradorBanco* administradorBanco;

    AdministradorBinario administradorBinario;

public:
    Registrador(CuentaAhorro* ca, CuentaCorriente* cc, AdministradorBanco* ab);
    void registrar();
};

#endif
