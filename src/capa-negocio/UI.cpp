#include "UI.hpp"

using namespace std;

UI::UI() {
  initscr();
  noecho();    // Disable key echoing
  cbreak();    // Take inputs character by character
  curs_set(0); // ocultamos cursor

  start_color();
  init_pair(RED, COLOR_RED, COLOR_BLACK);
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
  init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
}

void UI::imprimirEn(int row, int col, const char* txt, Color color) {
  move(row, col);
  clrtoeol(); // limpiar linea
  attron(COLOR_PAIR(color));
  mvprintw(row, col, txt);
  attroff(COLOR_PAIR(color));
  refresh();
}

void UI::imprimir(Color color, const char* txt) {
  attron(COLOR_PAIR(color));
  printw(txt);
  attroff(COLOR_PAIR(color));
  refresh();
}

void UI::limpiarPantalla() {
  clear();
  refresh();
}

void UI::imprimirControlesJuego() {
  imprimirEn(15, 10, "Movimiento:", CYAN);
   imprimirEn(16, 10, "w - Arriba", CYAN);
   imprimirEn(17, 10, "s - Abajo", CYAN);
   imprimirEn(18, 10, "a - Izquierda", CYAN);
   imprimirEn(19, 10, "d - Derecha", CYAN);

   imprimirEn(15, 30, "Acciones:", CYAN);
   imprimirEn(16, 30, "r - Revelar", CYAN);
   imprimirEn(17, 30, "f - Marcar", CYAN);
   imprimirEn(18, 30, "k - Salir", CYAN);
}

void UI::pintarTablero(Juego partida, Coord cursor) {
  Tablero tablero = partida.getTablero();
  int tableroWidth = 8 * 2 + 1;
  int posInicialX = (getScreenWidth() - tableroWidth) / 2;
  int espaciadoSuperior = 3;

  attron(COLOR_PAIR(GREEN));
  for (int fila = 0; fila < 8; fila++) {
    mvprintw(fila + espaciadoSuperior, posInicialX, "  "); // Agregamos espaciadoSuperior
    for (int columna = 0; columna < 8; columna++) {

      if (tablero.tablero[fila][columna].getReveladoEstado() && !tablero.tablero[fila][columna].getMinaEstado()) {

        if (fila == cursor.fila && columna == cursor.columna) {
          imprimir(RED, (to_string(tablero.tablero[fila][columna].getNumMinasAdyacentes()) + "  ").c_str());
          attron(COLOR_PAIR(GREEN));
        } else {
          imprimir(WHITE, (to_string(tablero.tablero[fila][columna].getNumMinasAdyacentes()) + "  ").c_str());
          attron(COLOR_PAIR(GREEN));
        }

      } else if (tablero.tablero[fila][columna].getMarcadaEstado()) {
        if (fila == cursor.fila && columna == cursor.columna) {
          imprimir(RED, "?  ");
          attron(COLOR_PAIR(GREEN));
        } else {
          imprimir(YELLOW, "?  ");
          attron(COLOR_PAIR(GREEN));
        }

      } else if (tablero.tablero[fila][columna].getMinaEstado() && tablero.tablero[fila][columna].getReveladoEstado()) {
          imprimir(MAGENTA, "!  ");
          attron(COLOR_PAIR(GREEN));

      } else {
        if (fila == cursor.fila && columna == cursor.columna) {
          imprimir(RED, "*  ");
          attron(COLOR_PAIR(GREEN));
        } else {
          printw("*  ");
        }
      }
    }
    printw("\n");
  }
  attroff(COLOR_PAIR(GREEN));
  refresh(); 
}

void UI::imprimirHistorial() {
    limpiarPantalla();
    std::vector<Datos> log = cargarLog("log.dat");

    int fila = 0;
    int columna = getScreenWidth() / 2 - 20;

    int maxFila, maxColumna;
    getmaxyx(stdscr, maxFila, maxColumna); // Obtener el tamaño máximo de la ventana

    // Habilitar el scroll vertical
    scrollok(stdscr, TRUE);

    for (const Datos& datos : log) {
        mvprintw(fila, columna, "Nombre: %s", datos.nombre.c_str());
        mvprintw(fila + 1, columna, "Fecha: %s", datos.fecha.c_str());
        mvprintw(fila + 2, columna, "Hora: %s", datos.hora.c_str());
        mvprintw(fila + 3, columna, "Tamaño: %d", datos.t_size.c_str());
        mvprintw(fila + 4, columna, "Minas: %d", datos.n_minas.c_str());
        mvprintw(fila + 5, columna, "Jugadas: %d", datos.n_jugadas.c_str());
        mvprintw(fila + 6, columna, "Resultado: %s", datos.resultado.c_str());

        fila += 8; // Ajustar la posición de impresión para el siguiente conjunto de datos

        // Verificar si se ha alcanzado el final de la ventana
        if (fila >= maxFila - 8) {
            mvprintw(maxFila-1, 0, "Presione una tecla para continuar...");
            refresh();
            getch();

            // Limpiar la pantalla y restablecer la posición de impresión
            limpiarPantalla();
            fila = 0;
        }
    }
}


int UI::getScreenWidth() { return getmaxx(stdscr); }

void UI::terminarUI() { endwin(); }
