#include "capa-negocio/Juego.hpp"
#include "capa-negocio/UI.hpp"
#include <cstdio>
#include <iostream>

/*#ifdef _WIN32
#define OS "Windows"
#include "C:\msys64\mingw64\include\pdcurs36\wincon\curses.h"
#elif __linux__
#define OS "Linux"
#include <ncurses.h>
#endif*/

using namespace std;

void menuInicio();
void GameLoop(Juego partida);
void pintarTablero(Juego partida);
void limpiarPantalla();

struct Coord {
  int fila;
  int columna;
};
Coord cursor;

int main() {


  menuInicio();
  endwin();
  return 0;
}

void menuInicio() {

  int opcion;

  do {
    echo();      // Habilita el eco de teclas
    nocbreak();  // Toma entradas en modo de línea
    curs_set(1); // habilitamos cursor
    limpiarPantalla();

    Juego partida("Pedro");
    cursor.fila = 3;
    cursor.columna = 3;

    attron(COLOR_PAIR(1));
    mvprintw(2, 20, "1. Nueva partida");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(3, 20, "2. Cargar partida");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(4, 20, "3. Historial");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(5, 20, "4. Salir");
    attroff(COLOR_PAIR(2));

    mvprintw(7, 20, ">>> ");
    scanw("%d", &opcion);
    fflush(stdin);
    refresh();

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

void limpiarPantalla() {
  clear();
  refresh();
}

void pintarTablero(Juego partida) {
  Tablero tablero = partida.getTablero();

  int SCREEN_WIDTH = getmaxx(stdscr);
  int tableroWidth = 8 * 2 + 1;
  int posInicialX = (SCREEN_WIDTH - tableroWidth) / 2;
  int espaciadoSuperior = 3;

  attron(COLOR_PAIR(2));
  for (int fila = 0; fila < 8; fila++) {
    mvprintw(fila + espaciadoSuperior, posInicialX,
             "  "); // Agregamos espaciadoSuperior

    for (int columna = 0; columna < 8; columna++) {

      if (tablero.tablero[fila][columna].getReveladoEstado() &&
          !tablero.tablero[fila][columna].getMinaEstado()) {
        if (fila == cursor.fila && columna == cursor.columna) {
          attron(COLOR_PAIR(1));
          printw("%d  ",
                 tablero.tablero[fila][columna].getNumMinasAdyacentes());
          attron(COLOR_PAIR(2));
        } else {
          attron(COLOR_PAIR(5));
          printw("%d  ",
                 tablero.tablero[fila][columna].getNumMinasAdyacentes());
          attron(COLOR_PAIR(2));
        }

      } else if (tablero.tablero[fila][columna].getMarcadaEstado()) {

        if (fila == cursor.fila && columna == cursor.columna) {
          attron(COLOR_PAIR(1));
          printw("?  ");
          attron(COLOR_PAIR(2));
        } else {
          attron(COLOR_PAIR(4));
          printw("?  ");
          attron(COLOR_PAIR(2));
        }

      } else if (tablero.tablero[fila][columna].getMinaEstado() &&
                 tablero.tablero[fila][columna].getReveladoEstado()) {
        if (fila == cursor.fila && columna == cursor.columna) {
          attron(COLOR_PAIR(1));
          printw("!  ");
          attron(COLOR_PAIR(2));
        } else {
          attron(COLOR_PAIR(6));
          printw("!  ");
          attron(COLOR_PAIR(2));
        }

      } else {
        if (fila == cursor.fila && columna == cursor.columna) {
          attron(COLOR_PAIR(1));
          printw("*  ");
          attron(COLOR_PAIR(2));
        } else {
          printw("*  ");
        }
      }
    }
    printw("\n");
  }

  attroff(COLOR_PAIR(2));

  refresh();
}

void GameLoop(Juego partida) {
 
  bool perdiste = false;

  while (perdiste == false) {
    limpiarPantalla();
    pintarTablero(partida);
    attron(COLOR_PAIR(3));
    mvprintw(15, 10, "Movimiento:");
    mvprintw(16, 10, "w - Arriba");
    mvprintw(17, 10, "s - Abajo");
    mvprintw(18, 10, "a - Izquierda");
    mvprintw(19, 10, "d - Derecha");

    mvprintw(15, 30, "Acciones:");
    mvprintw(16, 30, "r - Revelar");
    mvprintw(17, 30, "f - Marcar");
    mvprintw(18, 30, "k - Salir");
    attroff(COLOR_PAIR(3));
    refresh();

    int key = getch();

    if (key == 'w')
      cursor.fila--; // Move up
    else if (key == 's')
      cursor.fila++; // Move down
    else if (key == 'a')
      cursor.columna--; // Move left
    else if (key == 'd')
      cursor.columna++; // Move right

    // Reajuste del cursor
    if (cursor.fila > 7)
      cursor.fila = 0;
    if (cursor.fila < 0)
      cursor.fila = 7;
    if (cursor.columna > 7)
      cursor.columna = 0;
    if (cursor.columna < 0)
      cursor.columna = 7;

    // Acciones
    if (key == 'f') {
      partida.marcarCelda(cursor.fila, cursor.columna);

    } else if (key == 'r') {
      int mina = partida.revelarCelda(cursor.fila, cursor.columna);
      if (mina == 1) {
        pintarTablero(partida);
        refresh();
        getchar();
        limpiarPantalla();
        perdiste = true;
      }

    } else if (key == 'k') {
     
      attron(COLOR_PAIR(6));
      mvprintw(21, 10, "¿Seguro Que Quieres Salir? [y]-Sí / [Cualquier Tecla]-No");
      int seleccion = getch();

      if (seleccion == 'y') {
        move(21, 10);
        clrtoeol(); // limpiar linea
        refresh();

        mvprintw(21, 10, "¿Guardar La Partida? [y]-Sí / [Cualquier Tecla]-No");
        seleccion = getch();
        refresh();

        if (seleccion == 'y') {
          partida.guardarPartida();
        } else {
          partida.acabarPartida();
        }

        break;
      }

      refresh();
      attroff(COLOR_PAIR(6));

    }
  }
}