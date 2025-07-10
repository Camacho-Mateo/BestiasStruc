#include "AdministradorPDF.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm> // para std::max

void AdministradorPDF::crearPDFConTexto(const std::string& rutaArchivo, const std::string& contenido) {
    std::ofstream archivo(rutaArchivo, std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo crear el archivo PDF: " << rutaArchivo << std::endl;
        return;
    }

    // Separar contenido por líneas
    std::istringstream iss(contenido);
    std::vector<std::string> lineas;
    std::string linea;
    while (std::getline(iss, linea)) {
        std::string escapada;
        for (char c : linea) {
            if (c == '(' || c == ')' || c == '\\') escapada += '\\';
            escapada += c;
        }
        lineas.push_back(escapada);
    }

    // Calcular altura necesaria para el contenido
    int saltoLinea = 14;
    int altoPagina = std::max(792, static_cast<int>(lineas.size() * saltoLinea) + 100);
    int yPos = altoPagina - 72;  // Margen superior aumentado a 72 pts (1 pulgada)

    std::ostringstream streamContenido;
    streamContenido << "BT\n/F1 10 Tf\n";
    streamContenido << "0 0 0 rg\n";  // Color negro

    for (const auto& l : lineas) {
        streamContenido << "1 0 0 1 50 " << yPos << " Tm (" << l << ") Tj\n";
        yPos -= saltoLinea;
    }
    streamContenido << "ET\n";

    std::string contenidoStream = streamContenido.str();
    int lengthContenido = static_cast<int>(contenidoStream.size());

    // Calcular posición de startxref basada en los offsets estimados
    int offset1 = 10;
    int offset2 = offset1 + 51;
    int offset3 = offset2 + 51;
    int offset4 = offset3 + 108;
    int offset5 = offset4 + 40 + lengthContenido;
    int offset6 = offset5 + 69;

    int startxref = offset6;

    // Escritura del PDF
    archivo << "%PDF-1.4\n"
            << "1 0 obj\n"
            << "<< /Type /Catalog /Pages 2 0 R >>\n"
            << "endobj\n"
            << "2 0 obj\n"
            << "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            << "endobj\n"
            << "3 0 obj\n"
            << "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 " << altoPagina << "] "
            << "/Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
            << "endobj\n"
            << "4 0 obj\n"
            << "<< /Length " << lengthContenido << " >>\n"
            << "stream\n"
            << contenidoStream
            << "endstream\n"
            << "endobj\n"
            << "5 0 obj\n"
            << "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
            << "endobj\n"
            << "xref\n"
            << "0 6\n"
            << "0000000000 65535 f \n"
            << "0000000010 00000 n \n"
            << "0000000061 00000 n \n"
            << "0000000112 00000 n \n"
            << "0000000220 00000 n \n"
            << "0000000" << offset5 << " 00000 n \n"
            << "trailer\n"
            << "<< /Size 6 /Root 1 0 R >>\n"
            << "startxref\n"
            << startxref << "\n"
            << "%%EOF";

    archivo.close();

    std::cout << "[DEBUG] PDF generado en: " << rutaArchivo << "\n";
    std::cout << "[DEBUG] Total lineas en PDF: " << lineas.size() << "\n";
    std::cout << "[DEBUG] Altura de pagina PDF: " << altoPagina << "\n";
}

void AdministradorPDF::crearPDFDesdeTxt(const std::string& rutaTxt, const std::string& rutaPDF) {
    std::ifstream archivoTxt(rutaTxt);
    if (!archivoTxt.is_open()) {
        std::cerr << "No se pudo abrir el archivo TXT: " << rutaTxt << std::endl;
        return;
    }

    std::ostringstream buffer;
    buffer << archivoTxt.rdbuf();
    std::string contenido = buffer.str();

    // Debug
    std::cout << "[DEBUG] Leyendo archivo TXT: " << rutaTxt << "\n";
    std::cout << "[DEBUG] Tamano del contenido leido: " << contenido.size() << "\n";

    crearPDFConTexto(rutaPDF, contenido);
}