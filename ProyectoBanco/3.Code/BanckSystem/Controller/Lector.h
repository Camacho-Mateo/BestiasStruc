#include "Lector.h"
#include <iostream>

Lector::Lector(AdministradorBinario& admin) : adminBinario(admin) {}

void Lector::leerHistorialCuenta(const std::string& numeroCuenta) const {
    std::cout << "Leyendo historial para la cuenta: " << numeroCuenta << std::endl;
    adminBinario.leerEventos();
}
