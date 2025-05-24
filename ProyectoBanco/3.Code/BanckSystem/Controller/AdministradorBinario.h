#ifndef ADMINISTRADORBINARIO_H
#define ADMINISTRADORBINARIO_H

#include <string>
#include <fstream>

struct Movimiento {
    std::string cedula;
    std::string tipoMovimiento;
    double monto;
    std::string fecha;
    double saldoFinal;
};

class AdministradorBinario {
public:
    void registrarMovimiento(const std::string& cedula, const std::string& tipoMovimiento, 
                           double monto, const std::string& fecha, double saldoFinal);
};

#endif