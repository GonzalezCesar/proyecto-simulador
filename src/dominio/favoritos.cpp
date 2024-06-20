#include "headers/favoritos.hpp"
#include "../estructuras/archivo.hpp"
#include "headers/utilidades.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::list;
using std::queue;
using std::string;
using std::vector;

Favoritos::Favoritos() {}

void Favoritos::crearCarpeta(string ruta) {
  archivo nuevaCarpeta;
  vector<string> rutaSegmentada = split(ruta, '/');
  nuevaCarpeta.tipo = "CARPETA";
  nuevaCarpeta.nombre = rutaSegmentada[rutaSegmentada.size() - 1];
  nuevaCarpeta.ruta = ruta;
  archivos.push_front(nuevaCarpeta);
}

list<archivo> Favoritos::getArchivos() { return archivos; }

void Favoritos::guardarPagina(string nombre, string url) {
  archivo nuevaPagina;
  nuevaPagina.tipo = "PAGINA-" + url;
  nuevaPagina.nombre = nombre;
  nuevaPagina.ruta = nombre;
  archivos.push_back(nuevaPagina);
}

void Favoritos::modificarRutaPagina(string pagina, string rutaCarpeta) {

  for (auto iterador = archivos.begin(); iterador != archivos.end();
       ++iterador) {
    if (iterador->nombre == pagina) {
      iterador->ruta = rutaCarpeta + "/" + iterador->nombre;
      break;
    }
  }
}


bool Favoritos::existeCarpeta(string ruta) {
  for (auto archivo : archivos) {
    if (archivo.tipo == "CARPETA")
      return true;
  }
  return false;
}

void Favoritos::eliminarPagina(string ruta, bool eliminadoPermanente) {

  list<archivo>::iterator iteradorPagina = archivos.begin();
  while (iteradorPagina != archivos.end()) {
    if (iteradorPagina->ruta == ruta) {
      archivo pagina = getArchivoDeIterador(iteradorPagina);
      if (!eliminadoPermanente)
        actualizarPaginasBorradas(pagina);
      iteradorPagina = archivos.erase(iteradorPagina);
      break;
    } else {
      ++iteradorPagina;
    }
  }
}

// Elimina permamnentemente la primera página
// eliminada si hay 6 elementos en las páginas eliminadas.

void Favoritos::actualizarPaginasBorradas(
    archivo pagina) { 
  paginasEliminadas.push(pagina);
  if (paginasEliminadas.size() == 6) {
    paginasEliminadas.pop();
  }
}

void Favoritos::restaurarPagina() {
  archivos.push_back(paginasEliminadas.front());
  paginasEliminadas.pop();
}

// Retorna archivo a partir de una ruta
archivo Favoritos::getArchivoDeRuta(
    string ruta) { 
  archivo a;
  for (auto archivo : archivos) {
    if (archivo.ruta == ruta) {
      a.nombre = archivo.nombre;
      a.ruta = archivo.ruta;
      a.tipo = archivo.tipo;
      break;
    }
  }
  return a;
}

// Elimina permanentemente todo el contenido asociado a una
// carpeta

void Favoritos::eliminarContenidoEnCarpeta(
    string ruta) {   vector<string> rutaSegmentada = split(ruta, '/');
  string nombreCarpeta = rutaSegmentada[rutaSegmentada.size() - 1];

  auto iteradorArchivo = archivos.begin();
  while (iteradorArchivo != archivos.end()) {

    if (esDescendiente(nombreCarpeta, iteradorArchivo->ruta)) {
      iteradorArchivo = archivos.erase(iteradorArchivo);
    } else {
      ++iteradorArchivo;
    }
  }
}

void Favoritos::eliminarArchivo(string ruta) {
  list<archivo>::iterator iteradorArchivo = archivos.begin();
  while (iteradorArchivo != archivos.end()) {
    archivo a = getArchivoDeIterador(iteradorArchivo);
    if (iteradorArchivo->ruta == ruta) {
      iteradorArchivo = archivos.erase(iteradorArchivo);
      break;
    } else {
      ++iteradorArchivo;
    }
  }
}

string Favoritos::getPaginaURL(string paginaRuta) {
  string url;
  for (auto iteradorArchivo : archivos) {
    if ((paginaRuta == iteradorArchivo.ruta) && (esPagina(iteradorArchivo))) {
      string url = split(iteradorArchivo.tipo, '-')[1];
      return url;
    }
  }
  return url;
}

string Favoritos::getRutaCarpeta(int indice) {
  int conteo = 1;
  for (list<archivo>::iterator iteradorArchivo = archivos.begin();
       iteradorArchivo != archivos.end(); iteradorArchivo++) {
    archivo elementoArchivo = getArchivoDeIterador(iteradorArchivo);

    if (esCarpeta(elementoArchivo)) {
      if (conteo == indice) {
        return elementoArchivo.ruta;
      }
      conteo++;
    }
  }
  return "";
}

string Favoritos::getRutaPagina(int indice) {
  int conteo = 1;
  for (list<archivo>::iterator iteradorArchivo = archivos.begin();
       iteradorArchivo != archivos.end(); iteradorArchivo++) {
    archivo elementoArchivo = getArchivoDeIterador(iteradorArchivo);

    if (esPagina(elementoArchivo)) {
      if (conteo == indice) {
        return elementoArchivo.ruta;
      }
      conteo++;
    }
  }
  return "";
}

string Favoritos::getRutaPaginaEliminada(int indice) {
  int conteo = 1;
  queue<archivo> copiaEliminados = paginasEliminadas;
  while (!copiaEliminados.empty()) {

    archivo elementoArchivo = copiaEliminados.front();
    if (conteo == indice) {
      return elementoArchivo.ruta;
    }
    conteo++;
    copiaEliminados.pop();
  }
  return "";
}

queue<archivo> Favoritos::getPaginasEliminadas() { return paginasEliminadas; }

bool Favoritos::hayPaginas() {
  for (list<archivo>::iterator iteradorArchivo = archivos.begin();
       iteradorArchivo != archivos.end(); iteradorArchivo++) {
    archivo elementoArchivo = getArchivoDeIterador(iteradorArchivo);
    if (esPagina(elementoArchivo)) {
      return true;
    }
  }
  return false;
}

bool Favoritos::hayCarpetas() {
  for (list<archivo>::iterator iteradorArchivo = archivos.begin();
       iteradorArchivo != archivos.end(); iteradorArchivo++) {
    archivo elementoArchivo = getArchivoDeIterador(iteradorArchivo);

    if (esCarpeta(elementoArchivo)) {
      return true;
    }
  }
  return false;
}

bool Favoritos::hayPaginasEliminadas() {
  if (!paginasEliminadas.empty())
    return true;
  else
    return false;
}

bool Favoritos::existePagina(string nombre) {
  for (list<archivo>::iterator iteradorArchivo = archivos.begin();
       iteradorArchivo != archivos.end(); iteradorArchivo++) {

    archivo elementoArchivo = getArchivoDeIterador(iteradorArchivo);
    if ((esPagina(elementoArchivo)) && (iteradorArchivo->nombre == nombre)) {
      return true;
    }
  }
  return false;
}

void Favoritos::setArchivos(list<archivo> favoritos) { archivos = favoritos; }
void Favoritos::setPaginasEliminadas(queue<archivo> paginas) {
  paginasEliminadas = paginas;
}
