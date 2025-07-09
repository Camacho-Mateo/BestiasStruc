#ifndef CALCULADORAHASH_H
#define CALCULADORAHASH_H

#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include <string>

class CalculadoraHash {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;

public:
    CalculadoraHash(CuentaAhorro* ca, CuentaCorriente* cc);

    void generarArchivoHash(const std::string& nombreArchivo);

    void buscarPorHash(const std::string& hash);
};

#endif
