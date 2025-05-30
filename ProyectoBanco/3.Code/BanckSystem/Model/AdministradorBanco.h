#ifndef ADMINISTRADORBANCO_H
#define ADMINISTRADORBANCO_H

#include <string>
#include "../Controller/Buscador.h"
#include "../Controller/Lector.h"

using namespace std;

class AdministradorBanco {
private:
    Buscador* buscadorAhorro;
    Buscador* buscadorCorriente;
    Lector* lectorAhorro;
    Lector* lectorCorriente;

public:
    AdministradorBanco(Buscador* buscadorAhorro, Buscador* buscadorCorriente,
                      Lector* lectorAhorro, Lector* lectorCorriente);

    void buscarPorCedula(const string& cedula);
    void buscarPorNumeroCuenta();

    bool estaRegistrada(const string& cedula);
};

#endif
