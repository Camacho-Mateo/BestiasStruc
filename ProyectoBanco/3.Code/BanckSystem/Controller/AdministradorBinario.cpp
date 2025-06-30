#include "AdministradorBinario.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <chrono>
#include <ctime>

using namespace std;
namespace fs = std::filesystem;

void AdministradorBinario::guardarCuentas(const CuentaAhorro& cuentaAhorro, const CuentaCorriente& cuentaCorriente) {
    ofstream archivo("./cuentas.bin", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir archivo para guardar cuentas." << endl;
        return;
    }

    cout << "[DEBUG] Guardando cuentas en ./cuentas.bin..." << endl;

    size_t totalAhorro = cuentaAhorro.getTotalCuentas();
    archivo.write(reinterpret_cast<const char*>(&totalAhorro), sizeof(totalAhorro));
    for (size_t i = 0; i < totalAhorro; ++i) {
        string ced = cuentaAhorro.getCedula(i);
        size_t tam = ced.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(ced.c_str(), tam);

        string nom = cuentaAhorro.getNombre(i);
        tam = nom.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(nom.c_str(), tam);

        string num = cuentaAhorro.getNumeroCuentaStr(i);
        tam = num.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(num.c_str(), tam);

        double saldo = cuentaAhorro.getSaldo(i);
        archivo.write(reinterpret_cast<const char*>(&saldo), sizeof(saldo));
    }

    size_t totalCorriente = cuentaCorriente.getTotalCuentas();
    archivo.write(reinterpret_cast<const char*>(&totalCorriente), sizeof(totalCorriente));
    for (size_t i = 0; i < totalCorriente; ++i) {
        string ced = cuentaCorriente.getCedula(i);
        size_t tam = ced.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(ced.c_str(), tam);

        string nom = cuentaCorriente.getNombre(i);
        tam = nom.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(nom.c_str(), tam);

        string num = cuentaCorriente.getNumeroCuentaStr(i);
        tam = num.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(num.c_str(), tam);

        double saldo = cuentaCorriente.getSaldo(i);
        archivo.write(reinterpret_cast<const char*>(&saldo), sizeof(saldo));
    }

    archivo.close();
    cout << "[DEBUG] Archivo cuentas.bin guardado con éxito." << endl;
}

void AdministradorBinario::cargarCuentas(CuentaAhorro& cuentaAhorro, CuentaCorriente& cuentaCorriente) {
    ifstream archivo("./cuentas.bin", ios::binary);
    if (!archivo) {
        cerr << "No se pudo abrir archivo para cargar cuentas desde ./cuentas.bin." << endl;
        return;
    }

    cout << "[DEBUG] Cargando cuentas desde ./cuentas.bin..." << endl;

    cuentaAhorro = CuentaAhorro();
    cuentaCorriente = CuentaCorriente();

    size_t totalAhorro = 0;
    archivo.read(reinterpret_cast<char*>(&totalAhorro), sizeof(totalAhorro));
    for (size_t i = 0; i < totalAhorro; ++i) {
        string cedula, nombre, numeroCuenta;
        double saldo;

        size_t tam;
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        cedula.resize(tam);
        archivo.read(&cedula[0], tam);

        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        nombre.resize(tam);
        archivo.read(&nombre[0], tam);

        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        numeroCuenta.resize(tam);
        archivo.read(&numeroCuenta[0], tam);

        archivo.read(reinterpret_cast<char*>(&saldo), sizeof(saldo));

        cuentaAhorro.agregarCuenta(cedula, nombre, numeroCuenta, saldo);
    }

    size_t totalCorriente = 0;
    archivo.read(reinterpret_cast<char*>(&totalCorriente), sizeof(totalCorriente));
    for (size_t i = 0; i < totalCorriente; ++i) {
        string cedula, nombre, numeroCuenta;
        double saldo;

        size_t tam;
        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        cedula.resize(tam);
        archivo.read(&cedula[0], tam);

        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        nombre.resize(tam);
        archivo.read(&nombre[0], tam);

        archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        numeroCuenta.resize(tam);
        archivo.read(&numeroCuenta[0], tam);

        archivo.read(reinterpret_cast<char*>(&saldo), sizeof(saldo));

        cuentaCorriente.agregarCuenta(cedula, nombre, numeroCuenta, saldo);
    }

    archivo.close();
    cout << "[DEBUG] Archivo cuentas.bin cargado con éxito." << endl;
}

void AdministradorBinario::crearBackup() {
    fs::path carpetaBackup = "./backups";
    if (!fs::exists(carpetaBackup)) {
        fs::create_directory(carpetaBackup);
    }

    auto ahora = chrono::system_clock::now();
    time_t tiempoActual = chrono::system_clock::to_time_t(ahora);
    tm tiempoLocal;
    localtime_s(&tiempoLocal, &tiempoActual);  // ✅ Compatible con Windows

    stringstream nombreArchivo;
    nombreArchivo << carpetaBackup.string() << "/backup_"
                  << put_time(&tiempoLocal, "%Y%m%d_%H%M%S") << ".bin";

    ifstream origen("./cuentas.bin", ios::binary);
    ofstream destino(nombreArchivo.str(), ios::binary);

    if (!origen || !destino) {
        cerr << "Error al crear copia de seguridad (backup)." << endl;
        return;
    }

    destino << origen.rdbuf();
    origen.close();
    destino.close();

    cout << "[DEBUG] Copia de seguridad creada exitosamente como " << nombreArchivo.str() << endl;
}

void AdministradorBinario::restaurarBackup() {
    string nombreBackup;
    cout << "Ingrese el nombre del backup a restaurar (ej. backup_20250530_123405): ";
    cin >> nombreBackup;

    fs::path rutaBackup = "./backups/" + nombreBackup + ".bin";

    if (!fs::exists(rutaBackup)) {
        cerr << "Error: El archivo de respaldo especificado no existe: " << rutaBackup << endl;
        return;
    }

    if (fs::exists("./cuentas.bin")) {
        ifstream archivoActual("./cuentas.bin", ios::binary);
        ofstream copiaSeguridad("./backup.bin", ios::binary);
        if (archivoActual && copiaSeguridad) {
            copiaSeguridad << archivoActual.rdbuf();
            cout << "[DEBUG] Copia de seguridad temporal creada como backup.bin antes de restaurar." << endl;
        } else {
            cerr << "Advertencia: No se pudo crear copia de seguridad temporal." << endl;
        }
        archivoActual.close();
        copiaSeguridad.close();
    }

    ifstream backup(rutaBackup, ios::binary);
    ofstream cuentas("./cuentas.bin", ios::binary | ios::trunc);

    if (!backup) {
        cerr << "Error: No se pudo abrir el archivo de respaldo: " << rutaBackup << endl;
        return;
    }

    if (!cuentas) {
        cerr << "Error: No se pudo abrir cuentas.bin para restaurar." << endl;
        return;
    }

    cuentas << backup.rdbuf();
    backup.close();
    cuentas.close();

    cout << "[DEBUG] Restauración completada desde " << rutaBackup << " a cuentas.bin" << endl;
}

