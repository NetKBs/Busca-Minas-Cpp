#include "Celda.cpp"

#include <cmath>
#include <cstdio>

#include <iostream>

#include <list>

#include <string>

#include <time.h>

using namespace std;

struct Point {
  int fila, columna;
};

/**
 *
 *
 */

class Tablero {

private:
  static const int FILAS = 8, COLUMNAS = 8;
  const int MAX_MINAS = 12;
  Celda tablero[FILAS][COLUMNAS];
  // list crea una lista enlazada
  // pair es una estructura de la biblioteca estándar que almacena dos valores.
  list<pair<int, int>> celdasParaChecar;

public:
  Tablero() {}

  Celda obtenerCelda(int fila, int columna) { return tablero[fila][columna]; }

  void marcarCelda(int fila, int columna) {
    if (tablero[fila][columna].getMarcadaEstado()) {
        tablero[fila][columna].setMarcadoEstado(false);
    } else {
        tablero[fila][columna].setMarcadoEstado(true);
    }
  }

  int revelarCelda(int fila, int columna) {

    if (tablero[fila][columna].getMinaEstado()) { 
      return -1; // existe una mina
    }
    
    if (tablero[fila][columna].getNumMinasAdyacentes() > 0) { // Minas alrededor
        tablero[fila][columna].setReveladoEstado(true);
        return 0;
    }

    celdasParaChecar.push_back({fila, columna});

    while (!celdasParaChecar.empty()) {

      // Obtén las coordenadas x e y de la próxima celda
      int fila = celdasParaChecar.front().first;
      int columna = celdasParaChecar.front().second;
      celdasParaChecar.pop_front(); // Elimina esa celda de la cola

      // Revisar Celdas Adyacentes
      // En busqueda de Minas Al rededor


      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
          if (i == 0 && j == 0) { continue; }// Omitir la celda central

          int filaVecina = fila + i;
          int columnaVecina = columna + j;

          if (celdaValidaParaChecar(filaVecina, columnaVecina) &&
              !tablero[filaVecina][columnaVecina].getReveladoEstado()) {

            tablero[filaVecina][columnaVecina].setReveladoEstado(true);

            if (tablero[filaVecina][columnaVecina].getNumMinasAdyacentes() == 0 ) {
                celdasParaChecar.push_front({filaVecina, columnaVecina});
            } 
          }
        }
      }


    }

    return 0;
  }

  bool celdaValidaParaChecar(int fila, int columna) {
    if (fila >= 0 && fila <= 7 && columna >= 0 && columna <= 7) {
      return true;
    }
    return false;
  }

  void mostrarTableroDetalles() {
    for (int fila = 0; fila < FILAS; fila++) {
      for (int columna = 0; columna < COLUMNAS; columna++) {

        if(!tablero[fila][columna].getMinaEstado()) {
            cout << tablero[fila][columna].getNumMinasAdyacentes() << " ";
        } else {
            cout << "!" << " ";
        }
      }
      cout << endl;
    }
  }


  void generarTablero() {
    srand(time(NULL)); // rand seed
    int minas_colocadas = 0;
    int fila, columna;
    Point minas_coords[MAX_MINAS];

    while (minas_colocadas < MAX_MINAS) {
      fila = rand() % FILAS;
      columna = rand() % COLUMNAS;

      // Solo colocamos una mina si la celda ya no contiene
      if (tablero[fila][columna].getMinaEstado() == false) {
        tablero[fila][columna] = Celda(true);
        // guardamos coordenadas
        minas_coords[minas_colocadas].fila = fila;
        minas_coords[minas_colocadas].columna = columna;

        minas_colocadas++;
      }
    }

    // Sumar numero de minas adayacentes a las celdas adyacentes
    // de las minas
    
    int contador = 0;

    while (contador < MAX_MINAS) {

      int filaActual = minas_coords[contador].fila;
      int columnaActual = minas_coords[contador].columna;

      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

          if (i == 0 && j == 0) {continue;} // omiter la celda central

          int filaVecina = filaActual + i;
          int columnaVecina = columnaActual + j;

          if (celdaValidaParaChecar(filaVecina, columnaVecina) && tablero[filaVecina][columnaVecina].getMinaEstado() == false) {
            tablero[filaVecina][columnaVecina].sumarMinasAdyacentes();
          }
        }
      }
    
        contador++;

    }
  }


  void dibujarTablero() {
    /*
            cout << "  ";
            for (int i = 0; i < COLUMNAS; i++) {
                cout << i << " ";
            }
            cout << endl;
    */
    for (int fila = 0; fila < FILAS; fila++) {
      //           cout << fila << " ";
      for (int columna = 0; columna < COLUMNAS; columna++) {

        if (tablero[fila][columna].getReveladoEstado()) {
            cout << tablero[fila][columna].getNumMinasAdyacentes() << " ";

        } else if (tablero[fila][columna].getMarcadaEstado()) {
            cout << "?" << " "; 

        } else {
           cout << "*" << " "; 
        }

      }
      cout << endl;
    }
  }
};