#include "headers/favoritos.hpp"
#include "../estructuras/archivo.hpp"
#include "headers/utilidades.hpp"
#include <algorithm>
#include <codecvt>
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

list<archivo> *Favoritos::getArchivos() { return &archivos; }

void Favoritos::guardarPagina(string nombre, string url) {
  archivo nuevaPagina;
  nuevaPagina.tipo = "PAGINA-" + url;
  nuevaPagina.nombre = nombre;
  nuevaPagina.ruta = nombre;
  archivos.push_back(nuevaPagina);
}

void Favoritos::printFavoritos() {
  for (auto archivo : archivos) {
    printArchivo(archivo);
  }
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

void Favoritos::copiarQueue(queue<archivo> copia) {
  int size = copia.size();
  for (int i = 0; !copia.empty(); i++) {
    paginasEliminadas.push(copia.front());
    copia.pop();
  }
}
//--------------------------------------------Remover luego
void Favoritos::printPaginasEliminadas() {
  queue<archivo> copiaPaginasEliminadas = paginasEliminadas;
  for (int i = 0; i < paginasEliminadas.size(); i++) {
    cout << i + 1 << ". " << copiaPaginasEliminadas.front().nombre << endl;
    copiaPaginasEliminadas.pop();
  }
}

void Favoritos::actualizarPaginasBorradas(archivo pagina) {
  paginasEliminadas.push(pagina);
  if (paginasEliminadas.size() == 6) {
    paginasEliminadas.pop();
  }
}

void Favoritos::restaurarPagina(string ruta) {
  queue<archivo> copiaPaginasEliminadas;
  archivo pagina = getArchivoDeRuta(ruta);

  for (int i = 0; !paginasEliminadas.empty(); i++) {
    archivo pagina = paginasEliminadas.front();
    paginasEliminadas.pop();
    if (pagina.ruta == ruta) {
      archivos.push_back(pagina);
    } else if (pagina.ruta != ruta) {
      copiaPaginasEliminadas.push(pagina);
    }
  }
  copiarQueue(copiaPaginasEliminadas);
}

archivo Favoritos::getArchivoDeRuta(
    string ruta) { // Retorna archivo a partir de una ruta
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

//-----------------------------------------------------------------------------INTERFAZ
void Favoritos::printContenidoEnCarpeta(string ruta) {
  vector<string> rutaSegmentada = split(ruta, '/');

  string nombreCarpeta = rutaSegmentada[rutaSegmentada.size() - 1];
  for (list<archivo>::iterator archivo = archivos.begin();
       archivo != archivos.end(); archivo++) {

    if ((esDescendiente(nombreCarpeta, archivo->ruta)) &&
        (archivo->ruta != ruta))

      printArchivo(getArchivoDeIterador(archivo));
  }
}

void Favoritos::printCarpetas() {
  int conteo = 1;
  for (list<archivo>::iterator iteradorArchivo = archivos.begin();
       iteradorArchivo != archivos.end(); iteradorArchivo++) {
    archivo elementoArchivo = getArchivoDeIterador(iteradorArchivo);

    if (esCarpeta(elementoArchivo)) {
      printArchivoNumerado(elementoArchivo, conteo);
      conteo++;
    }
  }
};

void Favoritos::printPaginas() {
  int conteo = 1;

  for (list<archivo>::iterator iteradorArchivo = archivos.begin();
       iteradorArchivo != archivos.end(); iteradorArchivo++) {

    archivo elementoArchivo = getArchivoDeIterador(iteradorArchivo);

    if (esPagina(elementoArchivo)) {
      printArchivoNumerado(elementoArchivo, conteo);
      conteo++;
    }
  }
};

void Favoritos::printArchivo(archivo a) {
  if (esCarpeta(a))
    cout << " + " << a.ruta << endl;
  else
    cout << a.ruta << endl;
}
void Favoritos::printArchivoNumerado(archivo a, int numero) {
  if (esCarpeta(a))
    cout << numero << ". + " << a.ruta << endl;
  else
    cout << numero << ". " << a.ruta << endl;
}

//_---------------------------------------------------------------------------------

void Favoritos::eliminarContenidoEnCarpeta(string ruta) {
  vector<string> rutaSegmentada = split(ruta, '/');
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
