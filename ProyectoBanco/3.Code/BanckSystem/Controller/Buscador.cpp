#include "Buscador.h"
#include <algorithm>
#include <vector>
#include <string>

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

    int left = 0;
    int right = cedulas.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (cedulas[mid].first == cedula)
            return cedulas[mid].second;
        else if (cedulas[mid].first < cedula)
            left = mid + 1;
        else
            right = mid - 1;
    }

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

    int left = 0;
    int right = nombres.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (nombres[mid].first == nombre)
            return nombres[mid].second;
        else if (nombres[mid].first < nombre)
            left = mid + 1;
        else
            right = mid - 1;
    }

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

    int left = 0;
    int right = cuentas.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (cuentas[mid].first == numeroCuenta)
            return cuentas[mid].second;
        else if (cuentas[mid].first < numeroCuenta)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

std::vector<int> Buscador::buscarPorFecha(const std::string& fecha, bool esAhorro) {
    size_t total = esAhorro ? cuentaAhorro->getTotalCuentas() : cuentaCorriente->getTotalCuentas();
    std::vector<std::pair<std::string, int>> fechas;

    for (size_t i = 0; i < total; ++i) {
        std::string actual = esAhorro ? cuentaAhorro->getFechaRegistro(i) : cuentaCorriente->getFechaRegistro(i);
        fechas.push_back({actual, static_cast<int>(i)});
    }

    std::sort(fechas.begin(), fechas.end());

    std::vector<int> resultados;
    int left = 0;
    int right = fechas.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (fechas[mid].first == fecha) {
            // Encontrar todas las coincidencias hacia la izquierda
            int i = mid;
            while (i >= 0 && fechas[i].first == fecha) {
                resultados.push_back(fechas[i].second);
                i--;
            }
            // Encontrar todas las coincidencias hacia la derecha
            i = mid + 1;
            while (i < fechas.size() && fechas[i].first == fecha) {
                resultados.push_back(fechas[i].second);
                i++;
            }
            break;
        } else if (fechas[mid].first < fecha) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return resultados;
}
