#include "Registrador.h"
#include "../Model/Persona.h"
#include "../Model/Fecha.h"
#include "../Model/Validador.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

Registrador::Registrador(CuentaAhorro* ca, CuentaCorriente* cc)
    : cuentaAhorro(ca), cuentaCorriente(cc) {}

void Registrador::registrar() {
    string cedula, nombre, apellido, correo, telefono;
    Fecha fechaNacimiento;

    while (true) {
        try {
            cout << "Ingrese la cédula: ";
            cin >> cedula;
            Validador::validar(cedula, "cedula");
            break;
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    cin.ignore();

    while (true) {
        try {
            cout << "Ingrese el nombre: ";
            getline(cin, nombre);
            Validador::validar(nombre, "nombre");
            break;
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    while (true) {
        try {
            cout << "Ingrese el apellido: ";
            getline(cin, apellido);
            Validador::validar(apellido, "apellido");
            break;
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    while (true) {
        try {
            cout << "Ingrese el correo: ";
            getline(cin, correo);
            Validador::validar(correo, "correo");
            break;
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    while (true) {
        try {
            cout << "Ingrese el teléfono: ";
            getline(cin, telefono);
            Validador::validar(telefono, "telefono");
            break;
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    cout << "Ingrese la fecha de nacimiento (DD/MM/AAAA):\n";
    fechaNacimiento.pedirFecha();

    Persona persona(cedula, nombre, apellido, correo, telefono, fechaNacimiento);

    int tipoCuenta;
    cout << "Tipo de cuenta (1: Ahorro, 2: Corriente): ";
    cin >> tipoCuenta;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (tipoCuenta == 1) {
        cuentaAhorro->agregarCuenta(
            persona.getCedula(),
            persona.getNombre(),
            cuentaAhorro->generarNumeroCuenta(),
            0.0
        );
        cout << "Cuenta de ahorro registrada exitosamente.\n";

        administradorBinario.guardarCuentas(*cuentaAhorro, *cuentaCorriente);

    } else if (tipoCuenta == 2) {
        cuentaCorriente->agregarCuenta(
            persona.getCedula(),
            persona.getNombre(),
            cuentaCorriente->generarNumeroCuenta(),
            0.0
        );
        cout << "Cuenta corriente registrada exitosamente.\n";

        administradorBinario.guardarCuentas(*cuentaAhorro, *cuentaCorriente);

    } else {
        cout << "Tipo de cuenta inválido.\n";
    }

    cout << "\nPresione Enter para continuar...";
    cin.get();
}
