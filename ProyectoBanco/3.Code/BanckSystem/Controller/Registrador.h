#ifndef REGISTRADOR_H
#define REGISTRADOR_H

#include <iostream>
#include "../Model/Persona.h"
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "../Model/Validador.h"
#include "../Model/Fecha.h"

using namespace std;

class Registrador {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;

public:
    Registrador(CuentaAhorro* ca, CuentaCorriente* cc);

    void registrarPersona();
};

#endif
