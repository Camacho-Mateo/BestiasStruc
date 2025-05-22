#ifndef ADMINISTRADORBINARIO_H
#define ADMINISTRADORBINARIO_H

#include <string>
#include <fstream>
#include "../Model/Persona.h"
#include "../Model/Fecha.h"

using namespace std;

class AdministradorBinario {
private:
    string nombreArchivo;

public:
    AdministradorBinario(const string& nombreArchivo);

    void guardarRegistro(const Persona& persona, const Fecha& fechaRegistro, double saldo);
    void registrarMovimiento(const string& cedula, const string& tipoMovimiento, double monto, const string& fecha, double saldoFinal);
};

#endif
