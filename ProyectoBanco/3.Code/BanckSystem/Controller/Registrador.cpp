#include "Registrador.h"

Registrador::Registrador(CuentaAhorro* ca, CuentaCorriente* cc)
    : cuentaAhorro(ca), cuentaCorriente(cc) {}

void Registrador::registrarPersona() {
    string cedula, nombre, apellido, correo, telefono;
    Fecha fechaNacimiento;

    while (true) {
        try {
            cout << "Ingrese la cedula: ";
            cin >> cedula;
            Validador::validar(cedula, "cedula");
            break;
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    while (true) {
        try {
            cout << "Ingrese el nombre: ";
            cin.ignore();
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
            cout << "Ingrese el telefono: ";
            getline(cin, telefono);
            Validador::validar(telefono, "telefono");
            break;
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    cout << "Ingrese la fecha de nacimiento:" << endl;
    fechaNacimiento.pedirFecha();

    Persona persona(cedula, nombre, apellido, correo, telefono, fechaNacimiento);

    int tipoCuenta;
    cout << "Tipo de cuenta (1: Ahorro, 2: Corriente): ";
    cin >> tipoCuenta;

    if (tipoCuenta == 1) {
        cuentaAhorro->agregarCuenta(&persona);
        cout << "Cuenta de ahorro registrada exitosamente.\n";
    } else if (tipoCuenta == 2) {
        cuentaCorriente->agregarCuenta(&persona);
        cout << "Cuenta corriente registrada exitosamente.\n";
    } else {
        cout << "Tipo de cuenta invalido.\n";
    }
}
