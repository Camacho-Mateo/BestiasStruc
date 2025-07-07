#ifndef CALCULADORA_HASH_H
#define CALCULADORA_HASH_H

#include <string>
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"

class CalculadoraHash {
public:
    CalculadoraHash(CuentaAhorro* ca, CuentaCorriente* cc);
    void generarArchivoHash(const std::string& nombreArchivo);

private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;
};

#endif
