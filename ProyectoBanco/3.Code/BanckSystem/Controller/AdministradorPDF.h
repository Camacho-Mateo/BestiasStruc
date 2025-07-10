#ifndef ADMINISTRADORPDF_H
#define ADMINISTRADORPDF_H

#include <string>

class AdministradorPDF {
public:
    AdministradorPDF() = default;

    void crearPDFConTexto(const std::string& rutaArchivo, const std::string& contenido);
    void crearPDFDesdeTxt(const std::string& rutaTxt, const std::string& rutaPDF);
};

#endif