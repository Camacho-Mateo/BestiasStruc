#ifndef SECRETARIO_H
#define SECRETARIO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <algorithm>
#include <sstream>
#include <ctime>

#include "../View/MenuInteractivo.h"

class Secretario {
private:
    struct Cita {
        std::string cedula;
        std::string fechaNacimiento;
        std::string ciudad;
        std::string fechaCita;
        std::string hora;
        int piso;
    };

    std::vector<Cita> citas;
    const std::vector<std::string> ciudades = {
        "Quito", "Cayambe", "Ruminiahui", "Mejia", "Pedro Moncayo"
    };
    const std::vector<std::string> feriados = {
        // 2025
        "24/07/2025", "10/08/2025", "09/10/2025", "02/11/2025", "03/11/2025", "06/12/2025",
        // 2026
        "01/01/2026", "24/07/2026", "10/08/2026", "09/10/2026", "02/11/2026", "03/11/2026", "06/12/2026", "25/12/2026",
        // 2027
        "01/01/2027", "24/07/2027", "10/08/2027", "09/10/2027", "02/11/2027", "03/11/2027", "06/12/2027", "25/12/2027",
        // 2028
        "01/01/2028", "24/07/2028", "10/08/2028", "09/10/2028", "02/11/2028", "03/11/2028", "06/12/2028", "25/12/2028",
        // 2029
        "01/01/2029", "24/07/2029", "10/08/2029", "09/10/2029", "02/11/2029", "03/11/2029", "06/12/2029", "25/12/2029",
        // 2030
        "01/01/2030", "24/07/2030", "10/08/2030", "09/10/2030", "02/11/2030", "03/11/2030", "06/12/2030", "25/12/2030",
        // 2031
        "01/01/2031", "24/07/2031", "10/08/2031", "09/10/2031", "02/11/2031", "03/11/2031", "06/12/2031", "25/12/2031",
        // 2032
        "01/01/2032", "24/07/2032", "10/08/2032", "09/10/2032", "02/11/2032", "03/11/2032", "06/12/2032", "25/12/2032",
        // 2033
        "01/01/2033", "24/07/2033", "10/08/2033", "09/10/2033", "02/11/2033", "03/11/2033", "06/12/2033", "25/12/2033",
        // 2034
        "01/01/2034", "24/07/2034", "10/08/2034", "09/10/2034", "02/11/2034", "03/11/2034", "06/12/2034", "25/12/2034",
        // 2035
        "01/01/2035", "24/07/2035", "10/08/2035", "09/10/2035", "02/11/2035", "03/11/2035", "06/12/2035", "25/12/2035"
    };

    bool esFeriado(const std::string& fecha) {
        return std::find(feriados.begin(), feriados.end(), fecha) != feriados.end();
    }

    bool esFinDeSemana(const std::string& fecha) {
        std::tm tm = {};
        std::istringstream ss(fecha);
        ss >> std::get_time(&tm, "%d/%m/%Y");
        if (ss.fail()) return false;  // formato inválido

        std::mktime(&tm); // rellena tm.tm_wday
        // Domingo = 0, Sábado = 6
        return (tm.tm_wday == 0 || tm.tm_wday == 6);
    }

    bool yaExisteCita(const std::string& fecha, const std::string& hora, int piso) {
        for (const auto& cita : citas) {
            if (cita.fechaCita == fecha && cita.hora == hora && cita.piso == piso)
                return true;
        }
        return false;
    }

    std::string pedirCedula() {
        std::string cedula;
        char c;
        std::cout << "Ingrese la cedula: ";
        while (true) {
            cedula.clear();
            while (true) {
                c = getch();
                if (isdigit(c) && cedula.size() < 10) {
                    cedula += c;
                    std::cout << c;
                } else if (c == 8 && !cedula.empty()) {
                    cedula.pop_back();
                    std::cout << "\b \b";
                } else if (c == 13 && cedula.size() == 10) {
                    break;
                }
            }
            std::cout << std::endl;
            if (cedula.size() == 10) break;
            std::cout << "Cédula invalida. Intente de nuevo: ";
        }
        return cedula;
    }

