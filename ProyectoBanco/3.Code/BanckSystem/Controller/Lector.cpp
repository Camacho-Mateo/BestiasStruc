#include "Lector.h"
#include <iostream>
#include <fstream>

using namespace std;

Lector::Lector(AdministradorBinario& admin) : adminBinario(admin) {}

void Lector::leerHistorialCuenta(const string& numeroCuenta) const {
    ifstream in(adminBinario.getArchivo(), ios::binary);
    if (!in) {
        cout << "No hay historial.\n";
        return;
    }
    while (in.peek() != EOF) {
        Evento evento;
        evento.leer(in);
        if (evento.descripcion.find(numeroCuenta) != string::npos) {
            cout << evento.fecha.toString() << " - " << evento.descripcion << "\n";
        }
    }
    in.close();
}
