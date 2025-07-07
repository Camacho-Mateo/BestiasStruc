#include "Buscador.h"
#include <algorithm>

Buscador::Buscador(CuentaAhorro* ca, CuentaCorriente* cc)
    : cuentaAhorro(ca), cuentaCorriente(cc) {}

int Buscador::buscarPorCedula(const std::string& cedula, bool esAhorro) {
    size_t total = esAhorro ? cuentaAhorro->getTotalCuentas() : cuentaCorriente->getTotalCuentas();
    std::vector<std::pair<std::string, int>> cedulas;

    for (size_t i = 0; i < total; ++i) {
        std::string actual = esAhorro ? cuentaAhorro->getCedula(i) : cuentaCorriente->getCedula(i);
        cedulas.push_back({actual, static_cast<int>(i)});
    }

    std::sort(cedulas.begin(), cedulas.end());
    auto it = std::lower_bound(cedulas.begin(), cedulas.end(), std::make_pair(cedula, 0));

    if (it != cedulas.end() && it->first == cedula)
        return it->second;

    return -1;
}

int Buscador::buscarPorNombre(const std::string& nombre, bool esAhorro) {
    size_t total = esAhorro ? cuentaAhorro->getTotalCuentas() : cuentaCorriente->getTotalCuentas();
    std::vector<std::pair<std::string, int>> nombres;

    for (size_t i = 0; i < total; ++i) {
        std::string actual = esAhorro ? cuentaAhorro->getNombre(i) : cuentaCorriente->getNombre(i);
        nombres.push_back({actual, static_cast<int>(i)});
    }

    std::sort(nombres.begin(), nombres.end());
    auto it = std::lower_bound(nombres.begin(), nombres.end(), std::make_pair(nombre, 0));

    if (it != nombres.end() && it->first == nombre)
        return it->second;

    return -1;
}

int Buscador::buscarPorCuenta(const std::string& numeroCuenta, bool esAhorro) {
    size_t total = esAhorro ? cuentaAhorro->getTotalCuentas() : cuentaCorriente->getTotalCuentas();
    std::vector<std::pair<std::string, int>> cuentas;

    for (size_t i = 0; i < total; ++i) {
        std::string actual = esAhorro ? cuentaAhorro->getNumeroCuentaStr(i) : cuentaCorriente->getNumeroCuentaStr(i);
        cuentas.push_back({actual, static_cast<int>(i)});
    }

    std::sort(cuentas.begin(), cuentas.end());
    auto it = std::lower_bound(cuentas.begin(), cuentas.end(), std::make_pair(numeroCuenta, 0));

    if (it != cuentas.end() && it->first == numeroCuenta)
        return it->second;

    return -1;
}
