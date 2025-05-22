#ifndef ADMINISTRADORBINARIO_H
#define ADMINISTRADORBINARIO_H

#include <string>
#include <fstream>
#include "../Model/Fecha.h"
using namespace std;

struct Evento {
    string descripcion;
    Fecha fecha;

    void escribir(ofstream& out) const;
    void leer(ifstream& in);
};

class AdministradorBinario {
    string nombreArchivo;

public:
    AdministradorBinario(const string& archivo);

    void registrarEvento(const string& descripcion, const Fecha& fecha);
    void leerEventos() const;
};

#endif
