#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include "Fecha.h"

using namespace std;

class Persona {
private:
    string cedula;
    string nombre;
    string apellido;
    string correo;
    string telefono;
    Fecha fechaNacimiento;

public:
    Persona() = default;
    Persona(string cedula, string nombre, string apellido, string correo, string telefono, Fecha fechaNacimiento);

    string getCedula() const;
    string getNombre() const;
    string getApellido() const;
    string getCorreo() const;
    string getTelefono() const;
    Fecha getFechaNacimiento() const;

    void setCedula(string cedula);
    void setNombre(string nombre);
    void setApellido(string apellido);
    void setCorreo(string correo);
    void setTelefono(string telefono);
    void setFechaNacimiento(Fecha fechaNacimiento);
};

#endif
