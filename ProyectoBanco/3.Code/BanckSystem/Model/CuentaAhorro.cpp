#include "CuentaAhorro.h"
#include <string>
#include <fstream>
using namespace std;

template<typename T>
Cuenta<T>::Cuenta() : saldo(0) {}

template<typename T>
Cuenta<T>::Cuenta(string num, T saldoInicial) : numeroCuenta(num), saldo(saldoInicial) {}

template<typename T>
void Cuenta<T>::depositar(T cantidad) {
    saldo += cantidad;
}

template<typename T>
bool Cuenta<T>::retirar(T cantidad) {
    if (cantidad > saldo) return false;
    saldo -= cantidad;
    return true;
}

template<typename T>
T Cuenta<T>::getSaldo() const {
    return saldo;
}

template<typename T>
string Cuenta<T>::getNumeroCuenta() const {
    return numeroCuenta;
}

template<typename T>
void Cuenta<T>::setNumeroCuenta(string num) {
    numeroCuenta = num;
}

template<typename T>
void Cuenta<T>::escribir(ofstream& out) const {
    size_t len = numeroCuenta.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(numeroCuenta.c_str(), len);
    out.write(reinterpret_cast<const char*>(&saldo), sizeof(saldo));
}

template<typename T>
void Cuenta<T>::leer(ifstream& in) {
    size_t len;
    char* buffer;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    numeroCuenta = buffer;
    delete[] buffer;

    in.read(reinterpret_cast<char*>(&saldo), sizeof(saldo));
}

template class Cuenta<double>;

CuentaAhorro::CuentaAhorro() : Cuenta() {}

CuentaAhorro::CuentaAhorro(string num) : Cuenta(num, 0.0) {}
