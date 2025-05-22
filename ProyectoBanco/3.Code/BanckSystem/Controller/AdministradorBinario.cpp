#include "AdministradorBinario.h"
#include <fstream>
#include <iostream>


void AdministradorBinario::registrarMovimiento(const string& cedula, const string& tipoMovimiento, double monto, const string& fecha, double saldoFinal) {
    ofstream archivo("movimientos.bin", ios::binary | ios::app);
    if (!archivo) {
        cerr << "Error al abrir archivo binario para registrar movimiento.\n";
        return;
    }


    Movimiento mov;
    mov.cedula = cedula;
    mov.tipoMovimiento = tipoMovimiento;
    mov.monto = monto;
    mov.fecha = fecha;
    mov.saldoFinal = saldoFinal;

    archivo.write(reinterpret_cast<const char*>(&mov), sizeof(Movimiento));
    archivo.close();
}
