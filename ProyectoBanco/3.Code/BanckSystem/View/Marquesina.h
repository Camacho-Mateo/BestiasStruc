#ifndef MARQUESINA_H
#define MARQUESINA_H

#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <windows.h>

class Marquesina {
private:
    std::thread hilo;
    std::atomic<bool> corriendo;
    std::atomic<bool> pausada;
    std::mutex mutex;

    std::string mensajeSuperior = "  BIENVENIDO A BANKSYSTEM  ";

    HANDLE hConsole;
    SHORT lineaSuperior = 1;

    void desplazarTexto(std::string& texto) {
        if (!texto.empty()) {
            char primero = texto[0];
            texto.erase(0, 1);
            texto.push_back(primero);
        }
    }

    void moverCursor(int x, int y) {
        COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
        SetConsoleCursorPosition(hConsole, coord);
    }

    int obtenerAnchoConsola() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            return csbi.dwSize.X;
        }
        return 80;
    }

    void imprimirCentrado(const std::string& texto, SHORT fila) {
        int ancho = obtenerAnchoConsola();
        int espacio = (ancho - static_cast<int>(texto.size())) / 2;
        if (espacio < 0) espacio = 0;
        moverCursor(espacio, fila);
        std::cout << texto << std::flush;
    }

    void ajustarBufferYLineas() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);

        COORD nuevoTam = csbi.dwSize;
        if (nuevoTam.Y < 40) {
            nuevoTam.Y = 40;
            SetConsoleScreenBufferSize(hConsole, nuevoTam);
        }
    }

    void ejecutar() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        ajustarBufferYLineas();

        while (corriendo.load()) {
            if (!pausada.load()) {
                std::lock_guard<std::mutex> lock(mutex);

                // Guardar posición del cursor
                CONSOLE_SCREEN_BUFFER_INFO csbi;
                GetConsoleScreenBufferInfo(hConsole, &csbi);
                COORD posicionOriginal = csbi.dwCursorPosition;

                // Ocultar cursor
                CONSOLE_CURSOR_INFO cursorInfo;
                GetConsoleCursorInfo(hConsole, &cursorInfo);
                bool visibleAntes = cursorInfo.bVisible;
                cursorInfo.bVisible = FALSE;
                SetConsoleCursorInfo(hConsole, &cursorInfo);

                // Imprimir mensaje superior centrado
                imprimirCentrado(mensajeSuperior, lineaSuperior);

                // Restaurar cursor y visibilidad
                SetConsoleCursorPosition(hConsole, posicionOriginal);
                cursorInfo.bVisible = visibleAntes;
                SetConsoleCursorInfo(hConsole, &cursorInfo);

                // Desplazar texto para efecto marquesina
                desplazarTexto(mensajeSuperior);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    }

public:
    Marquesina() : corriendo(false), pausada(false),
                   hConsole(GetStdHandle(STD_OUTPUT_HANDLE)) {}

    void iniciar() {
        corriendo.store(true);
        hilo = std::thread(&Marquesina::ejecutar, this);
    }

    void detener() {
        corriendo.store(false);
        if (hilo.joinable()) {
            hilo.join();
        }

        // Restaurar cursor visible al terminar
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = TRUE;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }

    void pausar() {
        pausada.store(true);
    }

    void reanudar() {
        pausada.store(false);
    }

    void limpiarBufferEntrada() {
        // Limpia cualquier entrada pendiente para evitar que std::getline falle
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string leerEntrada(const std::string& prompt, SHORT filaInput) {
        pausar();
        std::lock_guard<std::mutex> lock(mutex);

        int ancho = obtenerAnchoConsola();

        int espacio = (ancho - static_cast<int>(prompt.size()) - 30) / 2;
        if (espacio < 0) espacio = 0;

        moverCursor(0, filaInput);
        std::cout << std::string(ancho, ' ');

        moverCursor(espacio, filaInput);
        std::cout << prompt << std::flush;

        moverCursor(espacio + prompt.size(), filaInput);

        // Mostrar cursor visible para que usuario vea lo que escribe
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        bool cursorVisibleAntes = cursorInfo.bVisible;
        cursorInfo.bVisible = TRUE;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        limpiarBufferEntrada(); // limpieza por si hay basura en buffer

        std::string entrada;
        std::getline(std::cin, entrada);

        cursorInfo.bVisible = cursorVisibleAntes;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        moverCursor(0, filaInput + 1);
        std::cout << std::string(ancho, ' ');
        std::string confirmacion = "Ingresado: " + entrada;
        imprimirCentrado(confirmacion, filaInput + 1);

        reanudar();
        return entrada;
    }

    ~Marquesina() {
        detener();
    }
};

#endif
