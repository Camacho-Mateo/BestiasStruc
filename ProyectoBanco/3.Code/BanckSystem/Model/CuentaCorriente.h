#ifndef CUENTACORRIENTE_H
#define CUENTACORRIENTE_H

#include <vector>
#include <string>

class CuentaCorriente {
private:
    std::vector<std::string> cedulas;
    std::vector<std::string> nombres;
    std::vector<std::string> numerosCuenta;
    std::vector<double> saldos;
    std::vector<std::string> telefonos;
    std::vector<std::string> correos;
    std::vector<std::string> sucursales;

    std::string codigoSucursal;
    static size_t contadorCuentas;

public:
    CuentaCorriente();

    size_t getTotalCuentas() const;

    std::string getCedula(size_t index) const;
    std::string getNombre(size_t index) const;
    std::string getNumeroCuentaStr(size_t index) const;
    double getSaldo(size_t index) const;
    std::string getTelefono(size_t index) const;
    std::string getCorreo(size_t index) const;
    std::string getSucursal(size_t index) const;

    void setSaldo(size_t index, double nuevoSaldo);

    void agregarCuenta(const std::string& cedula, const std::string& nombre,
                       const std::string& numeroCuenta, double saldoInicial,
                       const std::string& telefono, const std::string& correo,
                       const std::string& sucursal);

    std::string generarNumeroCuenta();

    void setCodigoSucursal(const std::string& codigo);
    void setContador(size_t nuevoValor);
    static size_t getContador();
};

#endif
