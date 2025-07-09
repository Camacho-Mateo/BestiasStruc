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
        auto escribirString = [&](const string& s) {
            size_t tam = s.size();
            archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
            archivo.write(s.c_str(), tam);
        };

        escribirString(cuentaAhorro.getCedula(i));
        escribirString(cuentaAhorro.getNombre(i));
        escribirString(cuentaAhorro.getNumeroCuentaStr(i));

        double saldo = cuentaAhorro.getSaldo(i);
        archivo.write(reinterpret_cast<const char*>(&saldo), sizeof(saldo));

        escribirString(cuentaAhorro.getTelefono(i));
        escribirString(cuentaAhorro.getCorreo(i));
        escribirString(cuentaAhorro.getSucursal(i));
    }

    size_t totalCorriente = cuentaCorriente.getTotalCuentas();
    archivo.write(reinterpret_cast<const char*>(&totalCorriente), sizeof(totalCorriente));
    for (size_t i = 0; i < totalCorriente; ++i) {
        auto escribirString = [&](const string& s) {
            size_t tam = s.size();
            archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
            archivo.write(s.c_str(), tam);
        };

        escribirString(cuentaCorriente.getCedula(i));
        escribirString(cuentaCorriente.getNombre(i));
        escribirString(cuentaCorriente.getNumeroCuentaStr(i));

        double saldo = cuentaCorriente.getSaldo(i);
        archivo.write(reinterpret_cast<const char*>(&saldo), sizeof(saldo));

        escribirString(cuentaCorriente.getTelefono(i));
        escribirString(cuentaCorriente.getCorreo(i));
        escribirString(cuentaCorriente.getSucursal(i));
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

    auto leerString = [&](ifstream& in) -> string {
        size_t tam;
        in.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        string s(tam, '\0');
        in.read(&s[0], tam);
        return s;
    };

    size_t totalAhorro = 0;
    archivo.read(reinterpret_cast<char*>(&totalAhorro), sizeof(totalAhorro));
    for (size_t i = 0; i < totalAhorro; ++i) {
        string cedula = leerString(archivo);
        string nombre = leerString(archivo);
        string numeroCuenta = leerString(archivo);
        double saldo;
        archivo.read(reinterpret_cast<char*>(&saldo), sizeof(saldo));

        string telefono = leerString(archivo);
        string correo = leerString(archivo);
        string sucursal = leerString(archivo);

        cuentaAhorro.agregarCuenta(cedula, nombre, numeroCuenta, saldo, telefono, correo, sucursal);
    }

    size_t totalCorriente = 0;
    archivo.read(reinterpret_cast<char*>(&totalCorriente), sizeof(totalCorriente));
    for (size_t i = 0; i < totalCorriente; ++i) {
        string cedula = leerString(archivo);
        string nombre = leerString(archivo);
        string numeroCuenta = leerString(archivo);
        double saldo;
        archivo.read(reinterpret_cast<char*>(&saldo), sizeof(saldo));

        string telefono = leerString(archivo);
        string correo = leerString(archivo);
        string sucursal = leerString(archivo);

        cuentaCorriente.agregarCuenta(cedula, nombre, numeroCuenta, saldo, telefono, correo, sucursal);
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
    localtime_s(&tiempoLocal, &tiempoActual);  // Compatible con Windows

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
