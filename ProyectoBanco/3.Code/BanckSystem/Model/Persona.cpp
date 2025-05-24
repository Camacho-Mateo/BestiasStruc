#include "Persona.h"

Persona::Persona(const std::string& ced, const std::string& nom, const std::string& ape,
               const std::string& corr, const std::string& tel, const Fecha& fecha)
    : cedula(ced), nombre(nom), apellido(ape), correo(corr), telefono(tel), fechaNacimiento(fecha) {}

// Implementación de getters
std::string Persona::getCedula() const { return cedula; }
std::string Persona::getNombre() const { return nombre; }
std::string Persona::getApellido() const { return apellido; }
std::string Persona::getCorreo() const { return correo; }
std::string Persona::getTelefono() const { return telefono; }
Fecha Persona::getFechaNacimiento() const { return fechaNacimiento; }

// Implementación de setters
void Persona::setCedula(const std::string& ced) { cedula = ced; }
void Persona::setNombre(const std::string& nom) { nombre = nom; }
void Persona::setApellido(const std::string& ape) { apellido = ape; }
void Persona::setCorreo(const std::string& corr) { correo = corr; }
void Persona::setTelefono(const std::string& tel) { telefono = tel; }
void Persona::setFechaNacimiento(const Fecha& fecha) { fechaNacimiento = fecha; }