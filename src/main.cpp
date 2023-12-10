#include "capa-negocio/Juego.hpp"
#include "tools.hpp"
#include <iostream>
using namespace std;

void menuInicio();
void GameLoop(Juego partida);
void dibujarTablero();

int main() {
  menuInicio();
  return 0;
}

void menuInicio() {

  int opcion;

  do {
    Juego partida("Pedro");
    cout << "1. Nueva partida" << endl;
    cout << "2. Cargar partida" << endl;
    cout << "3. Historial" << endl;
    cout << "4. Salir" << endl;

    cout << "Elija una opcion: ";
    cin >> opcion;

    switch (opcion) {
    case 1:
      partida.nuevaPartida();
      GameLoop(partida);

      break;
    case 2: {
      int verificacion = partida.cargarPartida();

      if (verificacion != 1) {
        GameLoop(partida);
      } else {
        cout << "Sin Partida Anterior" << endl;
        waitForInput();
      }

      break;
    }
    case 3:
      // Codigo para mostrar historial
      break;
    case 4:
      // Salir del programa
      break;
    default:

      cout << "Opcion invalida" << endl;
    }

  } while (opcion != 4);
}

void dibujarTablero(Juego partida) {
  //clearScreen();
  partida.dibujarTablero();
}

void GameLoop(Juego partida) {

  int opcion;
  bool perdiste = false;

  while (perdiste == false) {
    dibujarTablero(partida);

    cout << "\n\nQue hacer?" << endl;
    cout << "1.Elegir Celda\t2.Guardar Y Salir" << "\t3.Salir" << endl;
    cout << "\n>>>";
    cin >> opcion;

    if (opcion == 1) { // Elegir Celda

      int fila = -1, columna = -1;

      cout << "inserte numero de fila: ";
      cin >> fila;
      cout << "inserte numero de columna: ";
      cin >> columna;

      string verificacionCoords = partida.verificarCoordenadas(fila, columna);
      if (verificacionCoords != "") {
        cout << "\n" << verificacionCoords;
        waitForInput();
        continue;
      }

      while (opcion != -1) {

        printf("Accion a tomar en (%d,%d):\n", fila, columna);
        cout << "1.Revelar Celda\t2.Marcar Celda\t3.Nada" << endl;
        cout << ">>> ";
        cin >> opcion;

        switch (opcion) {

        case 1: {
          if (partida.revelarCelda(fila, columna) == 1) {
            perdiste = true;
            partida.acabarPartida();
          } 
          opcion = -1;
          break;
        }

        case 2: {

          partida.marcarCelda(fila, columna);
          cout << "Marcado Hecho con exito" << endl;
          waitForInput();
          opcion = -1; // salir
          break;
        }

        case 3: {
          opcion = -1;
          break;
        }

        default:
          cout << "Opcion invalida" << endl;
          break;
        }
      }

    } else if (opcion == 2) {
      partida.guardarPartida();
      break;

    } else if (opcion == 3) {
      break;
    } else {
      cout << "Opcion invalida" << endl;
      waitForInput();
    }
  }
}