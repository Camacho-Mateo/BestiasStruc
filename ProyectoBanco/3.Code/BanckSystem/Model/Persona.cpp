#include "Persona.h"

Persona::Persona(string cedula, string nombre, string apellido, string correo, string telefono, Fecha fechaNacimiento)
    : cedula(cedula), nombre(nombre), apellido(apellido), correo(correo), telefono(telefono), fechaNacimiento(fechaNacimiento) {}

string Persona::getCedula() const { return cedula; }
string Persona::getNombre() const { return nombre; }
string Persona::getApellido() const { return apellido; }
string Persona::getCorreo() const { return correo; }
string Persona::getTelefono() const { return telefono; }
Fecha Persona::getFechaNacimiento() const { return fechaNacimiento; }

void Persona::setCedula(string cedula) { this->cedula = cedula; }
void Persona::setNombre(string nombre) { this->nombre = nombre; }
void Persona::setApellido(string apellido) { this->apellido = apellido; }
void Persona::setCorreo(string correo) { this->correo = correo; }
void Persona::setTelefono(string telefono) { this->telefono = telefono; }
void Persona::setFechaNacimiento(Fecha fechaNacimiento) { this->fechaNacimiento = fechaNacimiento; }