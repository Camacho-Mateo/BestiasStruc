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

    int hora = 8, minuto = 0, dia = 7, mes = 7, anio = 2025;

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

    std::string obtenerHoraActual() {
        std::ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << hora << ":" << std::setw(2) << std::setfill('0') << minuto;
        return ss.str();
    }

    std::string obtenerFechaActual() {
        std::ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << dia << "/"
           << std::setw(2) << std::setfill('0') << mes << "/"
           << anio;
        return ss.str();
    }

    void avanzarTiempo() {
        minuto += 20;
        if (minuto >= 60) {
            minuto = 0;
            hora++;
        }
        if (hora >= 17) {
            hora = 8;
            minuto = 0;
            dia++;
            if (dia > 31) { dia = 1; mes++; }
            if (mes > 12) { mes = 1; anio++; }
        }
    }

public:
    void agendar() {
        std::string cedula = pedirCedula();
        std::string fechaNacimiento = pedirFechaNacimiento();
        std::string ciudad = pedirCiudad();

        int anioNacimiento = stoi(fechaNacimiento.substr(6, 4));
        int piso = (anioNacimiento <= 1990) ? 1 : (rand() % 2) + 1;

        Cita cita;
        cita.cedula = cedula;
        cita.fechaNacimiento = fechaNacimiento;
        cita.ciudad = ciudad;
        cita.fechaCita = obtenerFechaActual();
        cita.hora = obtenerHoraActual();
        cita.piso = piso;

        citas.push_back(cita);
        std::cout << "\nCita agendada:\n"
                  << "Cedula: " << cita.cedula << "\n"
                  << "Fecha Nacimiento: " << cita.fechaNacimiento << "\n"
                  << "Ciudad: " << cita.ciudad << "\n"
                  << "Fecha Cita: " << cita.fechaCita << " " << cita.hora << "\n"
                  << "Piso: " << cita.piso << "\n";

        avanzarTiempo();
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
