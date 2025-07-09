#include <iostream>
#include <limits>
#include <string>
#include <conio.h>
#include <vector>

#include "../Controller/Registrador.h"
#include "../Controller/Cajero.h"
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "../Controller/Buscador.h"
#include "../Controller/Lector.h"
#include "../Model/AdministradorBanco.h"
#include "../Controller/AdministradorBinario.h"
#include "../Model/Validador.h"
#include "../Controller/Ordenador.h"
#include "../View/MenuInteractivo.h"
#include "../Controller/CalculadoraHash.h"
#include "../Controller/CreadorQR.h"
#include "../View/Marquesina.h"
#include "../View/MenuAyuda.h"
#include "../Controller/Criptador.h"
#include "../Controller/Editor.h"    // <-- Incluido Editor

using namespace std;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Marquesina marquesina;
    marquesina.iniciar();

    CuentaAhorro cuentaAhorro;
    CuentaCorriente cuentaCorriente;

    Buscador buscadorAhorro(&cuentaAhorro, nullptr);
    Buscador buscadorCorriente(nullptr, &cuentaCorriente);

    Lector lectorAhorro(&cuentaAhorro, nullptr, &buscadorAhorro);
    Lector lectorCorriente(nullptr, &cuentaCorriente, &buscadorCorriente);

    AdministradorBinario binario;
    binario.cargarCuentas(cuentaAhorro, cuentaCorriente);

    Cajero cajero(&cuentaAhorro, &cuentaCorriente, &buscadorAhorro, &binario);
    AdministradorBanco adminBanco(&buscadorAhorro, &buscadorCorriente, &lectorAhorro, &lectorCorriente);
    Registrador registrador(&cuentaAhorro, &cuentaCorriente, &adminBanco);
    Editor editor(&cuentaAhorro, &cuentaCorriente, &adminBanco);  // <-- Nueva instancia
    Ordenador ordenador(&cuentaAhorro, &cuentaCorriente);
    CalculadoraHash calculadoraHash(&cuentaAhorro, &cuentaCorriente);
    CreadorQR creadorQR(&cuentaAhorro, &cuentaCorriente);
    MenuAyuda menuAyuda;
    Criptador criptador;

    vector<string> opcionesMenu = {
        "Registrar nuevo cliente",
        "Buscar cliente (Administrador)",
        "Realizar deposito",
        "Realizar retiro",
        "Realizar transferencia",
        "Consultar saldo",
        "Crear backup de cuentas",
        "Restaurar backup de cuentas",
        "Ordenar y mostrar cuentas",
        "Generar hashes MD5 del archivo binario",
        "Generar QR de usuarios",
        "Encriptar backup existente",
        "Editar cliente",       // <-- Nueva opción
        "Ayuda",
        "Salir"
    };

    int opcion = 0;
    bool salir = false;

    while (!salir) {
        MenuInteractivo menu(opcionesMenu);
        opcion = menu.ejecutar();

        switch (opcion) {
            case 1:
                registrador.registrar();
                break;

            case 2: {
                vector<string> opcionesBusqueda = {
                    "Buscar por cedula",
                    "Buscar por numero de cuenta"
                };
                MenuInteractivo menuBusqueda(opcionesBusqueda);
                int subopcion = menuBusqueda.ejecutar();

                if (subopcion == 1) {
                    string cedula;
                    cout << "\nIngrese cedula a buscar: ";
                    getline(cin, cedula);
                    adminBanco.buscarPorCedula(cedula);
                } else if (subopcion == 2) {
                    adminBanco.buscarPorNumeroCuenta();
                }
                break;
            }

            case 3: {
                int tipo;
                string numeroCuenta;
                double monto;

                vector<string> opcionesTipo = {"Cuenta Ahorro", "Cuenta Corriente"};
                MenuInteractivo menuTipo(opcionesTipo);
                tipo = menuTipo.ejecutar();

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

                vector<string> opcionesTipo = {"Cuenta Ahorro", "Cuenta Corriente"};
                MenuInteractivo menuTipo(opcionesTipo);
                tipo = menuTipo.ejecutar();

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

                vector<string> opcionesTipo = {"Cuenta Ahorro", "Cuenta Corriente"};

                cout << "CUENTA ORIGEN:" << endl;
                MenuInteractivo menuOrigen(opcionesTipo);
                tipoOrigen = menuOrigen.ejecutar();

                cout << "Numero de cuenta: ";
                getline(cin, cuentaOrigen);

                cout << "Cedula del titular: ";
                getline(cin, cedula);

                cout << "\nCUENTA DESTINO:" << endl;
                MenuInteractivo menuDestino(opcionesTipo);
                tipoDestino = menuDestino.ejecutar();

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

                vector<string> opcionesTipo = {"Cuenta Ahorro", "Cuenta Corriente"};
                MenuInteractivo menuTipo(opcionesTipo);
                tipo = menuTipo.ejecutar();

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

            case 7:
                cout << "\nCreando backup de las cuentas..." << endl;
                binario.crearBackup();
                cout << "Backup creado exitosamente." << endl;
                break;

            case 8:
                cout << "\nRestaurando backup de las cuentas..." << endl;
                binario.restaurarBackup();
                binario.cargarCuentas(cuentaAhorro, cuentaCorriente);
                cout << "Backup restaurado correctamente." << endl;
                break;

            case 9: {
                vector<string> opcionesOrden = {
                    "Ordenar por nombre",
                    "Ordenar por numero de cuenta"
                };
                MenuInteractivo menuOrden(opcionesOrden);
                int criterio = menuOrden.ejecutar();

                if (criterio == 1) {
                    ordenador.ordenarPorNombre(true);
                    ordenador.ordenarPorNombre(false);
                } else {
                    ordenador.ordenarPorNumeroCuenta(true);
                    ordenador.ordenarPorNumeroCuenta(false);
                }
                break;
            }

            case 10:
                calculadoraHash.generarArchivoHash("hashes_md5.txt");
                cout << "\nArchivo de hashes generado: hashes_md5.txt\n";
                break;

            case 11:
                creadorQR.generarPDFs();
                cout << "\nQRs generados exitosamente para todos los usuarios.\n";
                break;

            case 12:
                criptador.enigma();
                break;

            case 13:
                editor.ejecutar();  // <-- Nueva opción Ejecutar Editor
                break;

            case 14:
                menuAyuda.mostrarAyuda();
                break;

            case 15:
                cout << "\nGracias por usar el sistema bancario. ¡Hasta pronto!" << endl;
                salir = true;
                break;

            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
                break;
        }

        if (!salir) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    binario.guardarCuentas(cuentaAhorro, cuentaCorriente);
    marquesina.detener();

    return 0;
}
