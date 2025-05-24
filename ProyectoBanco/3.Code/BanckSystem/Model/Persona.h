#ifndef PERSONA_H
#define PERSONA_H

#include "Fecha.h"
#include <string>

class Persona {
private:
    std::string cedula;
    std::string nombre;
    std::string apellido;
    std::string correo;
    std::string telefono;
    Fecha fechaNacimiento;

public:
    Persona(const std::string& ced, const std::string& nom, const std::string& ape,
           const std::string& corr, const std::string& tel, const Fecha& fecha);
    
    // Getters
    std::string getCedula() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getCorreo() const;
    std::string getTelefono() const;
    Fecha getFechaNacimiento() const;
    
    // Setters
    void setCedula(const std::string& ced);
    void setNombre(const std::string& nom);
    void setApellido(const std::string& ape);
    void setCorreo(const std::string& corr);
    void setTelefono(const std::string& tel);
    void setFechaNacimiento(const Fecha& fecha);
};

#endif