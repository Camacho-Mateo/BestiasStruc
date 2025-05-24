#ifndef FECHA_H
#define FECHA_H

class Fecha {
private:
    char* fechaNacimiento;

public:
    Fecha();
    ~Fecha();
    
    void pedirFecha();
    const char* getFecha() const;
};

#endif