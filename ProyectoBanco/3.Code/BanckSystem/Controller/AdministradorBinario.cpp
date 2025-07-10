#include "AdministradorBinario.h"
#include "AdministradorPDF.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <chrono>
#include <ctime>

namespace fs = std::filesystem;
using namespace std;

void AdministradorBinario::guardarCuentas(const CuentaAhorro& cuentaAhorro, const CuentaCorriente& cuentaCorriente) {
    ofstream archivoBin("./cuentas.bin", ios::binary);
    if (!archivoBin) {
        cerr << "Error al abrir archivo para guardar cuentas." << endl;
        return;
    }

    ofstream archivoTxt("./cuentas.txt");
    if (!archivoTxt) {
        cerr << "Error al abrir archivo para guardar reporte de cuentas." << endl;
        return;
    }

    // Guardar cuentas de ahorro en binario y texto
    size_t totalAhorro = cuentaAhorro.getTotalCuentas();
    archivoBin.write(reinterpret_cast<const char*>(&totalAhorro), sizeof(totalAhorro));
    archivoTxt << "CUENTAS DE AHORRO:\n\n";
    for (size_t i = 0; i < totalAhorro; ++i) {
        auto escribirStringBin = [&](const string& s) {
            size_t tam = s.size();
            archivoBin.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
            archivoBin.write(s.c_str(), tam);
        };

        escribirStringBin(cuentaAhorro.getCedula(i));
        escribirStringBin(cuentaAhorro.getNombre(i));
        escribirStringBin(cuentaAhorro.getNumeroCuentaStr(i));

        double saldo = cuentaAhorro.getSaldo(i);
        archivoBin.write(reinterpret_cast<const char*>(&saldo), sizeof(saldo));

        escribirStringBin(cuentaAhorro.getTelefono(i));
        escribirStringBin(cuentaAhorro.getCorreo(i));
        escribirStringBin(cuentaAhorro.getSucursal(i));

        escribirStringBin(cuentaAhorro.getFechaRegistro(i));

        archivoTxt << "Cuenta #" << (i+1) << "\n"
                   << "Cédula: " << cuentaAhorro.getCedula(i) << "\n"
                   << "Nombre: " << cuentaAhorro.getNombre(i) << "\n"
                   << "Número de cuenta: " << cuentaAhorro.getNumeroCuentaStr(i) << "\n"
                   << "Saldo: " << saldo << "\n"
                   << "Teléfono: " << cuentaAhorro.getTelefono(i) << "\n"
                   << "Correo: " << cuentaAhorro.getCorreo(i) << "\n"
                   << "Sucursal: " << cuentaAhorro.getSucursal(i) << "\n"
                   << "Fecha registro: " << cuentaAhorro.getFechaRegistro(i) << "\n"
                   << "---------------------------\n";
    }

    // Guardar cuentas corrientes en binario y texto
    size_t totalCorriente = cuentaCorriente.getTotalCuentas();
    archivoBin.write(reinterpret_cast<const char*>(&totalCorriente), sizeof(totalCorriente));
    archivoTxt << "\nCUENTAS CORRIENTES:\n\n";
    for (size_t i = 0; i < totalCorriente; ++i) {
        auto escribirStringBin = [&](const string& s) {
            size_t tam = s.size();
            archivoBin.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
            archivoBin.write(s.c_str(), tam);
        };

        escribirStringBin(cuentaCorriente.getCedula(i));
        escribirStringBin(cuentaCorriente.getNombre(i));
        escribirStringBin(cuentaCorriente.getNumeroCuentaStr(i));

        double saldo = cuentaCorriente.getSaldo(i);
        archivoBin.write(reinterpret_cast<const char*>(&saldo), sizeof(saldo));

        escribirStringBin(cuentaCorriente.getTelefono(i));
        escribirStringBin(cuentaCorriente.getCorreo(i));
        escribirStringBin(cuentaCorriente.getSucursal(i));

        escribirStringBin(cuentaCorriente.getFechaRegistro(i));

        archivoTxt << "Cuenta #" << (i+1) << "\n"
                   << "Cédula: " << cuentaCorriente.getCedula(i) << "\n"
                   << "Nombre: " << cuentaCorriente.getNombre(i) << "\n"
                   << "Número de cuenta: " << cuentaCorriente.getNumeroCuentaStr(i) << "\n"
                   << "Saldo: " << saldo << "\n"
                   << "Teléfono: " << cuentaCorriente.getTelefono(i) << "\n"
                   << "Correo: " << cuentaCorriente.getCorreo(i) << "\n"
                   << "Sucursal: " << cuentaCorriente.getSucursal(i) << "\n"
                   << "Fecha registro: " << cuentaCorriente.getFechaRegistro(i) << "\n"
                   << "---------------------------\n";
    }

    archivoBin.close();
    archivoTxt.close();

    AdministradorPDF administradorPDF;
    administradorPDF.crearPDFDesdeTxt("./cuentas.txt", "./cuentas.pdf");
    cout << "PDF generado exitosamente como ./cuentas.pdf" << endl;
}



void AdministradorBinario::cargarCuentas(CuentaAhorro& cuentaAhorro, CuentaCorriente& cuentaCorriente) {
    ifstream archivo("./cuentas.bin", ios::binary);
    if (!archivo) {
        cerr << "No se pudo abrir archivo para cargar cuentas desde ./cuentas.bin." << endl;
        return;
    }

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

        string fechaRegistro = leerString(archivo);

        cuentaAhorro.agregarCuenta(cedula, nombre, numeroCuenta, saldo, telefono, correo, sucursal, fechaRegistro);
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

        string fechaRegistro = leerString(archivo);

        cuentaCorriente.agregarCuenta(cedula, nombre, numeroCuenta, saldo, telefono, correo, sucursal, fechaRegistro);
    }

    archivo.close();
    
}

void AdministradorBinario::crearBackup() {
    fs::path carpetaBackup = "./backups";
    if (!fs::exists(carpetaBackup)) {
        fs::create_directory(carpetaBackup);
    }

    auto ahora = chrono::system_clock::now();
    time_t tiempoActual = chrono::system_clock::to_time_t(ahora);
    tm tiempoLocal;
#ifdef _WIN32
    localtime_s(&tiempoLocal, &tiempoActual);
#else
    localtime_r(&tiempoActual, &tiempoLocal);
#endif

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

    cout << "Copia de seguridad creada exitosamente como " << nombreArchivo.str() << endl;
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
            cout << "Copia de seguridad temporal creada como backup.bin antes de restaurar." << endl;
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

    cout << "Restauración completada desde " << rutaBackup << " a cuentas.bin" << endl;
}