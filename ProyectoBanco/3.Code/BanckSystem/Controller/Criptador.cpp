#include "Criptador.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void Criptador::procesarArchivo(const std::string& archivoEntrada, const std::string& archivoSalida) {
    std::ifstream entrada(archivoEntrada, std::ios::binary);
    std::ofstream salida(archivoSalida, std::ios::binary | std::ios::trunc);

    if (!entrada || !salida) {
        std::cerr << "Error al abrir los archivos para procesar." << std::endl;
        return;
    }

    char byte;
    while (entrada.get(byte)) {
        byte ^= clave;
        salida.put(byte);
    }

    entrada.close();
    salida.close();
}

void Criptador::enigma() {
    std::string nombreArchivo;
    std::cout << "Ingrese el nombre del archivo de backup a encriptar (ej: backup_20250708_150000): ";
    std::cin >> nombreArchivo;

    fs::path ruta = carpetaBackups + nombreArchivo + ".bin";

    if (!fs::exists(ruta)) {
        std::cerr << "El archivo no existe: " << ruta << std::endl;
        return;
    }

    procesarArchivo(ruta.string(), ruta.string());
    std::cout << "[DEBUG] Archivo encriptado correctamente: " << ruta << std::endl;
}

void Criptador::turing() {
    std::string nombreArchivo;
    std::cout << "Ingrese el nombre del archivo encriptado a descifrar (ej: backup_20250708_150000): ";
    std::cin >> nombreArchivo;

    fs::path rutaEntrada = carpetaBackups + nombreArchivo + ".bin";
    fs::path rutaSalida = carpetaBackups + nombreArchivo + "_descifrado.bin";

    if (!fs::exists(rutaEntrada)) {
        std::cerr << "El archivo no existe: " << rutaEntrada << std::endl;
        return;
    }

    procesarArchivo(rutaEntrada.string(), rutaSalida.string());
    std::cout << "[DEBUG] Archivo descifrado correctamente como: " << rutaSalida << std::endl;
}
