#include "AdministradorBinario.h"
#include <fstream>
#include <iostream>

void AdministradorBinario::registrarMovimiento(const std::string& cedula, const std::string& tipoMovimiento, 
                                             double monto, const std::string& fecha, double saldoFinal) {
    std::ofstream archivo("movimientos.bin", std::ios::binary | std::ios::app);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo binario para registrar movimiento." << std::endl;
        return;
    }

    Movimiento mov;
    mov.cedula = cedula;
    mov.tipoMovimiento = tipoMovimiento;
    mov.monto = monto;
    mov.fecha = fecha;
    mov.saldoFinal = saldoFinal;

    size_t tamCedula = mov.cedula.size();
    size_t tamTipo = mov.tipoMovimiento.size();
    size_t tamFecha = mov.fecha.size();

    archivo.write(reinterpret_cast<char*>(&tamCedula), sizeof(tamCedula));
    archivo.write(mov.cedula.c_str(), tamCedula);

    archivo.write(reinterpret_cast<char*>(&tamTipo), sizeof(tamTipo));
    archivo.write(mov.tipoMovimiento.c_str(), tamTipo);

    archivo.write(reinterpret_cast<char*>(&mov.monto), sizeof(mov.monto));

    archivo.write(reinterpret_cast<char*>(&tamFecha), sizeof(tamFecha));
    archivo.write(mov.fecha.c_str(), tamFecha);

    archivo.write(reinterpret_cast<char*>(&mov.saldoFinal), sizeof(mov.saldoFinal));

    archivo.close();
}