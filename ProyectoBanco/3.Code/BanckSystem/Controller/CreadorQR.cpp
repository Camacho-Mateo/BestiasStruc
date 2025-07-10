#include "CreadorQR.h"
#include <fstream>
#include <sstream>
#include <bitset>
#include <iomanip>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using namespace std;

CreadorQR::CreadorQR() {
    fs::create_directory("./clientesQR");
}

string CreadorQR::convertirTextoABinario(const string& texto) {
    stringstream binario;
    for (char c : texto) {
        binario << bitset<8>(c);
    }
    return binario.str();
}

// Ahora genera vector<vector<bool>> con true/false para módulos negros/blancos
vector<vector<bool>> CreadorQR::generarQRVisual(const string& binario) {
    const int size = 21;
    vector<vector<bool>> qr(size, vector<bool>(size, false));

    size_t bitIndex = 0;
    for (int i = 0; i < size && bitIndex < binario.size(); ++i) {
        for (int j = 0; j < size && bitIndex < binario.size(); ++j) {
            qr[i][j] = (binario[bitIndex++] == '1');
        }
    }

    return qr;
}

// Dibuja en PDF con módulos cuadrados (6x6 pts) negros/blancos para simular QR real
void CreadorQR::guardarPDF(const string& nombreArchivo, const vector<vector<bool>>& qr) {
    ofstream archivo("./clientesQR/" + nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error al crear PDF: " << nombreArchivo << endl;
        return;
    }

    const int size = qr.size();
    const int modSize = 6;   // tamaño módulo en puntos PDF
    const int margin = 20;   // margen en puntos PDF
    const int pageWidth = margin * 2 + size * modSize;
    const int pageHeight = margin * 2 + size * modSize;

    stringstream pdf;

    pdf << "%PDF-1.4\n"
        << "1 0 obj << /Type /Catalog /Pages 2 0 R >> endobj\n"
        << "2 0 obj << /Type /Pages /Kids [3 0 R] /Count 1 >> endobj\n"
        << "3 0 obj << /Type /Page /Parent 2 0 R /MediaBox [0 0 " << pageWidth << " " << pageHeight << "] "
           << "/Resources << >> /Contents 4 0 R >> endobj\n";

    stringstream contenido;

    contenido << "q\n";  // Guardar estado gráfico
    // Fondo blanco
    contenido << "1 1 1 rg\n";  
    contenido << "0 0 " << pageWidth << " " << pageHeight << " re f\n";

    // Dibujar módulos negros o blancos
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (qr[y][x]) {
                contenido << "0 0 0 rg\n";  // negro
            } else {
                contenido << "1 1 1 rg\n";  // blanco
            }
            int px = margin + x * modSize;
            int py = pageHeight - margin - (y + 1) * modSize;  // PDF y = 0 en abajo
            contenido << px << " " << py << " " << modSize << " " << modSize << " re f\n";
        }
    }

    contenido << "Q\n";  // Restaurar estado gráfico

    string contenidoStr = contenido.str();
    int length = (int)contenidoStr.size();

    pdf << "4 0 obj << /Length " << length << " >> stream\n"
        << contenidoStr
        << "endstream\nendobj\n"
        << "xref\n0 5\n0000000000 65535 f \n"
        << "0000000010 00000 n \n"
        << "0000000060 00000 n \n"
        << "0000000110 00000 n \n"
        << "0000000200 00000 n \n"
        << "trailer << /Size 5 /Root 1 0 R >>\n"
        << "startxref\n" << (200 + length + 50) << "\n%%EOF\n";

    archivo << pdf.str();
    archivo.close();
}

void CreadorQR::generarQRporCliente(CuentaAhorro& ahorro, CuentaCorriente& corriente) {
    for (size_t i = 0; i < ahorro.getTotalCuentas(); ++i) {
        string datos = ahorro.getCedula(i) + "|" + ahorro.getNombre(i) + "|" + ahorro.getNumeroCuentaStr(i);
        if (datos == "||") continue;

        cout << "Generando QR para: " << datos << endl;

        string binario = convertirTextoABinario(datos);
        auto qr = generarQRVisual(binario);

        string nombrePdf = "QR_" + ahorro.getCedula(i) + "_" + ahorro.getNumeroCuentaStr(i) + ".pdf";
        guardarPDF(nombrePdf, qr);
    }

    for (size_t i = 0; i < corriente.getTotalCuentas(); ++i) {
        string datos = corriente.getCedula(i) + "|" + corriente.getNombre(i) + "|" + corriente.getNumeroCuentaStr(i);
        if (datos == "||") continue;

        cout << "Generando QR para: " << datos << endl;

        string binario = convertirTextoABinario(datos);
        auto qr = generarQRVisual(binario);

        string nombrePdf = "QR_" + corriente.getCedula(i) + "_" + corriente.getNumeroCuentaStr(i) + ".pdf";
        guardarPDF(nombrePdf, qr);
    }
}
