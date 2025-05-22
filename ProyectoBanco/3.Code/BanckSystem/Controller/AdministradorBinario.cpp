#include "AdministradorBinario.h"
#include <iostream>
using namespace std;

void Evento::escribir(ofstream& out) const {
    size_t len = descripcion.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(descripcion.c_str(), len);
    fecha.escribir(out);
}

void Evento::leer(ifstream& in) {
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    char* buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    descripcion = buffer;
    delete[] buffer;
    fecha.leer(in);
}

AdministradorBinario::AdministradorBinario(const string& archivo) : nombreArchivo(archivo) {}

void AdministradorBinario::registrarEvento(const string& descripcion, const Fecha& fecha) {
    ofstream out(nombreArchivo, ios::binary | ios::app);
    Evento evento{descripcion, fecha};
    evento.escribir(out);
    out.close();
}

void AdministradorBinario::leerEventos() const {
    ifstream in(nombreArchivo, ios::binary);
    if (!in) {
        cout << "No hay eventos registrados.\n";
        return;
    }
    while (in.peek() != EOF) {
        Evento evento;
        evento.leer(in);
        cout << evento.fecha.toString() << " - " << evento.descripcion << "\n";
    }
    in.close();
}
