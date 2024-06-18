#include "../../estructuras/archivo.hpp"
#include <iostream>
#include <list>
#include <vector>

using std::list;
using std::vector;

#ifndef MANEJADOR_HTML
#define MANEJADOR_HTML

class ManejadorHTML {
private:
  list<archivo> *archivos;

public:
  void setArchivos(list<archivo> &archivos);
  string getHTML();
  string generarListasHTML();
  string formatearCarpeta(archivo carpeta);
  string formatearPagina(archivo pagina);
  string crearComentario(string comentario);
  vector<archivo> getOrdenadoPorNivel();
  string getRutaDeComentario(string comentario);
  string removerIdentacion(string linea);
  void insertarEnRuta(string &html, string elemento, string ruta);
  string getNombreDeArchivo(string comentario);
};

void printHeader();
#endif // !DEBUG
