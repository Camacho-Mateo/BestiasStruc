#include "Editor.h"
#include <conio.h>
#include <limits>

Editor::Editor(CuentaAhorro* ca, CuentaCorriente* cc, AdministradorBanco* ab)
    : cuentaAhorro(ca), cuentaCorriente(cc), administradorBanco(ab) {}

void Editor::ejecutar() {
    std::string cedula;

    // Pedir cédula con validación similar a Registrador
    while (true) {
        try {
            char c;
            cedula.clear();
            std::cout << "Ingrese la cedula a editar: ";
            while (true) {
                c = getch();
                if (isdigit(c) && cedula.length() < 10) {
                    std::cout << c;
                    cedula += c;
                } else if (c == 8 && !cedula.empty()) {
                    std::cout << "\b \b";
                    cedula.pop_back();
                } else if (c == 13 && !cedula.empty()) {
                    break;
                }
            }
            std::cout << std::endl;
            Validador::validar(cedula, "cedula");

            if (!administradorBanco->estaRegistrada(cedula)) {
                std::cout << "La cédula no está registrada. Intente otra vez.\n";
                continue;
            }
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    std::vector<std::string> opciones = {
        "Modificar Nombre",
        "Modificar Cedula",
        "Modificar Correo",
        "Modificar Telefono",
        "Salir"
    };
    MenuInteractivo menu(opciones);

    bool salir = false;
    while (!salir) {
        int opcion = menu.ejecutar();

        switch (opcion) {
            case 1:
                modificarNombre(cedula);
                break;
            case 2:
                modificarCedula(cedula);
                break;
            case 3:
                modificarCorreo(cedula);
                break;
            case 4:
                modificarTelefono(cedula);
                break;
            case 5:
                salir = true;
                break;
            default:
                std::cout << "Opción inválida.\n";
                break;
        }
    }
}

// Modificar nombre en todas las cuentas con esa cédula
void Editor::modificarNombre(const std::string& cedula) {
    std::string nuevoNombre;

    // Validar nombre igual que en Registrador (solo letras, no vacío)
    while (true) {
        try {
            char c;
            nuevoNombre.clear();
            std::cout << "Ingrese el nuevo nombre: ";
            while (true) {
                c = getch();
                if (isalpha(c) || c == ' ') { // permitir espacios para nombres compuestos
                    std::cout << c;
                    nuevoNombre += c;
                } else if (c == 8 && !nuevoNombre.empty()) {
                    std::cout << "\b \b";
                    nuevoNombre.pop_back();
                } else if (c == 13 && !nuevoNombre.empty()) {
                    break;
                }
            }
            std::cout << std::endl;
            Validador::validar(nuevoNombre, "nombre");
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    size_t totalA = cuentaAhorro->getTotalCuentas();
    for (size_t i = 0; i < totalA; ++i) {
        if (cuentaAhorro->getCedula(i) == cedula) {
            cuentaAhorro->setNombre(i, nuevoNombre);
        }
    }
    size_t totalC = cuentaCorriente->getTotalCuentas();
    for (size_t i = 0; i < totalC; ++i) {
        if (cuentaCorriente->getCedula(i) == cedula) {
            cuentaCorriente->setNombre(i, nuevoNombre);
        }
    }

    administradorBinario.guardarCuentas(*cuentaAhorro, *cuentaCorriente);
    std::cout << "Nombre actualizado exitosamente.\n";
}

void Editor::modificarCedula(const std::string& cedula) {
    std::string nuevaCedula;

    while (true) {
        try {
            char c;
            nuevaCedula.clear();
            std::cout << "Ingrese la nueva cedula: ";
            while (true) {
                c = getch();
                if (isdigit(c) && nuevaCedula.length() < 10) {
                    std::cout << c;
                    nuevaCedula += c;
                } else if (c == 8 && !nuevaCedula.empty()) {
                    std::cout << "\b \b";
                    nuevaCedula.pop_back();
                } else if (c == 13 && !nuevaCedula.empty()) {
                    break;
                }
            }
            std::cout << std::endl;
            Validador::validar(nuevaCedula, "cedula");

            // Verificar que la nueva cédula no esté registrada ya
            if (administradorBanco->estaRegistrada(nuevaCedula)) {
                std::cout << "La nueva cedula ya está registrada. Intente otra.\n";
                continue;
            }
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    // Actualizar en CuentaAhorro
    size_t totalA = cuentaAhorro->getTotalCuentas();
    for (size_t i = 0; i < totalA; ++i) {
        if (cuentaAhorro->getCedula(i) == cedula) {
            cuentaAhorro->setCedula(i, nuevaCedula);
        }
    }
    // Actualizar en CuentaCorriente
    size_t totalC = cuentaCorriente->getTotalCuentas();
    for (size_t i = 0; i < totalC; ++i) {
        if (cuentaCorriente->getCedula(i) == cedula) {
            cuentaCorriente->setCedula(i, nuevaCedula);
        }
    }

    administradorBinario.guardarCuentas(*cuentaAhorro, *cuentaCorriente);
    std::cout << "Cédula actualizada exitosamente.\n";
}

// Modificar correo
void Editor::modificarCorreo(const std::string& cedula) {
    std::string nuevoCorreo;

    while (true) {
        try {
            std::cout << "Ingrese el nuevo correo: ";
            std::getline(std::cin, nuevoCorreo);
            Validador::validar(nuevoCorreo, "correo");
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    size_t totalA = cuentaAhorro->getTotalCuentas();
    for (size_t i = 0; i < totalA; ++i) {
        if (cuentaAhorro->getCedula(i) == cedula) {
            cuentaAhorro->setCorreo(i, nuevoCorreo);
        }
    }
    size_t totalC = cuentaCorriente->getTotalCuentas();
    for (size_t i = 0; i < totalC; ++i) {
        if (cuentaCorriente->getCedula(i) == cedula) {
            cuentaCorriente->setCorreo(i, nuevoCorreo);
        }
    }

    administradorBinario.guardarCuentas(*cuentaAhorro, *cuentaCorriente);
    std::cout << "Correo actualizado exitosamente.\n";
}

// Modificar teléfono
void Editor::modificarTelefono(const std::string& cedula) {
    std::string nuevoTelefono;

    while (true) {
        try {
            char c;
            nuevoTelefono.clear();
            std::cout << "Ingrese el nuevo telefono: ";
            while (true) {
                c = getch();
                if (isdigit(c) && nuevoTelefono.length() < 15) {
                    std::cout << c;
                    nuevoTelefono += c;
                } else if (c == 8 && !nuevoTelefono.empty()) {
                    std::cout << "\b \b";
                    nuevoTelefono.pop_back();
                } else if (c == 13 && !nuevoTelefono.empty()) {
                    break;
                }
            }
            std::cout << std::endl;
            Validador::validar(nuevoTelefono, "telefono");
            break;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    size_t totalA = cuentaAhorro->getTotalCuentas();
    for (size_t i = 0; i < totalA; ++i) {
        if (cuentaAhorro->getCedula(i) == cedula) {
            cuentaAhorro->setTelefono(i, nuevoTelefono);
        }
    }
    size_t totalC = cuentaCorriente->getTotalCuentas();
    for (size_t i = 0; i < totalC; ++i) {
        if (cuentaCorriente->getCedula(i) == cedula) {
            cuentaCorriente->setTelefono(i, nuevoTelefono);
        }
    }

    administradorBinario.guardarCuentas(*cuentaAhorro, *cuentaCorriente);
    std::cout << "Telefono actualizado exitosamente.\n";
}
