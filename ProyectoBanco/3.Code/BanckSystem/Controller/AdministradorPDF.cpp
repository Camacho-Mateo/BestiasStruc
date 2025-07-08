#include "AdministradorPDF.h"
#include <fstream>
#include <sstream>

void AdministradorPDF::crearPDFConTexto(const std::string& rutaArchivo, const std::string& contenido) {
    std::ofstream archivo(rutaArchivo, std::ios::binary);
    if (!archivo.is_open()) return;

    std::ostringstream streamContenido;
    streamContenido << "BT /F1 12 Tf 50 700 Td (";

    for (char c : contenido) {
        if (c == '(' || c == ')' || c == '\\') {
            streamContenido << '\\' << c;
        } else if (c == '\n') {
            streamContenido << ") Tj\n"
                            << "50 " << (700 - 14) << " Td (";
        } else {
            streamContenido << c;
        }
    }
    streamContenido << ") Tj ET\n";

    std::string contenidoStream = streamContenido.str();

    archivo << "%PDF-1.4\n"
            << "1 0 obj\n"
            << "<< /Type /Catalog /Pages 2 0 R >>\n"
            << "endobj\n"
            << "2 0 obj\n"
            << "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            << "endobj\n"
            << "3 0 obj\n"
            << "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
            << "endobj\n"
            << "4 0 obj\n"
            << "<< /Length " << contenidoStream.size() << " >>\n"
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
            << "0000000340 00000 n \n"
            << "trailer\n"
            << "<< /Size 6 /Root 1 0 R >>\n"
            << "startxref\n"
            << "450\n"
            << "%%EOF";

    archivo.close();
}
