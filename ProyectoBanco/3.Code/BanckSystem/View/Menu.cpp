#include "Menu.h"

void Menu::mostrarMenu() {
    Persona persona;
    CuentaAhorro cuentaAhorro;
    CuentaCorriente cuentaCorriente;
    Cajero cajero;
    AdministradorBinario adminBinario;

    bool salir = false;
    while (!salir) {
        cout << "----- Banco Simple -----\n";
        cout << "1. Registrar Persona\n";
        cout << "2. Crear Cuenta Ahorro\n";
        cout << "3. Crear Cuenta Corriente\n";
        cout << "4. Depositar\n";
        cout << "5. Transferir\n";
        cout << "6. Ver Saldo\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        int opcion;
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string nombre, apellido, cedula, correo, telefono;
                cout << "Nombre: ";
                cin >> ws;
                getline(cin, nombre);
                cout << "Apellido: ";
                getline(cin, apellido);
                cout << "Cedula: ";
                getline(cin, cedula);
                cout << "Correo: ";
                getline(cin, correo);
                cout << "Telefono: ";
                getline(cin, telefono);

                if (!Validador::validarNombre(nombre) || !Validador::validarNombre(apellido) ||
                    !Validador::validarCedula(cedula) || !Validador::validarCorreo(correo)) {
                    cout << "Datos invalidos, intente de nuevo.\n";
                    break;
                }

                persona = Persona(nombre, apellido, cedula, correo, telefono);
                Registrador::registrarPersona(persona);
                adminBinario.registrarMovimiento("Registro Persona: " + nombre);
                cout << "Persona registrada correctamente.\n";
                break;
            }
            case 2: {
                string numCuenta;
                cout << "Numero cuenta ahorro: ";
                cin >> numCuenta;
                cuentaAhorro = CuentaAhorro(numCuenta);
                Registrador::registrarCuentaAhorro(cuentaAhorro);
                adminBinario.registrarMovimiento("Creacion Cuenta Ahorro: " + numCuenta);
                cout << "Cuenta ahorro creada.\n";
                break;
            }
            case 3: {
                string numCuenta;
                cout << "Numero cuenta corriente: ";
                cin >> numCuenta;
                cuentaCorriente = CuentaCorriente(numCuenta);
                Registrador::registrarCuentaCorriente(cuentaCorriente);
                adminBinario.registrarMovimiento("Creacion Cuenta Corriente: " + numCuenta);
                cout << "Cuenta corriente creada.\n";
                break;
            }
            case 4: {
                cout << "Depositar en (1) Ahorro (2) Corriente: ";
                int tipoCuenta;
                cin >> tipoCuenta;
                cout << "Cantidad: ";
                double cantidad;
                cin >> cantidad;
                if (tipoCuenta == 1) {
                    cuentaAhorro.depositar(cantidad);
                    adminBinario.registrarMovimiento("Deposito en Ahorro: " + to_string(cantidad));
                } else if (tipoCuenta == 2) {
                    cuentaCorriente.depositar(cantidad);
                    adminBinario.registrarMovimiento("Deposito en Corriente: " + to_string(cantidad));
                }
                cout << "Deposito realizado.\n";
                break;
            }
            case 5: {
                cout << "Transferir de (1) Ahorro a Corriente (2) Corriente a Ahorro: ";
                int tipoTransferencia;
                cin >> tipoTransferencia;
                cout << "Cantidad a transferir: ";
                double cantidad;
                cin >> cantidad;
                bool exito = false;
                if (tipoTransferencia == 1) {
                    exito = cajero.transferir(cuentaAhorro, cuentaCorriente, cantidad);
                } else if (tipoTransferencia == 2) {
                    exito = cajero.transferir(cuentaCorriente, cuentaAhorro, cantidad);
                }
                if (exito) {
                    adminBinario.registrarMovimiento("Transferencia: " + to_string(cantidad));
                    cout << "Transferencia realizada.\n";
                } else {
                    cout << "No hay saldo suficiente.\n";
                }
                break;
            }
            case 6: {
                cout << "Saldo Ahorro: " << cuentaAhorro.getSaldo() << "\n";
                cout << "Saldo Corriente: " << cuentaCorriente.getSaldo() << "\n";
                break;
            }
            case 7: {
                salir = true;
                cout << "Gracias por usar el banco.\n";
                break;
            }
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
}
