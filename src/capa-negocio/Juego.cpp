#include "Juego.hpp"
#include "../capa-datos/datos.hpp"

Juego::Juego(std::string usuario) {
  this->usuario = usuario;
  resultado = INCONCLUSO;
  fecha_hora = obtenerFechaHora();
}

void Juego::nuevaPartida() { tablero.generarTablero(); }

int Juego::cargarPartida() {
  int verificar = loadStateTablero(ESTADO_TAB_FN, tablero.tablero);
  if (verificar != 1) {
    loadStateJuego(DATOS_JUG_FN, *this);
    return 0;
  }
  return 1;
}

std::string Juego::verificarCoordenadas(int fila, int columna) {

  if ((fila < 0 || columna < 0) && (fila > 7 || columna > 7)) {
    return "Coordenadas Invalidas";
  } else if (tablero.obtenerCelda(fila, columna).getReveladoEstado()) {
    return "Celda Ya Revelada";
  }

  return "";
}

int Juego::revelarCelda(int fila, int columna) {
  numero_jugadas++;
  int verificacion = tablero.revelarCelda(fila, columna);
  if (verificacion == 1)
    resultado = DERROTA;
  return verificacion;
}

void Juego::marcarCelda(int fila, int columna) {
  tablero.marcarCelda(fila, columna);
}

void Juego::dibujarTablero() {
  tablero.mostrarTableroDetalles();
  tablero.dibujarTablero();
}

std::string Juego::obtenerFechaHora() {
  std::stringstream date_time;
  auto now = std::chrono::system_clock::now();

  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
  std::tm *localtm = std::localtime(&now_c);

  date_time << std::put_time(localtm, "%F %T");

  return date_time.str();
}

std::string Juego::getResultadoEstado() {
  if (resultado == DERROTA)
    return "DERROTA";
  else if (resultado == VICTORIA)
    return "VICTORIA";
  else
    return "INCONCLUSO";
}

void Juego::chequearVictoria() {
  int minasMarcadas = 0;
  int celdasReveladas = 0;

  for (int fila = 0; fila < 8; fila++) {
    for (int columna = 0; columna < 8; columna++) {

      Celda celda = tablero.obtenerCelda(fila, columna);

      if (celda.getMarcadaEstado() && celda.getMinaEstado()) {
        minasMarcadas++;
      }

      if (celda.getReveladoEstado() && !celda.getMinaEstado()) {
        celdasReveladas++;
      }
    }
  }

  if (minasMarcadas == 12) {
    cout << "Felicidades, has ganado marcando todas las minas!" << endl;
  } else if (celdasReveladas == (8 * 8 - 12)) {
    cout << "Felicidades, has ganado revelando todas las celdas sin minas!" << endl;
  }
}

void Juego::acabarPartida() {
  guardarLog(LOG, usuario, fecha_hora, 8, 12, numero_jugadas,
             getResultadoEstado());
}

void Juego::guardarPartida() {
  saveState(ESTADO_TAB_FN, tablero.tablero);
  guardarJuegoDatos(DATOS_JUG_FN, usuario, fecha_hora, 8, 12, numero_jugadas,
                    getResultadoEstado());
}

void Juego::setNombre(std::string nombre) { usuario = nombre; }
void Juego::setFecha(std::string fecha) { fecha_hora = fecha; }
void Juego::setNumJugadas(int jugadas) { numero_jugadas = jugadas; }
void Juego::setResultado(Resultado resultado) { this->resultado = resultado; }