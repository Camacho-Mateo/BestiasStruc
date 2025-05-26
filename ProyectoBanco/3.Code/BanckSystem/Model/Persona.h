#ifndef PERSONA_H
#define PERSONA_H

#include "Fecha.h"
#include <string>
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
    Persona(const string& ced, const string& nom, const string& ape,
           const string& corr, const string& tel, const Fecha& fecha);
    
    string getCedula() const;
    string getNombre() const;
    string getApellido() const;
    string getCorreo() const;
    string getTelefono() const;
    Fecha getFechaNacimiento() const;
    
    void setCedula(const string& ced);
    void setNombre(const string& nom);
    void setApellido(const string& ape);
    void setCorreo(const string& corr);
    void setTelefono(const string& tel);
    void setFechaNacimiento(const Fecha& fecha);
};

#endif
