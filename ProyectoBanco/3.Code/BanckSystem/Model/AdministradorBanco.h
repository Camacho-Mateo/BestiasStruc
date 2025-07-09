#ifndef ADMINISTRADOR_BANCO_H
#define ADMINISTRADOR_BANCO_H

#include <string>
#include <map>
#include "Persona.h"
#include "../Controller/Buscador.h"
#include "../Controller/Lector.h"

class AdministradorBanco {
private:
    Buscador* buscadorAhorro;
    Buscador* buscadorCorriente;
    Lector* lectorAhorro;
    Lector* lectorCorriente;

    std::map<std::string, Persona> personas;

public:
    AdministradorBanco(Buscador* buscadorAhorro, Buscador* buscadorCorriente,
                       Lector* lectorAhorro, Lector* lectorCorriente);

    void buscarPorCedula(const std::string& cedula);
    void buscarPorNumeroCuenta();

    bool estaRegistrada(const std::string& cedula);

    void agregarPersona(const Persona& persona);
    Persona obtenerPersona(const std::string& cedula) const;
};

#endif
