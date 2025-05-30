#include "Registrador.h"
#include "../Model/Persona.h"
#include "../Model/Fecha.h"
#include "../Model/Validador.h"
#include <iostream>
#include <string>
#include <limits>
#include <conio.h>

using namespace std;

Registrador::Registrador(CuentaAhorro* ca, CuentaCorriente* cc, AdministradorBanco* ab)
    : cuentaAhorro(ca), cuentaCorriente(cc), administradorBanco(ab) {}

void Registrador::registrar() {
    string cedula, nombre, apellido, correo, telefono;
    Fecha fechaNacimiento;

    while (true) {
        try {
            char c;
            cedula.clear();
            cout << "Ingrese la cedula: ";
            while (true) {
                c = getch();
                if (c >= '0' && c <= '9' && cedula.length() < 10) {
                    cout << c;
                    cedula += c;
                } else if (c == 8 && !cedula.empty()) {
                    cout << "\b \b";
                    cedula.pop_back();
                } else if (c == 13 && !cedula.empty()) {
                    break;
                }
            }
            cout << endl;
            Validador::validar(cedula, "cedula");

            if (administradorBanco->estaRegistrada(cedula)) {
                cout << "La cédula ya está registrada. Saltando registro de datos personales.\n";
            }
            break;
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    if (!administradorBanco->estaRegistrada(cedula)) {
        while (true) {
            try {
                char c;
                nombre.clear();
                cout << "Ingrese el nombre: ";
                while (true) {
                    c = getch();
                    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                        cout << c;
                        nombre += c;
                    } else if (c == 8 && !nombre.empty()) {
                        cout << "\b \b";
                        nombre.pop_back();
                    } else if (c == 13 && !nombre.empty()) {
                        break;
                    }
                }
                cout << endl;
                Validador::validar(nombre, "nombre");
                break;
            } catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
        }

        while (true) {
            try {
                char c;
                apellido.clear();
                cout << "Ingrese el apellido: ";
                while (true) {
                    c = getch();
                    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                        cout << c;
                        apellido += c;
                    } else if (c == 8 && !apellido.empty()) {
                        cout << "\b \b";
                        apellido.pop_back();
                    } else if (c == 13 && !apellido.empty()) {
                        break;
                    }
                }
                cout << endl;
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
                char c;
                telefono.clear();
                cout << "Ingrese el telefono: ";
                while (true) {
                    c = getch();
                    if (c >= '0' && c <= '9' && telefono.length() < 15) {
                        cout << c;
                        telefono += c;
                    } else if (c == 8 && !telefono.empty()) {
                        cout << "\b \b";
                        telefono.pop_back();
                    } else if (c == 13 && !telefono.empty()) {
                        break;
                    }
                }
                cout << endl;
                Validador::validar(telefono, "telefono");
                break;
            } catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
        }

        cout << "Ingrese la fecha de nacimiento (DD/MM/AAAA):\n";
        fechaNacimiento.pedirFecha();
    }

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
        cout << "Tipo de cuenta invalido.\n";
    }

    cout << "\nPresione Enter para continuar...";
    cin.get();
}
