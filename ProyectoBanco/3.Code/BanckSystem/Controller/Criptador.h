#ifndef CRIPTADOR_H
#define CRIPTADOR_H

#include <string>

class Criptador {
private:
    const std::string carpetaBackups = "./backups/";
    const char clave = 0xAA;

    void procesarArchivo(const std::string& archivoEntrada, const std::string& archivoSalida);

public:
    void enigma();
    void turing();
};

#endif
