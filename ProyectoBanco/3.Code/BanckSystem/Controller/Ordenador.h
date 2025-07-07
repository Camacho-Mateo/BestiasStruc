#ifndef ORDENADOR_H
#define ORDENADOR_H

#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include <vector>
#include <string>

struct Registro {
    std::string nombre;
    std::string cedula;
    std::string numeroCuenta;
    double saldo;
};

class Ordenador {
private:
    CuentaAhorro* cuentaAhorro;
    CuentaCorriente* cuentaCorriente;

    void quickSort(std::vector<Registro>& vec, int low, int high, bool ordenarPorNombre);
    int partition(std::vector<Registro>& vec, int low, int high, bool ordenarPorNombre);
    void bucketSort(std::vector<Registro>& vec);
    void imprimir(const std::vector<Registro>& vec, bool esAhorro);

public:
    Ordenador(CuentaAhorro* ca, CuentaCorriente* cc);
    void ordenarPorNombre(bool esAhorro);
    void ordenarPorNumeroCuenta(bool esAhorro);
};

#endif
