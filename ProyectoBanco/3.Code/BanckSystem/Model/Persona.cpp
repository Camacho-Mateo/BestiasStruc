#include "Persona.h"
using namespace std;

Persona::Persona(const std::string& ced, const std::string& nom, const std::string& ape,
               const std::string& corr, const std::string& tel, const Fecha& fecha)
    : cedula(ced), nombre(nom), apellido(ape), correo(corr), telefono(tel), fechaNacimiento(fecha) {}

string Persona::getCedula() const { return cedula; }
string Persona::getNombre() const { return nombre; }
string Persona::getApellido() const { return apellido; }
string Persona::getCorreo() const { return correo; }
string Persona::getTelefono() const { return telefono; }
Fecha Persona::getFechaNacimiento() const { return fechaNacimiento; }

void Persona::setCedula(const string& ced) { cedula = ced; }
void Persona::setNombre(const string& nom) { nombre = nom; }
void Persona::setApellido(const string& ape) { apellido = ape; }
void Persona::setCorreo(const string& corr) { correo = corr; }
void Persona::setTelefono(const string& tel) { telefono = tel; }
void Persona::setFechaNacimiento(const Fecha& fecha) { fechaNacimiento = fecha; }
