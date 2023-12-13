#include "Tablero.hpp"
#include <cstdio>
#include <iostream>
#include <list>
#include <time.h>
#include <utility>

#include <fstream> // BORRAR


using namespace std;

struct Point {
  int fila, columna;
};

void Tablero::mostrarEsquemaInterno() {
  std::ofstream archivo("detalles_tablero.txt"); // Abrir el archivo de texto

  for (int fila = 0; fila < FILAS; fila++) {
    for (int columna = 0; columna < COLUMNAS; columna++) {
      if (!tablero[fila][columna].getMinaEstado()) {
        archivo << tablero[fila][columna].getNumMinasAdyacentes() << " ";
      } else {
        archivo << "!" << " ";
      }
    }
    archivo << endl;
  }

  archivo.close(); // Cerrar el archivo
}

Celda Tablero::obtenerCelda(int fila, int columna) {
  return tablero[fila][columna];
}

void Tablero::marcarCelda(int fila, int columna) {

  if (tablero[fila][columna].getMarcadaEstado()) {
    tablero[fila][columna].setMarcadoEstado(false);
  } else {
    tablero[fila][columna].setMarcadoEstado(true);
  }
}

int Tablero::revelarCelda(int fila, int columna) {

  if (tablero[fila][columna].getMinaEstado()) {
    tablero[fila][columna].setReveladoEstado(true);
    return 1;
  }

  if (tablero[fila][columna].getNumMinasAdyacentes() > 0) {
    tablero[fila][columna].setReveladoEstado(true);
    return 0;
  }

  list<pair<int, int>> celdasParaChecar;
  celdasParaChecar.push_back({fila, columna});

  while (!celdasParaChecar.empty()) {

    int fila = celdasParaChecar.front().first;     // fila
    int columna = celdasParaChecar.front().second; // columna
    celdasParaChecar.pop_front();                  // quitar

    // Revisar Celdas Adyacentes
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {

        if (i == 0 && j == 0)
          continue; // celda central
        int filaVecina = fila + i;
        int columnaVecina = columna + j;

        if (celdaValidaParaChecar(filaVecina, columnaVecina) &&
            !tablero[filaVecina][columnaVecina].getReveladoEstado()) {

          tablero[filaVecina][columnaVecina].setReveladoEstado(true);

          if (tablero[filaVecina][columnaVecina].getNumMinasAdyacentes() == 0) {
            celdasParaChecar.push_front({filaVecina, columnaVecina});
          }
        }
      }
    }
  }

  return 0;
}

bool Tablero::celdaValidaParaChecar(int fila, int columna) {
  if (fila >= 0 && fila <= 7 && columna >= 0 && columna <= 7)
    return true;
  return false;
}

void Tablero::generarTablero() {
  srand(time(NULL)); // rand seed
  int minas_colocadas = 0;
  int fila, columna;
  pair<int, int> minas_coords[MAX_MINAS];

  while (minas_colocadas < MAX_MINAS) {
    fila = rand() % FILAS;
    columna = rand() % COLUMNAS;

    if (tablero[fila][columna].getMinaEstado() == false) {

      tablero[fila][columna] = Celda(true);
      minas_coords[minas_colocadas].first = fila;
      minas_coords[minas_colocadas].second = columna;
      minas_colocadas++;
    }
  }

  asignarAdyacenciaCeldas(minas_coords);
  
}

void Tablero::asignarAdyacenciaCeldas(pair<int, int> coords[]) {

  for (int contador = 0; contador < 12; contador++) {
    int filaActual = coords[contador].first;
    int columnaActual = coords[contador].second;

    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {

        if (i == 0 && j == 0) continue; // central

        int filaVecina = filaActual + i;
        int columnaVecina = columnaActual + j;

        if (celdaValidaParaChecar(filaVecina, columnaVecina) &&
            tablero[filaVecina][columnaVecina].getMinaEstado() == false) {
          tablero[filaVecina][columnaVecina].sumarMinasAdyacentes();
        }
      }
    }
  }
}
