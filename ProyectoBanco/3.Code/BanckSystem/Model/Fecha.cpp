#include "Fecha.h"
#include <sstream>
#include <iomanip>

using namespace std;

Fecha::Fecha() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    dia = ltm->tm_mday;
    mes = ltm->tm_mon + 1;
    anio = 1900 + ltm->tm_year;
}

Fecha::Fecha(int dia, int mes, int anio) {
    if (validarFecha(dia, mes, anio)) {
        this->dia = dia;
        this->mes = mes;
        this->anio = anio;
    } else {
        throw invalid_argument("Fecha inválida.");
    }
}

bool Fecha::esBisiesto(int anio) {
    return ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0));
}

bool Fecha::validarFecha(int dia, int mes, int anio) {
    if (anio < 1900 || anio > 2100 || mes < 1 || mes > 12 || dia < 1) {
        return false;
    }

    int diasPorMes[] = { 31, esBisiesto(anio) ? 29 : 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31 };

    return dia <= diasPorMes[mes - 1];
}

int Fecha::getDia() const {
    return dia;
}

int Fecha::getMes() const {
    return mes;
}

int Fecha::getAnio() const {
    return anio;
}

string Fecha::toString() const {
    stringstream ss;
    ss << setfill('0') << setw(2) << dia << "/"
       << setfill('0') << setw(2) << mes << "/"
       << anio;
    return ss.str();
}
