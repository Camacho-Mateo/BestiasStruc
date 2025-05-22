#include "Persona.h"
#include <iostream>
using namespace std;

Persona::Persona() {}

Persona::Persona(string n, string a, string c, string co, string t)
    : nombre(n), apellido(a), cedula(c), correo(co), telefono(t) {}

string Persona::getCedula() const { return cedula; }
string Persona::getNombre() const { return nombre; }

void Persona::mostrar() const {
    cout << "Nombre: " << nombre << " " << apellido << "\n";
    cout << "Cedula: " << cedula << "\n";
    cout << "Correo: " << correo << "\n";
    cout << "Telefono: " << telefono << "\n";
}

void Persona::escribir(ofstream& out) const {
    size_t len;

    len = nombre.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(nombre.c_str(), len);

    len = apellido.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(apellido.c_str(), len);

    len = cedula.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(cedula.c_str(), len);

    len = correo.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(correo.c_str(), len);

    len = telefono.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(telefono.c_str(), len);
}

void Persona::leer(ifstream& in) {
    size_t len;
    char* buffer;

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    nombre = buffer;
    delete[] buffer;

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    apellido = buffer;
    delete[] buffer;

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    cedula = buffer;
    delete[] buffer;

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    correo = buffer;
    delete[] buffer;

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    telefono = buffer;
    delete[] buffer;
}
