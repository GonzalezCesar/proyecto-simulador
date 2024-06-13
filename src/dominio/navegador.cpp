#include "../include/navegador.hpp"
#include "../include/utilidades.hpp"
#include <iostream>
#include <list>

using std::list;
using std::string;

Navegador::Navegador() {}
void Navegador::irSiguentePagina() { paginaActual--; }
void Navegador::irPaginaAnterior() { paginaActual++; }
string Navegador::getPaginaActual() { return paginaActual->url; }

void Navegador::irNuevaPagina(string url) {
  historial.agregarPagina(url);
  paginaActual = historial.getInicioHistorial();
}

void Navegador::setHome() { // Establece el navegador en la página de inicio (no
                            // afecta el historial)
  list<ItemHistorial> *l = new list<ItemHistorial>;
  ItemHistorial home;
  home.url = "Home";
  home.fecha = {""};
  l->push_back(home);
  paginaActual = l->begin();
}

bool Navegador::isHome() { // Confirma que el navegador se encuentra en la
                           // página de inicio Verdadero: Sí, está en la página
                           // de inicio.
  if (paginaActual->url == "Home") // Falso:No, no está en la página de inicio.
    return true;
  return false;
}

bool Navegador::hayPaginaSiguiente() { // Confirma si hay página a la que
                                       // avanzar
  if (paginaActual->url == "Home") // Verdadero: Sí, las hay
    return false;                  // Falso: No, no las hay
  if (paginaActual != historial.getInicioHistorial())
    return true;
  return false;
}
bool Navegador::hayPaginaAnterior() { // Confirma si existe una página a la que
                                      // volver
  list<ItemHistorial>::iterator l = paginaActual; // Verdadero: Sí, las hay.
  l++;                                            // Falso: No, no las hay.
  if (paginaActual->url == "Home")
    return false;
  if (l != historial.getFinalHistorial())
    return true;
  return false;
}
