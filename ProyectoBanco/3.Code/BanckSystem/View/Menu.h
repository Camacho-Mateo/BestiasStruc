#ifndef MENU_H
#define MENU_H

#include "../Model/Persona.h"
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "../Controller/Registrador.h"
#include "../Controller/Cajero.h"
#include "../Controller/AdministradorBinario.h"
#include "../Model/Validador.h"
#include <iostream>

using namespace std;

class Menu {
public:
    void mostrarMenu();
};

#endif
