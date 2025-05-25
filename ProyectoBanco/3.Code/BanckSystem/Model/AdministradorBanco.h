#ifndef ADMINISTRADORBANCO_H
#define ADMINISTRADORBANCO_H

#include <string>
#include "../Controller/Buscador.h"
#include "../Controller/Lector.h"

class AdministradorBanco {
private:
    Buscador* buscadorAhorro;
    Buscador* buscadorCorriente;
    Lector* lectorAhorro;
    Lector* lectorCorriente;

public:
    AdministradorBanco(Buscador* buscadorAhorro, Buscador* buscadorCorriente,
                       Lector* lectorAhorro, Lector* lectorCorriente);
    
    void buscarPorCedula(const std::string& cedula);
    void buscarPorNumeroCuenta();
};

#endif
