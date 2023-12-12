#include "capa-negocio/UI.hpp"
#include <cstdio>
#include <ncurses.h>

using namespace std;

void menuInicio();
int seleccionDeMenu(int opcion);
void GameLoop(Juego partida);

UI ui = UI();

int main() {
  menuInicio();
  ui.terminarUI();
  return 0;
}

void menuInicio() {
  const int ITEMS = 4;
  string menuItems[ITEMS] = {"1 - Nueva Partida", "2 - Cargar Partida", "3 - Historial", "4 - Salir"};
  int selectedOption = 0;
  bool run = true;

  do {
    ui.limpiarPantalla();
    ui.imprimirEn(3, ui.getScreenWidth() / 2 - 10, "BUSCA MINAS - JUEGO" , YELLOW);

    for (int i = 0; i < ITEMS; i++) {
      if (i == selectedOption) {
        ui.imprimirEn(i + 5, ui.getScreenWidth() / 2 - 15, menuItems[i].c_str(), CYAN);
      } else {
        ui.imprimirEn(i + 5, ui.getScreenWidth() / 2 - 15, menuItems[i].c_str(), WHITE);
      }
    }

    ui.imprimirEn(15, ui.getScreenWidth() / 2 - 20, "W - arriba | S - abajo | Enter - elegir" , CYAN);
    int key = getch();

    if (key == 's') {
      selectedOption++;
      if (selectedOption >= ITEMS)
        selectedOption = 0;

    } else if (key == 'w') {
      selectedOption--;
      if (selectedOption < 0)
        selectedOption = 3;

    } else if (key == '\n') {
      if (seleccionDeMenu(selectedOption + 1) != 0) {
        run = false;
      }
    }

  } while (run == true);
}

int seleccionDeMenu(int opcion) {

  if (opcion == 1 || opcion == 2) {
    Juego partida = Juego("Nombre");

    if (opcion == 1) {
      partida.nuevaPartida();
      GameLoop(partida);

    } else {

      if (partida.cargarPartida() != 1) {
        GameLoop(partida);
      } else {
        // no hay partidas
      }
    }

  } else if (opcion == 3) { // Historial
    move(20, 1);
    ui.imprimirHistorial();
    getchar();
  } else { // Salir
    return 1;
  }

  return 0;
}

void GameLoop(Juego partida) {
  Coord cursor;
  cursor.fila = 3;
  cursor.columna = 3;
  bool perdiste = false;

  while (perdiste == false) {
    ui.limpiarPantalla();
    ui.pintarTablero(partida, cursor);
    ui.imprimirControlesJuego();
    int key = getch();

    // Movimiento
    if (key == 'w') {
      cursor.fila--; // Move up
      if (cursor.fila < 0) cursor.fila = 7;
    } else if (key == 's') {
      cursor.fila++; // Move down
      if (cursor.fila > 7) cursor.fila = 0;
    } else if (key == 'a') {
      cursor.columna--; // Move left
      if (cursor.columna < 0) cursor.columna = 7;
    } else if (key == 'd') {
      cursor.columna++; // Move right
      if (cursor.columna > 7) cursor.columna = 0;
    }

    // Acciones
    if (key == 'f') {
      partida.marcarCelda(cursor.fila, cursor.columna);

    } else if (key == 'r') {
      if (partida.revelarCelda(cursor.fila, cursor.columna) == 1) {
        ui.pintarTablero(partida, cursor);
        ui.imprimirEn(21, ui.getScreenWidth() / 2 - 15, "Haz Encontrado Una Mina Perdiste", RED );
        getchar();
        perdiste = true;
      }

    } else if (key == 'k') {
      ui.imprimirEn(21, 10, "¿Seguro Que Quieres Salir? [y]-Sí / [Cualquier Tecla]-No", MAGENTA);
      int seleccion = getch();

      if (seleccion == 'y') {
        ui.imprimirEn(21, 10, "¿ Guardar La Partida? [y]-Sí / [Cualquier Tecla]-No", MAGENTA);
        seleccion = getch();
        if (seleccion == 'y') partida.guardarPartida();
        else partida.acabarPartida();
        break;
      }
    }
  }
}