    std::string pedirFechaNacimiento() {
        std::string fecha;
        std::cout << "Ingrese su fecha de nacimiento (dd/mm/aaaa): ";
        while (true) {
            fecha.clear();
            while (fecha.size() < 10) {
                char c = getch();
                size_t pos = fecha.size();
                if ((pos == 2 || pos == 5) && c == '/') {
                    std::cout << c;
                    fecha += c;
                } else if (isdigit(c)) {
                    std::cout << c;
                    fecha += c;
                } else if (c == 8 && !fecha.empty()) {
                    std::cout << "\b \b";
                    fecha.pop_back();
                }
            }
            std::cout << std::endl;
            try {
                int d = stoi(fecha.substr(0, 2));
                int m = stoi(fecha.substr(3, 2));
                int a = stoi(fecha.substr(6, 4));
                if (d >= 1 && d <= 31 && m >= 1 && m <= 12 && a >= 1950 && a <= 2025)
                    return fecha;
            } catch (...) {}
            std::cout << "Fecha inválida. Intente de nuevo: ";
        }
    }

    std::string pedirCiudad() {
        std::cout << "Seleccione su ciudad de la provincia de Pichincha:\n";
        MenuInteractivo menuCiudad(ciudades);
        int opcion = menuCiudad.ejecutar();
        return ciudades[opcion - 1];
    }

    std::string pedirFechaCita() {
        std::string fecha;
        std::cout << "Ingrese la fecha deseada para la cita (dd/mm/aaaa, desde 10/07/2025): ";
        while (true) {
            std::getline(std::cin, fecha);
            if (fecha.empty()) continue;

            try {
                int d = stoi(fecha.substr(0, 2));
                int m = stoi(fecha.substr(3, 2));
                int a = stoi(fecha.substr(6, 4));

                std::tm tm = {};
                tm.tm_mday = d;
                tm.tm_mon = m - 1;
                tm.tm_year = a - 1900;
                std::time_t t = std::mktime(&tm);

                if (t == -1 || a < 2025 || (a == 2025 && (m < 7 || (m == 7 && d < 10)))) {
                    throw std::invalid_argument("Fecha fuera de rango");
                }

                std::ostringstream oss;
                oss << std::setw(2) << std::setfill('0') << d << "/"
                    << std::setw(2) << std::setfill('0') << m << "/"
                    << a;

                std::string fechaFormateada = oss.str();
                if (!esFeriado(fechaFormateada) && !esFinDeSemana(fechaFormateada)) {
                    return fechaFormateada;
                }

                std::cout << "Fecha no laborable (feriado o fin de semana). Ingrese otra: ";
            } catch (...) {
                std::cout << "Formato invalido. Intente de nuevo: ";
            }
        }
    }

    std::string pedirHora() {
        std::string hora;
        std::cout << "Ingrese la hora (HH:MM, entre 08:00 y 17:00, múltiplos de 20min): ";
        while (true) {
            std::getline(std::cin, hora);
            try {
                if (hora.size() != 5 || hora[2] != ':') throw std::invalid_argument("Formato incorrecto");
                int h = stoi(hora.substr(0, 2));
                int m = stoi(hora.substr(3, 2));
                if (h >= 8 && h < 17 && (m == 0 || m == 20 || m == 40))
                    return hora;
            } catch (...) {}
            std::cout << "Hora inválida. Intente de nuevo: ";
        }
    }

public:
    void agendar() {
        std::string cedula = pedirCedula();
        std::string fechaNacimiento = pedirFechaNacimiento();
        std::string ciudad = pedirCiudad();

        int anioNacimiento = stoi(fechaNacimiento.substr(6, 4));
        int piso = (anioNacimiento <= 1990) ? 1 : (rand() % 2) + 1;

        std::string fechaCita, horaCita;
        while (true) {
            fechaCita = pedirFechaCita();
            horaCita = pedirHora();

            if (!yaExisteCita(fechaCita, horaCita, piso)) break;

            std::cout << "Ya existe una cita en ese piso para esa hora. Intente otra hora o fecha.\n";
        }

        Cita cita;
        cita.cedula = cedula;
        cita.fechaNacimiento = fechaNacimiento;
        cita.ciudad = ciudad;
        cita.fechaCita = fechaCita;
        cita.hora = horaCita;
        cita.piso = piso;

        citas.push_back(cita);
        std::cout << "\nCita agendada:\n"
                  << "Cedula: " << cita.cedula << "\n"
                  << "Fecha Nacimiento: " << cita.fechaNacimiento << "\n"
                  << "Ciudad: " << cita.ciudad << "\n"
                  << "Fecha Cita: " << cita.fechaCita << " " << cita.hora << "\n"
                  << "Piso: " << cita.piso << "\n";

        guardarCitas();
    }

    void guardarCitas() {
        std::ofstream archivo("citas.txt");
        for (const auto& cita : citas) {
            archivo << cita.cedula << ", " << cita.fechaNacimiento << ", "
                    << cita.ciudad << ", " << cita.fechaCita << " "
                    << cita.hora << ", Piso " << cita.piso << "\n";
        }
        archivo.close();
    }
};

#endif
