#include "Registrador.h"
#include "../Model/Persona.h"
#include "../Model/Fecha.h"
#include "../Model/Validador.h"
#include "../View/MenuInteractivo.h"
#include <iostream>
#include <string>
#include <limits>
#include <conio.h>
#include <map>
#include <ctime>

using namespace std;

Registrador::Registrador(CuentaAhorro* ca, CuentaCorriente* cc, AdministradorBanco* ab)
    : cuentaAhorro(ca), cuentaCorriente(cc), administradorBanco(ab) {}

std::string obtenerFechaActual() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", now);
    return string(buffer);
}

void Registrador::registrar() {
    string cedula;
    Fecha fechaNacimiento;

    // Pedir cédula y validar
    while (true) {
        try {
            char c;
            cedula.clear();
            cout << "Ingrese la cedula: ";
            while (true) {
                c = getch();
                if (isdigit(c) && cedula.length() < 10) {
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
            break;
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    string nombre, apellido, correo, telefono, codigoSucursal;

    if (administradorBanco->estaRegistrada(cedula)) {
        cout << "La cédula ya está registrada. Se usarán los datos existentes.\n";

        bool encontrado = false;

        size_t totalAhorro = cuentaAhorro->getTotalCuentas();
        for (size_t i = 0; i < totalAhorro; ++i) {
            if (cuentaAhorro->getCedula(i) == cedula) {
                nombre = cuentaAhorro->getNombre(i);
                correo = cuentaAhorro->getCorreo(i);
                telefono = cuentaAhorro->getTelefono(i);
                codigoSucursal = cuentaAhorro->getSucursal(i);
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            size_t totalCorriente = cuentaCorriente->getTotalCuentas();
            for (size_t i = 0; i < totalCorriente; ++i) {
                if (cuentaCorriente->getCedula(i) == cedula) {
                    nombre = cuentaCorriente->getNombre(i);
                    correo = cuentaCorriente->getCorreo(i);
                    telefono = cuentaCorriente->getTelefono(i);
                    codigoSucursal = cuentaCorriente->getSucursal(i);
                    encontrado = true;
                    break;
                }
            }
        }

        if (!encontrado) {
            cout << "Error: Cédula registrada pero no se encontraron datos asociados.\n";
            return;
        }
    } else {
        while (true) {
            try {
                char c;
                nombre.clear();
                cout << "Ingrese el nombre: ";
                while (true) {
                    c = getch();
                    if (isalpha(c)) {
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
                    if (isalpha(c)) {
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
                    if (isdigit(c) && telefono.length() < 15) {
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

        nombre = nombre + " " + apellido;

        map<int, pair<string, string>> sucursalesPichincha = {
            {1, {"Quito", "01"}},
            {2, {"Ruminiahui", "02"}},
            {3, {"Cayambe", "03"}},
            {4, {"Mejia", "04"}},
            {5, {"Pedro Moncayo", "05"}},
            {6, {"Pedro Vicente Maldonado", "06"}},
            {7, {"Puerto Quito", "07"}},
            {8, {"San Miguel de los Bancos", "08"}}
        };

        vector<string> nombresSucursales;
        for (const auto& s : sucursalesPichincha) {
            nombresSucursales.push_back(s.second.first);
        }

        MenuInteractivo menuSucursal(nombresSucursales);
        int seleccion = menuSucursal.ejecutar();
        codigoSucursal = sucursalesPichincha[seleccion].second;
    }

    string fechaRegistro = obtenerFechaActual();

    MenuInteractivo menuTipo({ "Cuenta de Ahorro", "Cuenta Corriente" });
    int tipoCuenta = menuTipo.ejecutar();

    if (tipoCuenta == 1) {
        cuentaAhorro->setCodigoSucursal(codigoSucursal);
        cuentaAhorro->agregarCuenta(
            cedula,
            nombre,
            cuentaAhorro->generarNumeroCuenta(),
            0.0,
            telefono,
            correo,
            codigoSucursal,
            fechaRegistro
        );
        cout << "Cuenta de ahorro registrada exitosamente.\n";

    } else if (tipoCuenta == 2) {
        cuentaCorriente->setCodigoSucursal(codigoSucursal);
        cuentaCorriente->agregarCuenta(
            cedula,
            nombre,
            cuentaCorriente->generarNumeroCuenta(),
            0.0,
            telefono,
            correo,
            codigoSucursal,
            fechaRegistro
        );
        cout << "Cuenta corriente registrada exitosamente.\n";

    } else {
        cout << "Tipo de cuenta invalido.\n";
        return;
    }

    administradorBinario.guardarCuentas(*cuentaAhorro, *cuentaCorriente);

    cout << "\nPresione Enter para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}
