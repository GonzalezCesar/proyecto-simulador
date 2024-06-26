#include "../../estructuras/item_historial.hpp"
#include <iostream>
#include <list>
#include <stack>

#ifndef HISTORIAL
#define HISTORIAL

using std::list;
using std::string;

class Historial {
private:
  list<ItemHistorial> paginas_registradas;

public:
  Historial();
  Historial(list<ItemHistorial> paginas);
  void agregarPagina(string url);
  void setHistorial(list<ItemHistorial> paginas);
  list<ItemHistorial>::iterator getInicioHistorial();
  list<ItemHistorial>::iterator getFinalHistorial();
  bool estaVacio();
  int getCantidadDePaginas();
  list<ItemHistorial> getHistorial();
  ~Historial();
};

#endif
