#include "Celda.hpp"

Celda::Celda() { mina = false; }
Celda::Celda(bool minaEstado) { mina = minaEstado; }

bool Celda::getReveladoEstado() { return revelado; }
bool Celda::getMinaEstado() { return mina; }
bool Celda::getMarcadaEstado() { return marcada; }
int Celda::getNumMinasAdyacentes() { return minas_adyacentes; }

void Celda::setReveladoEstado(bool estado) { revelado = estado; }
void Celda::setMarcadoEstado(bool estado) {marcada = estado;}
void Celda::setNumMinasAdayacentes(int cantidad) {minas_adyacentes = cantidad;}

void Celda::sumarMinasAdyacentes() { minas_adyacentes++; }
