#ifndef CELDA_H
#define CELDA_H

/**
  * Celda representa una celda individual en un tablero de campo minado. 
  * Puede contener una mina, estar revelado, estar marcada o estar vacía.  
*/

class Celda {

private:
  bool mina;
  int minas_adyacentes = 0;
  bool revelado = false;
  bool marcada = false;

public:
  Celda();
  Celda(bool minaEstado);

  bool getReveladoEstado();
  bool getMinaEstado();
  bool getMarcadaEstado();
  int getNumMinasAdyacentes();

  void setReveladoEstado(bool estado);
  void setMarcadoEstado(bool estado);
  void setNumMinasAdayacentes(int cantidad);
  void sumarMinasAdyacentes();

};

#endif