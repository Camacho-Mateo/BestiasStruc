#ifndef REGISTRADOR_H
#define REGISTRADOR_H

#include "../Model/Persona.h"
#include "../Model/Validador.h"
#include "AdministradorBinario.h"
#include "../Model/Fecha.h"
#include <string>
using namespace std;

class Registrador {
    AdministradorBinario& adminBinario;

public:
    Registrador(AdministradorBinario& admin);

    bool registrarUsuario(const Persona& persona);
};

#endif