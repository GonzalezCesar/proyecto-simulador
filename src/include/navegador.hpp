#include "../include/historial.hpp"
#include <iostream>
#include <list>
using std::list;
using std::string;

#ifndef NAVEGADOR
#define NAVEGADOR

class Navegador {
private:
  list<ItemHistorial>::iterator paginaActual;

public:
  Historial historial;

  Navegador();
  void irSiguentePagina();
  void irPaginaAnterior();
  string getPaginaActual();
  void irNuevaPagina(string url);
  void setHome();
  bool isHome();
  bool hayPaginaSiguiente();
  bool hayPaginaAnterior();
};
#endif
