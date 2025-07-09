#ifndef EDITOR_H
#define EDITOR_H

#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "../Model/AdministradorBanco.h"
#include "../Controller/AdministradorBinario.h"
#include "../Model/Validador.h"
#include "../View/MenuInteractivo.h"
#include <iostream>
#include <string>

class Editor {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;
    AdministradorBanco* administradorBanco;
    AdministradorBinario administradorBinario;

    void modificarNombre(const std::string& cedula);
    void modificarCedula(const std::string& cedula);
    void modificarCorreo(const std::string& cedula);
    void modificarTelefono(const std::string& cedula);

public:
    Editor(CuentaAhorro* ca, CuentaCorriente* cc, AdministradorBanco* ab);

    void ejecutar();
};

#endif
