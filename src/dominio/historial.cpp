#include "headers/historial.hpp"
#include "../estructuras/item_historial.hpp"
#include "headers/utilidades.hpp"
#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;

Historial::Historial() {}

Historial::Historial(list<ItemHistorial> paginas) {
  paginas_registradas = paginas;
}
Historial::~Historial() {}

void Historial::agregarPagina(string url) {
  string tiempo = getTiempo();
  ItemHistorial pagina;
  pagina.url = url;
  pagina.fecha = split(tiempo, ' ');
  paginas_registradas.push_front(pagina);
}
void Historial::setHistorial(list<ItemHistorial> paginas) {
  paginas_registradas = paginas;
}
string Historial::getItemFormateado(ItemHistorial pagina) {
  return pagina.fecha[horaYMinutos] + " - " + pagina.url;
}

void Historial::printHistorial() {
  list<ItemHistorial>::iterator pagina;
  vector<string> fechaActual = paginas_registradas.begin()->fecha;
  string cabecera = getCabeceraFecha(fechaActual);
  cout << cabecera << endl;

  for (auto const &pagina : paginas_registradas) {
    if (fechasIguales(fechaActual, pagina.fecha))
      cout << getItemFormateado(pagina) << endl;
    else {
      string cabecera = getCabeceraFecha(pagina.fecha);
      fechaActual = pagina.fecha;
      cout << cabecera << endl;
      cout << getItemFormateado(pagina) << endl;
    }
  }
}

void Historial::addTesting(ItemHistorial pagina) { // Ignorar, remover luego
  paginas_registradas.push_front(pagina);
}

list<ItemHistorial>::iterator
Historial::getInicioHistorial() { // Devuelve un iterador al principio de la
                                  // lista del historial
  list<ItemHistorial>::iterator punteroAHistorial = paginas_registradas.begin();
  return punteroAHistorial;
}

list<ItemHistorial>::iterator
Historial::getFinalHistorial() { // Devuelve un iterador al final de la lista
                                 // del historial
  list<ItemHistorial>::iterator punteroAHistorial = paginas_registradas.end();
  return punteroAHistorial;
}

bool Historial::estaVacio() {
  if (paginas_registradas.empty())
    return true;
  return false;
}
int Historial::getCantidadDePaginas() { return paginas_registradas.size(); }
