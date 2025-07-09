#ifndef CUENTA_CORRIENTE_H
#define CUENTA_CORRIENTE_H

#include <string>
#include <vector>

class CuentaCorriente {
private:
    static size_t contadorCuentas;
    std::string codigoSucursal;

    std::vector<std::string> cedulas;
    std::vector<std::string> nombres;
    std::vector<std::string> numerosCuenta;
    std::vector<double> saldos;
    std::vector<std::string> telefonos;
    std::vector<std::string> correos;
    std::vector<std::string> sucursales;
    std::vector<std::string> fechasRegistro;

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
    std::string getFechaRegistro(size_t index) const;

    void setCedula(size_t index, const std::string& nuevaCedula);
    void setNombre(size_t index, const std::string& nuevoNombre);
    void setTelefono(size_t index, const std::string& nuevoTelefono);
    void setCorreo(size_t index, const std::string& nuevoCorreo);
    void setSucursal(size_t index, const std::string& nuevaSucursal);
    void setFechaRegistro(size_t index, const std::string& nuevaFecha);
    void setSaldo(size_t index, double nuevoSaldo);

    void agregarCuenta(const std::string& cedula, const std::string& nombre,
                       const std::string& numeroCuenta, double saldoInicial,
                       const std::string& telefono, const std::string& correo,
                       const std::string& sucursal,
                       const std::string& fechaRegistro);

    std::string generarNumeroCuenta();

    void setCodigoSucursal(const std::string& codigo);
    void setContador(size_t nuevoValor);
    static size_t getContador();
};

#endif
