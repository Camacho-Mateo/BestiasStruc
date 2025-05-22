#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include <fstream>
using namespace std;

class Persona {
    string nombre;
    string apellido;
    string cedula;
    string correo;
    string telefono;

public:
    Persona();
    Persona(string n, string a, string c, string co, string t);

    string getCedula() const;
    string getNombre() const;

    void mostrar() const;

    void escribir(ofstream& out) const;
    void leer(ifstream& in);
};

#endif
