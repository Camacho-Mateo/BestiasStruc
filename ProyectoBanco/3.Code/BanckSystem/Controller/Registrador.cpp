#include "Registrador.h"
#include <iostream>
using namespace std;

Registrador::Registrador(AdministradorBinario& admin) : adminBinario(admin) {}

bool Registrador::registrarUsuario(const Persona& persona) {
    if (!Validador::validarNombre(persona.getNombre())) {
        cerr << "Nombre invalido\n";
        return false;
    }
    if (!Validador::validarCedula(persona.getCedula())) {
        cerr << "Cedula invalida\n";
        return false;
    }

    Fecha hoy;
    adminBinario.registrarEvento("Registro de usuario: " + persona.getNombre(), hoy);

    return true;
}
