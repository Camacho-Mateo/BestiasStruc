#ifndef CREADORQR_H
#define CREADORQR_H

#include <string>
#include <vector>
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"

class CreadorQR {
public:
    CreadorQR();

    std::string convertirTextoABinario(const std::string& texto);
    std::vector<std::vector<bool>> generarQRVisual(const std::string& binario);

    void guardarPDF(const std::string& nombreArchivo, const std::vector<std::vector<bool>>& qr);

    void generarQRporCliente(CuentaAhorro& ahorro, CuentaCorriente& corriente);
};

#endif
