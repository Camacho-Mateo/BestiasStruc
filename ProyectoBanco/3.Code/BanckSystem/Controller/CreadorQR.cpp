#include "CreadorQR.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

CreadorQR::CreadorQR(CuentaAhorro* ca, CuentaCorriente* cc)
    : cuentaAhorro(ca), cuentaCorriente(cc) {}

vector<vector<bool>> CreadorQR::generarQR(const string& contenido) {
    vector<vector<bool>> qr(21, vector<bool>(21, false));
    for (size_t i = 0; i < contenido.size() && i < 21 * 21; ++i) {
        qr[i / 21][i % 21] = (contenido[i] % 2 == 0);
    }
    return qr;
}

string CreadorQR::convertirQRaTexto(const vector<vector<bool>>& qrData) {
    ostringstream ss;
    for (const auto& fila : qrData) {
        for (bool celda : fila) {
            ss << (celda ? "##" : "  ");
        }
        ss << '\n';
    }
    return ss.str();
}

void CreadorQR::generarPDFs() {
    namespace fs = filesystem;
    fs::create_directory("UsuariosQR");

    for (size_t i = 0; i < cuentaAhorro->getTotalCuentas(); ++i) {
        string nombre = cuentaAhorro->getNombre(i);
        string cuenta = cuentaAhorro->getNumeroCuentaStr(i);
        string contenido = nombre + " - " + cuenta;

        vector<vector<bool>> qr = generarQR(contenido);
        string qrAscii = convertirQRaTexto(qr);

        string rutaPDF = "UsuariosQR/" + cuenta + ".pdf";
        administradorPDF.crearPDFConTexto(rutaPDF, qrAscii);
    }

    for (size_t i = 0; i < cuentaCorriente->getTotalCuentas(); ++i) {
        string nombre = cuentaCorriente->getNombre(i);
        string cuenta = cuentaCorriente->getNumeroCuentaStr(i);
        string contenido = nombre + " - " + cuenta;

        vector<vector<bool>> qr = generarQR(contenido);
        string qrAscii = convertirQRaTexto(qr);

        string rutaPDF = "UsuariosQR/" + cuenta + ".pdf";
        administradorPDF.crearPDFConTexto(rutaPDF, qrAscii);
    }
}
