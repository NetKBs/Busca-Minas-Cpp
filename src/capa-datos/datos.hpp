#include "../capa-negocio/Celda.hpp"
#include "../capa-negocio/Juego.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>

using namespace std;

string ruta = "src/capa-datos/";

inline void guardarJuegoDatos(string filename, string nombre, string fecha,
                              int t_size, int n_minas, int num_jugadas,
                              string resultado) {

  ofstream fout(ruta + filename);
  fout << nombre << " " << fecha << " " << t_size << " " << n_minas << " "
       << num_jugadas << " " << resultado << endl;
  fout.close();
}

inline void guardarLog(string filename, string nombre, string fecha, int t_size,
                       int n_minas, int num_jugadas, string resultado) {

  fstream fout;
  fout.open(ruta + filename, ios::app); // Abrir en modo append en lugar de overwrite
  fout << nombre << " " << fecha << " " << t_size << " " << n_minas << " "
       << num_jugadas << " " << resultado << endl;
  fout.close();
}

inline void saveState(string filename, Celda tablero[8][8]) {
  ofstream fout(ruta + filename);

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      fout << tablero[i][j].getMinaEstado() << " ";
      fout << tablero[i][j].getReveladoEstado() << " ";
      fout << tablero[i][j].getMarcadaEstado() << " ";
      fout << tablero[i][j].getNumMinasAdyacentes();
      fout << "\n";
    }
    fout << "\n";
  }
  fout.close();
}

inline int loadStateTablero(string filename, Celda tablero[8][8]) {

  ifstream fin(ruta + filename);

  if (!fin.is_open()) {
    return 1;
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {

      int mina, revelado, marcado, minasAdy;
      // ignorar espacios
      fin >> skipws >> mina;
      fin >> skipws >> revelado;
      fin >> skipws >> marcado;
      fin >> skipws >> minasAdy;

      Celda celda = Celda();

      if (mina)
        celda = Celda(true);
      if (revelado)
        celda.setReveladoEstado(revelado);
      if (marcado)
        celda.setMarcadoEstado(marcado);
      celda.setNumMinasAdayacentes(minasAdy);

      tablero[i][j] = celda;
    }
  }

  fin.close();
  return 0;
}

inline void loadStateJuego(string filename, Juego &partida) {
  ifstream fin(ruta + filename);

  string nombre, fecha, hora, resultado;
  int t_size, n_minas, num_jugadas;

  fin >> nombre;
  fin >> fecha;
  fin >> hora;
  fin >> t_size;
  fin >> n_minas;
  fin >> num_jugadas;
  fin >> resultado;

  // Set the loaded data to the Juego instance
  partida.setNombre(nombre);
  partida.setFecha(fecha+ " " + hora);
  partida.setNumJugadas(num_jugadas);

  if (resultado == "INCONCLUSO") {
    partida.setResultado(INCONCLUSO);
  } else if (resultado == "VICTORIA") {
    partida.setResultado(VICTORIA);
  } else {
    partida.setResultado(DERROTA);
  }

  fin.close();
}
