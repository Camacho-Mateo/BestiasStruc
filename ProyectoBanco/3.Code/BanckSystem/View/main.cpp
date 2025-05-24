#include <iostream>
#include <limits>
#include "../Controller/Registrador.h"
#include "../Controller/Cajero.h"
#include "../Model/AdministradorBanco.h"
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "../Controller/Buscador.h"
#include "../Controller/Lector.h"

void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void mostrarMenuPrincipal() {
    std::cout << "\n=== SISTEMA BANCARIO ===" << std::endl;
    std::cout << "1. Registrar nuevo cliente" << std::endl;
    std::cout << "2. Buscar cliente (Administrador)" << std::endl;
    std::cout << "3. Realizar depósito" << std::endl;
    std::cout << "4. Realizar retiro" << std::endl;
    std::cout << "5. Realizar transferencia" << std::endl;
    std::cout << "6. Consultar saldo" << std::endl;
    std::cout << "7. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

int main() {

    CuentaAhorro cuentaAhorro;
    CuentaCorriente cuentaCorriente;
    
    Buscador buscadorAhorro(&cuentaAhorro, nullptr);
    Buscador buscadorCorriente(nullptr, &cuentaCorriente);
    
    Lector lectorAhorro(&cuentaAhorro, nullptr, &buscadorAhorro);
    Lector lectorCorriente(nullptr, &cuentaCorriente, &buscadorCorriente);

    Cajero cajero(&cuentaAhorro, &cuentaCorriente, &buscadorAhorro);
    AdministradorBanco adminBanco(&buscadorAhorro, &buscadorCorriente, 
                                &lectorAhorro, &lectorCorriente);
    Registrador registrador(&cuentaAhorro, &cuentaCorriente);

    int opcion;
    bool ejecutando = true;

    while (ejecutando) {
        mostrarMenuPrincipal();
        std::cin >> opcion;
        limpiarBuffer();

        try {
            switch (opcion) {
                case 1: { 
                    registrador.registrar();
                    break;
                }
                case 2: { 
                    std::string cedula;
                    std::cout << "\nIngrese cédula a buscar: ";
                    std::cin >> cedula;
                    adminBanco.buscarPorCedula(cedula);
                    break;
                }
                case 3: {
                    int tipo;
                    std::string numeroCuenta;
                    double monto;

                    std::cout << "\n=== DEPÓSITO ===" << std::endl;
                    std::cout << "Tipo de cuenta (1: Ahorro, 2: Corriente): ";
                    std::cin >> tipo;
                    std::cout << "Número de cuenta: ";
                    std::cin >> numeroCuenta;
                    std::cout << "Monto a depositar: ";
                    std::cin >> monto;

                    if (cajero.depositar(tipo == 1, numeroCuenta, monto)) {
                        std::cout << "Depósito realizado con éxito." << std::endl;
                    } else {
                        std::cout << "Error al realizar el depósito." << std::endl;
                    }
                    break;
                }
                case 4: { 
                    int tipo;
                    std::string numeroCuenta;
                    double monto;

                    std::cout << "\n=== RETIRO ===" << std::endl;
                    std::cout << "Tipo de cuenta (1: Ahorro, 2: Corriente): ";
                    std::cin >> tipo;
                    std::cout << "Número de cuenta: ";
                    std::cin >> numeroCuenta;
                    std::cout << "Monto a retirar: ";
                    std::cin >> monto;

                    if (cajero.retirar(tipo == 1, numeroCuenta, monto)) {
                        std::cout << "Retiro realizado con éxito." << std::endl;
                    } else {
                        std::cout << "Error al realizar el retiro." << std::endl;
                    }
                    break;
                }
                case 5: {
                    int tipoOrigen, tipoDestino;
                    std::string cuentaOrigen, cuentaDestino, cedula;
                    double monto;

                    std::cout << "\n=== TRANSFERENCIA ===" << std::endl;
                    std::cout << "CUENTA ORIGEN:" << std::endl;
                    std::cout << "Tipo (1: Ahorro, 2: Corriente): ";
                    std::cin >> tipoOrigen;
                    std::cout << "Número de cuenta: ";
                    std::cin >> cuentaOrigen;
                    std::cout << "Cédula del titular: ";
                    std::cin >> cedula;

                    std::cout << "\nCUENTA DESTINO:" << std::endl;
                    std::cout << "Tipo (1: Ahorro, 2: Corriente): ";
                    std::cin >> tipoDestino;
                    std::cout << "Número de cuenta: ";
                    std::cin >> cuentaDestino;

                    std::cout << "\nMonto a transferir: ";
                    std::cin >> monto;

                    if (cajero.transferir(tipoOrigen == 1, cuentaOrigen, cedula, 
                                        tipoDestino == 1, cuentaDestino, monto)) {
                        std::cout << "Transferencia realizada con éxito." << std::endl;
                    } else {
                        std::cout << "Error al realizar la transferencia." << std::endl;
                    }
                    break;
                }
                case 6: {
                    int tipo;
                    std::string numeroCuenta, cedula;

                    std::cout << "\n=== CONSULTA DE SALDO ===" << std::endl;
                    std::cout << "Tipo de cuenta (1: Ahorro, 2: Corriente): ";
                    std::cin >> tipo;
                    std::cout << "Número de cuenta: ";
                    std::cin >> numeroCuenta;
                    std::cout << "Cédula del titular: ";
                    std::cin >> cedula;

                    double saldo = cajero.consultarSaldo(tipo == 1, numeroCuenta, cedula);
                    if (saldo >= 0) {
                        std::cout << "Saldo actual: $" << saldo << std::endl;
                    } else {
                        std::cout << "No se pudo obtener el saldo." << std::endl;
                    }
                    break;
                }
                case 7: {
                    ejecutando = false;
                    std::cout << "\nGracias por usar el sistema bancario. ¡Hasta pronto!" << std::endl;
                    break;
                }
                default: {
                    std::cout << "\nOpción inválida. Intente nuevamente." << std::endl;
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "\nError: " << e.what() << std::endl;
        }

        if (opcion != 7) {
            std::cout << "\nPresione Enter para continuar...";
            limpiarBuffer();
        }
    }

    return 0;
}