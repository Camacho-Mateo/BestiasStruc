// CreadorQR.h
#ifndef CREADORQR_H
#define CREADORQR_H

#include <string>
#include <vector>
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "AdministradorPDF.h"

class CreadorQR {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;
    AdministradorPDF administradorPDF;

    std::string convertirQRaTexto(const std::vector<std::vector<bool>>& qrData);

public:
    CreadorQR(CuentaAhorro* ca, CuentaCorriente* cc);

    std::vector<std::vector<bool>> generarQR(const std::string& contenido);

    void dibujarQR(const std::vector<std::vector<bool>>& qrData, const std::string& rutaArchivo);

    void generarPDFs();
};

#endif
