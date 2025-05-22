#include <iostream>
#include "../Controller/Registrador.h"
#include "../Model/AdministradorBanco.h"
#include "../Model/CuentaAhorro.h"
#include "../Model/CuentaCorriente.h"
#include "../Controller/Buscador.h"
#include "../Controller/Lector.h"
#include "../Controller/Cajero.h"

using namespace std;

int main() {
    CuentaAhorro cuentaAhorro;
    CuentaCorriente cuentaCorriente;

    Buscador buscadorAhorro(&cuentaAhorro);
    Buscador buscadorCorriente(&cuentaCorriente);

    Lector lectorAhorro(&cuentaAhorro, &buscadorAhorro);
    Lector lectorCorriente(&cuentaCorriente, &buscadorCorriente);

    Cajero cajero(&cuentaAhorro, &cuentaCorriente, &buscadorAhorro, &buscadorCorriente);
    AdministradorBanco adminBanco(&buscadorAhorro, &buscadorCorriente, &lectorAhorro, &lectorCorriente);
    Registrador registrador(&cuentaAhorro, &cuentaCorriente);

    int opcion;

    do {
        cout << "\n========== BANCO XYZ ==========\n";
        cout << "1. Crear nuevo usuario\n";
        cout << "2. Modo administrador\n";
        cout << "3. Hacer depósito\n";
        cout << "4. Hacer transferencia\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                registrador.registrar();
                break;
            }
            case 2: {
                int tipoBusqueda;
                string cedula;
                adminBanco.buscarPorCedula("");
                break;
            }
            case 3: {
                int tipoCuenta;
                string numeroCuenta;
                float monto;

                cout << "Tipo de cuenta (1 = Ahorro, 2 = Corriente): ";
                cin >> tipoCuenta;
                cout << "Número de cuenta: ";
                cin >> numeroCuenta;
                cout << "Monto a depositar: ";
                cin >> monto;

                cajero.depositar(tipoCuenta, numeroCuenta, monto);
                break;
            }
            case 4: {
                int tipoCuentaOrigen, tipoCuentaDestino;
                string cuentaOrigen, cuentaDestino, cedula;
                float monto;

                cout << "Tipo de cuenta de origen (1 = Ahorro, 2 = Corriente): ";
                cin >> tipoCuentaOrigen;
                cout << "Número de cuenta de origen: ";
                cin >> cuentaOrigen;
                cout << "Cédula del dueño de la cuenta origen: ";
                cin >> cedula;

                cout << "Tipo de cuenta de destino (1 = Ahorro, 2 = Corriente): ";
                cin >> tipoCuentaDestino;
                cout << "Número de cuenta de destino: ";
                cin >> cuentaDestino;

                cout << "Monto a transferir: ";
                cin >> monto;

                cajero.transferir(tipoCuentaOrigen, cuentaOrigen, cedula,
                                  tipoCuentaDestino, cuentaDestino, monto);
                break;
            }
            case 5: {
                cout << "Gracias por usar el sistema bancario. ¡Hasta pronto!\n";
                break;
            }
            default: {
                cout << "Opción inválida. Intente de nuevo.\n";
            }
        }

    } while(opcion != 5);

    return 0;
}
