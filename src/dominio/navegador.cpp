#include "headers/navegador.hpp"
#include "headers/utilidades.hpp"
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
// Establece el navegador en la página de inicio (no
// afecta el historial)

void Navegador::setHome() {   
  list<ItemHistorial> *l = new list<ItemHistorial>;
  ItemHistorial home;
  home.url = "Home";
  home.fecha = {""};
  l->push_back(home);
  paginaActual = l->begin();
}

// Confirma que el navegador se encuentra en la
// página de inicio Verdadero: Sí, está en la página
// de inicio.
// Falso:No, no está en la página de inicio.

bool Navegador::isHome() {   
  if (paginaActual->url == "Home") 
    return true;
  return false;
}

// Confirma si hay página a la que
// avanzar
// Verdadero: Sí, las hay
// Falso: No, no las hay

bool Navegador::hayPaginaSiguiente() { 
  if (paginaActual->url == "Home")     
    return false;                      
  if (paginaActual != historial.getInicioHistorial())
    return true;
  return false;
}

// Confirma si existe una página a la que
// volver
// Verdadero: Sí, las hay.
// Falso: No, no las hay.

bool Navegador::hayPaginaAnterior() { 
  list<ItemHistorial>::iterator l = paginaActual;   
  l++;                                            
  if (paginaActual->url == "Home")
    return false;
  if (l != historial.getFinalHistorial())
    return true;
  return false;
}
