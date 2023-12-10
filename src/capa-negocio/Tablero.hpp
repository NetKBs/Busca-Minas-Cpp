#include "Celda.hpp"
#include <utility>

#ifndef TABLERO_H
#define TABLERO_H

/**
 * Tablero que contiene una matriz de celdas
 * por defecto las celdas no tienen minas
 */

class Tablero {
private:
  static const int FILAS = 8, COLUMNAS = 8;
  const int MAX_MINAS = 12;

public: 
  Celda tablero[FILAS][COLUMNAS];

public:

   Celda obtenerCelda(int fila, int columna); 

   /// Intercambia el valor del marcado en la celda
   void marcarCelda(int fila, int columna);

   /// Revela la celda. Return 0 : OK / Return 1 : Mina Encontrada
   int revelarCelda(int fila, int columna);

   bool celdaValidaParaChecar(int fila, int columna);

   /// CHULETA PARA VER DETALLES BORRAR
   void mostrarTableroDetalles();


   /// Asigna minas en celdas aleatoriamente
   /// asigna adayacencia a las celdas vecinas
   void generarTablero();

   void dibujarTablero();

  private:
   /// Recibe coordenadas de las minas 
   /// Asigna adyacencia a las celdas al rededor
   void asignarAdyacenciaCeldas(std::pair<int, int> coords[]);

};

#endif