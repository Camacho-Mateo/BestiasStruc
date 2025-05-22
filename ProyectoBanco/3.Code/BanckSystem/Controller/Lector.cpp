#include "Lector.h"
#include <iostream>

Lector::Lector(Buscador* buscador) {
    this->buscador = buscador;
}

void Lector::mostrarDatosPorCuenta(const string& numeroCuenta) {
    int fila = buscador->buscarPorCuenta(numeroCuenta);
    if (fila == -1) {
        cout << "Cuenta no encontrada.\n";
        return;
    }


    auto datos = buscador->obtenerDatosPorFila(fila);

    cout << "Datos de la cuenta:\n";
    cout << "Número de cuenta: " << datos.numeroCuenta << "\n";
    cout << "Nombre: " << datos.persona.getNombre() << "\n";
    cout << "Apellido: " << datos.persona.getApellido() << "\n";
    cout << "Cédula: " << datos.persona.getCedula() << "\n";
    cout << "Correo: " << datos.persona.getCorreo() << "\n";
    cout << "Teléfono: " << datos.persona.getTelefono() << "\n";
    cout << "Saldo: " << datos.saldo << "\n";
}

void Lector::mostrarDatosPorCedula(const string& cedula) {
    int fila = buscador->buscarPorCedula(cedula);
    if (fila == -1) {
        cout << "Usuario no encontrado.\n";
        return;
    }

    auto datos = buscador->obtenerDatosPorFila(fila);

    cout << "Datos del usuario:\n";
    cout << "Número de cuenta: " << datos.numeroCuenta << "\n";
    cout << "Nombre: " << datos.persona.getNombre() << "\n";
    cout << "Apellido: " << datos.persona.getApellido() << "\n";
    cout << "Cédula: " << datos.persona.getCedula() << "\n";
    cout << "Correo: " << datos.persona.getCorreo() << "\n";
    cout << "Teléfono: " << datos.persona.getTelefono() << "\n";
    cout << "Saldo: " << datos.saldo << "\n";
}

