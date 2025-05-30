#include <iostream>
#include <limits>
#include <string>
#include "../Controller/Registrador.h"
#include "../Controller/Cajero.h"
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "../Controller/Buscador.h"
#include "../Controller/Lector.h"
#include "../Model/AdministradorBanco.h"
#include "../Controller/AdministradorBinario.h"
#include "../Model/Validador.h"

using namespace std;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void mostrarMenuPrincipal() {
    cout << "\n=== SISTEMA BANCARIO ===" << endl;
    cout << "1. Registrar nuevo cliente" << endl;
    cout << "2. Buscar cliente (Administrador)" << endl;
    cout << "3. Realizar deposito" << endl;
    cout << "4. Realizar retiro" << endl;
    cout << "5. Realizar transferencia" << endl;
    cout << "6. Consultar saldo" << endl;
    cout << "7. Salir" << endl;
    cout << "8. Crear backup de cuentas" << endl;
    cout << "9. Restaurar backup de cuentas" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    CuentaAhorro cuentaAhorro;
    CuentaCorriente cuentaCorriente;

    Buscador buscadorAhorro(&cuentaAhorro, nullptr);
    Buscador buscadorCorriente(nullptr, &cuentaCorriente);

    Lector lectorAhorro(&cuentaAhorro, nullptr, &buscadorAhorro);
    Lector lectorCorriente(nullptr, &cuentaCorriente, &buscadorCorriente);

    Cajero cajero(&cuentaAhorro, &cuentaCorriente, &buscadorAhorro);
    AdministradorBanco adminBanco(&buscadorAhorro, &buscadorCorriente, &lectorAhorro, &lectorCorriente);
    Registrador registrador(&cuentaAhorro, &cuentaCorriente, &adminBanco);

    AdministradorBinario binario;
    binario.cargarCuentas(cuentaAhorro, cuentaCorriente);

    int opcion = 0;

    while (opcion != 7) {
        mostrarMenuPrincipal();

        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Intente nuevamente.\n";
            limpiarBuffer();
            continue;
        }

        limpiarBuffer();

        switch (opcion) {
            case 1:
                registrador.registrar();
                break;

            case 2: {
                int subopcion;
                cout << "\n=== BUSQUEDA DE CLIENTE ===\n";
                cout << "1. Buscar por cedula\n";
                cout << "2. Buscar por numero de cuenta\n";
                cout << "Seleccione una opcion: ";
                if (!(cin >> subopcion)) {
                    cout << "Entrada invalida.\n";
                    limpiarBuffer();
                    break;
                }
                limpiarBuffer();

                if (subopcion == 1) {
                    string cedula;
                    cout << "\nIngrese cedula a buscar: ";
                    getline(cin, cedula);
                    adminBanco.buscarPorCedula(cedula);
                } else if (subopcion == 2) {
                    adminBanco.buscarPorNumeroCuenta();
                } else {
                    cout << "Opcion invalida.\n";
                }
                break;
            }

            case 3: {
                int tipo;
                string numeroCuenta;
                double monto;

                cout << "\n=== DEPOSITO ===" << endl;
                cout << "Tipo de cuenta (1: Ahorro, 2: Corriente): ";
                if (!(cin >> tipo) || (tipo != 1 && tipo != 2)) {
                    cout << "Entrada invalida. Debe ser 1 o 2.\n";
                    limpiarBuffer();
                    break;
                }
                limpiarBuffer();

                cout << "Numero de cuenta: ";
                getline(cin, numeroCuenta);

                cout << "Monto a depositar: ";
                monto = stod(Validador::validarCantidad());

                if (cajero.depositar(tipo == 1, numeroCuenta, monto)) {
                    cout << "Deposito realizado con exito." << endl;
                } else {
                    cout << "Error al realizar el deposito." << endl;
                }
                break;
            }

            case 4: {
                int tipo;
                string numeroCuenta;
                double monto;

                cout << "\n=== RETIRO ===" << endl;
                cout << "Tipo de cuenta (1: Ahorro, 2: Corriente): ";
                if (!(cin >> tipo) || (tipo != 1 && tipo != 2)) {
                    cout << "Entrada invalida. Debe ser 1 o 2.\n";
                    limpiarBuffer();
                    break;
                }
                limpiarBuffer();

                cout << "Numero de cuenta: ";
                getline(cin, numeroCuenta);

                cout << "Monto a retirar: ";
                monto = stod(Validador::validarCantidad());

                if (cajero.retirar(tipo == 1, numeroCuenta, monto)) {
                    cout << "Retiro realizado con exito." << endl;
                } else {
                    cout << "Error al realizar el retiro." << endl;
                }
                break;
            }

            case 5: {
                int tipoOrigen, tipoDestino;
                string cuentaOrigen, cuentaDestino, cedula;
                double monto;

                cout << "\n=== TRANSFERENCIA ===" << endl;
                cout << "CUENTA ORIGEN:" << endl;
                cout << "Tipo (1: Ahorro, 2: Corriente): ";
                if (!(cin >> tipoOrigen) || (tipoOrigen != 1 && tipoOrigen != 2)) {
                    cout << "Entrada invalida. Debe ser 1 o 2.\n";
                    limpiarBuffer();
                    break;
                }
                limpiarBuffer();

                cout << "Numero de cuenta: ";
                getline(cin, cuentaOrigen);

                cout << "Cedula del titular: ";
                getline(cin, cedula);

                cout << "\nCUENTA DESTINO:" << endl;
                cout << "Tipo (1: Ahorro, 2: Corriente): ";
                if (!(cin >> tipoDestino) || (tipoDestino != 1 && tipoDestino != 2)) {
                    cout << "Entrada invalida. Debe ser 1 o 2.\n";
                    limpiarBuffer();
                    break;
                }
                limpiarBuffer();

                cout << "Numero de cuenta: ";
                getline(cin, cuentaDestino);

                cout << "\nMonto a transferir: ";
                monto = stod(Validador::validarCantidad());

                if (cajero.transferir(tipoOrigen == 1, cuentaOrigen, cedula,
                                      tipoDestino == 1, cuentaDestino, monto)) {
                    cout << "Transferencia realizada con exito." << endl;
                } else {
                    cout << "Error al realizar la transferencia." << endl;
                }
                break;
            }

            case 6: {
                int tipo;
                string numeroCuenta, cedula;

                cout << "\n=== CONSULTA DE SALDO ===" << endl;
                cout << "Tipo de cuenta (1: Ahorro, 2: Corriente): ";
                if (!(cin >> tipo) || (tipo != 1 && tipo != 2)) {
                    cout << "Entrada invalida. Debe ser 1 o 2.\n";
                    limpiarBuffer();
                    break;
                }
                limpiarBuffer();

                cout << "Numero de cuenta: ";
                getline(cin, numeroCuenta);

                cout << "Cedula del titular: ";
                getline(cin, cedula);

                double saldo = cajero.consultarSaldo(tipo == 1, numeroCuenta, cedula);
                if (saldo >= 0) {
                    cout << "Saldo actual: $" << saldo << endl;
                } else {
                    cout << "No se pudo obtener el saldo." << endl;
                }
                break;
            }

            case 8:
                cout << "\nCreando backup de las cuentas..." << endl;
                binario.crearBackup();
                cout << "Backup creado exitosamente." << endl;
                break;

            case 9:
                cout << "\nRestaurando backup de las cuentas..." << endl;
                binario.restaurarBackup();
                binario.cargarCuentas(cuentaAhorro, cuentaCorriente);
                cout << "Backup restaurado correctamente." << endl;
                break;

            case 7:
                cout << "\nGracias por usar el sistema bancario. ¡Hasta pronto!" << endl;
                break;

            default:
                cout << "\nOpcion invalida. Intente nuevamente." << endl;
                break;
        }

        if (opcion != 7) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    binario.guardarCuentas(cuentaAhorro, cuentaCorriente);

    return 0;
}
