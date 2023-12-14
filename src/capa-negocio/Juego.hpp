#include "Tablero.hpp"
#include <iostream>
#include <chrono>
#include <iomanip> 
#include <sstream>

#ifndef JUEGO_H
#define JUEGO_H

#define ESTADO_TAB_FN "tablero.dat" // tablero filaname
#define DATOS_JUG_FN "juego.dat" // datos juego
#define LOG "log.dat"

enum Resultado {
  DERROTA,
  VICTORIA,
  INCONCLUSO
};

class Juego {

private:
  Tablero tablero = *new Tablero();
  std::string usuario;
  Resultado resultado;
  std::string fecha_hora;
  int numero_jugadas = 0;
public:

  Juego (std::string usuario);

  std::string obtenerFechaHora();
  std::string getResultadoEstado();
  void nuevaPartida();
  int cargarPartida();
  void guardarPartida();
  int revelarCelda(int fila, int columna);
  void marcarCelda(int fila, int columna);
  std::string chequearVictoria();
  void acabarPartida();
  void setNombre(std::string nombre);
  void setFecha(std::string fecha);
  void setNumJugadas(int jugadas);
  void setResultado(Resultado resultado);
  Tablero getTablero();
  std::string getNombre();

  void mostrarTableroDetalles();

};

#endif