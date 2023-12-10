#include "../capa-negocio/Celda.hpp"
#include "../capa-negocio/Juego.hpp"
#include <fstream>
#include <iostream>
#include <ostream>

using namespace std;

inline void guardarLog(string filename, string nombre, string fecha, int t_size,
                       int n_minas, string resultado) {
  fstream fout;
  fout.open(filename, ios::app); // Abrir en modo append en lugar de overwrite
  fout << nombre <<" "<< fecha <<" "<< t_size <<" "<< n_minas <<" "<< resultado << endl;
  fout.close();
}

inline void saveState(string filename, Celda tablero[8][8]) {
  ofstream fout(filename);
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

inline int loadState(string filename, Celda tablero[8][8]) {

  ifstream fin(filename);

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
