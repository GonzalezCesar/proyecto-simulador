#include "../../estructuras/archivo.hpp"
#include <iostream>
#include <list>
#include <queue>
#include <vector>

using std::list;
using std::queue;
using std::string;
using std::vector;

#ifndef FAVORITOS
#define FAVORITOS

class Favoritos {
private:
  list<archivo> archivos;
  queue<archivo> paginasEliminadas;

  void actualizarPaginasBorradas(archivo pagina);
  void copiarQueue(queue<archivo> copia);

public:
  Favoritos();
  void guardarPagina(string nombre, string url);
  void crearCarpeta(string nombre);
  void modificarRutaPagina(string pagina, string rutaCarpeta);
  void restaurarPagina(string ruta);
  list<archivo> *getArchivos();
  archivo getArchivoDeRuta(string ruta);

  void eliminarPagina(string ruta, bool eliminadoPermanente);
  void eliminarArchivo(string ruta);
  void eliminarContenidoEnCarpeta(string ruta);
  string getRutaPaginaEliminada(int indice);
  // Mudar luego ---------------------
  void printArchivoNumerado(archivo a, int numero);
  void printFavoritos();
  void printArchivo(archivo a);
  void printCarpetas();
  void printPaginas();
  void printContenidoEnCarpeta(string ruta);
  void printPaginasEliminadas();
  // ---------------------------------
  bool existeCarpeta(string ruta);
  archivo getCarpeta(string ruta);
  string getPaginaURL(string paginaRuta);
  string getRutaCarpeta(int indice);
  string getRutaPagina(int indice);
};
#endif // !FAVORITOS FAVORITOS
