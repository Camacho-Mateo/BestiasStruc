#ifndef ADMINISTRADOR_BINARIO_H
#define ADMINISTRADOR_BINARIO_H

#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"

class AdministradorBinario {
public:
    void guardarCuentas(const CuentaAhorro& cuentaAhorro, const CuentaCorriente& cuentaCorriente);
    void cargarCuentas(CuentaAhorro& cuentaAhorro, CuentaCorriente& cuentaCorriente);
    void crearBackup();
    void restaurarBackup();
};

#endif


