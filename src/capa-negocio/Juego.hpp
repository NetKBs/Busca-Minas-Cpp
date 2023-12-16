#include "Tablero.hpp"
#include <iostream>
#include <chrono>
#include <iomanip> 
#include <sstream>

#ifndef JUEGO_H
#define JUEGO_H

/// Filenames
#define ESTADO_TAB_FN "tablero.dat"
#define DATOS_JUG_FN "juego.dat"
#define LOG "log.dat"

enum Resultado {
  DERROTA,
  VICTORIA,
  INCONCLUSO
};

class Juego {

private:
  Tablero tablero = *new Tablero();
  /// Estadisticas
  std::string usuario;
  Resultado resultado;
  std::string fecha_hora;
  int numero_jugadas = 0;
public:

  Juego (std::string usuario);

  void nuevaPartida();
  int cargarPartida();
  void guardarPartida();
  /// Guarda en log el resultado de la partida
  void acabarPartida();
  /// Si return == 1, el resultado será derrota y acabará la partida 
  int revelarCelda(int fila, int columna);
  void marcarCelda(int fila, int columna);
  std::string chequearVictoria();

  void setNombre(std::string nombre);
  void setFecha(std::string fecha);
  void setNumJugadas(int jugadas);
  void setResultado(Resultado resultado);

  Tablero getTablero();
  std::string getNombre();
  std::string obtenerFechaHora();
  std::string getResultadoEstado();

  void mostrarTableroDetalles();

};

#endif