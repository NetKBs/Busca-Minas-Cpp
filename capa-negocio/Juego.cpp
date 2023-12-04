#include "Tablero.cpp"
#include <iostream>
#include <ostream>


class Juego {

private:

    Tablero tablero = Tablero();

public:

    void nuevaPartida() {
        tablero.generarTablero();
    }

    void cargarPartida();

    string verificarCoordenadas(int fila, int columna) {

        if (fila < 0 || columna < 0 && fila > 7 || columna > 7) { 
            return "Coordenadas Invalidas";
        }

        if (tablero.obtenerCelda(fila, columna).getReveladoEstado()) {
            return "Celda Ya Revelada";
        }

        return "";
    }

    void revelarCelda(int fila, int columna) {
        tablero.revelarCelda(fila, columna);
    }

    void marcarCelda(int fila, int columna) {
        tablero.marcarCelda(fila, columna);
    }

    void dibujarTablero() {
        tablero.mostrarTableroDetalles();
        cout << "\n-----------------------" << endl;
        tablero.dibujarTablero();

    }

    void chequearVictoria();

    void guardarPartida();

};