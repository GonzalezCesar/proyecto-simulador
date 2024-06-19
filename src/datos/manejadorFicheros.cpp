#include "headers/manejadorFicheros.hpp"
#include "../dominio/headers/utilidades.hpp"
#include "../estructuras/archivo.hpp"
#include "../estructuras/item_historial.hpp"
#include "../presentacion/headers/interfaz.hpp"
#include "headers/manejadorFicheros.hpp"
#include <fstream>
#include <list>
#include <queue>

using std::getline;
using std::ifstream;
using std::list;
using std::ofstream;
using std::queue;

void guardarEnFichero(string nombreFichero, string contenido) {
  ofstream fichero(nombreFichero);
  fichero << contenido;
  fichero.close();
}

string archivoACSV(archivo a) { return a.ruta + "," + a.nombre + "," + a.tipo; }

string generarCSVArchivos(list<archivo> paginasEliminadas) {
  string csv;
  for (auto pagina : paginasEliminadas) {
    csv += archivoACSV(pagina) + "\n";
  }
  return csv;
}

string generarCSVArchivos(queue<archivo> paginasEliminadas) {
  string csv;
  while (!paginasEliminadas.empty()) {
    csv += archivoACSV(paginasEliminadas.front()) + "\n";
    paginasEliminadas.pop();
  }
  return csv;
}

void guardarFavoritos(list<archivo> paginas) {}

string getLineaFichero();

list<archivo> cargarCSVArchivos(string nombreFichero) {
  list<archivo> archivos;
  string linea;
  ifstream fichero(nombreFichero);
  while (getline(fichero, linea)) {
    archivo elemento = deCSVAArchivo(linea);
    archivos.push_back(elemento);
  }
  fichero.close();
  return archivos;
}

queue<archivo> cargarPaginasEliminadas() {
  queue<archivo> archivos;
  string linea;
  ifstream fichero("favoritos_eliminados_temp.csv");
  while (getline(fichero, linea)) {
    archivo elemento = deCSVAArchivo(linea);
    archivos.push(elemento);
  }
  return archivos;
}

archivo deCSVAArchivo(string lineaCSV) {
  vector<string> lineaSegmentada = split(lineaCSV, ',');
  archivo a{lineaSegmentada[1], lineaSegmentada[0], lineaSegmentada[2]};
  return a;
}

// list<archivo> cargarArchivosCSV(string archvo) {}

// list<ItemHistorial>
// list<archivo>
// queue<archivo>
