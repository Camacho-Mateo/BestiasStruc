#ifndef CUENTA_CORRIENTE_H
#define CUENTA_CORRIENTE_H

#include <string>
#include <vector>

class CuentaCorriente {
private:
    struct Cuenta {
        std::string cedula;
        std::string nombre;
        std::string numeroCuenta;
        double saldo;
    };

    std::vector<Cuenta> cuentas;
    static size_t contadorCuentas;
    std::string codigoSucursal = "00";

public:
    CuentaCorriente();

    size_t getTotalCuentas() const;
    std::string getCedula(size_t index) const;
    std::string getNombre(size_t index) const;
    std::string getNumeroCuentaStr(size_t index) const;
    double getSaldo(size_t index) const;
    void setSaldo(size_t index, double nuevoSaldo);

    void agregarCuenta(const std::string& cedula, const std::string& nombre,
                       const std::string& numeroCuenta, double saldoInicial);

    std::string generarNumeroCuenta();
    void setCodigoSucursal(const std::string& codigo);

    static void setContador(size_t nuevoValor);
    static size_t getContador();
};

#endif
