#include "../capa-datos/datos.hpp"

#ifdef _WIN32
#include "C:\msys64\mingw64\include\pdcurs36\wincon\curses.h"
#elif __linux__
#include <ncurses.h>
#endif

struct Coord {
  int fila;
  int columna;
};

#ifndef UI_H
#define UI_H

enum Color {
	RED=1,
	GREEN,
	CYAN,
	YELLOW,
	WHITE,
	MAGENTA,
	BLUE,
};

class UI {

private:

public:
	UI();

	void imprimirEn(int row, int col, const char* txt, Color color);
	void imprimir(Color color, const char* txt);
	void limpiarPantalla();
	void terminarUI();
	int getScreenWidth();
	void imprimirControlesJuego(); 
 	void pintarTablero(Juego partida, Coord cursor);
 	void imprimirHistorial();
};

#endif