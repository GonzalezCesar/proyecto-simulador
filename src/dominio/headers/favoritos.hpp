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
  archivo getArchivoDeRuta(string ruta);
  void copiarQueue(queue<archivo> copia);

public:
  Favoritos();
  void guardarPagina(string nombre, string url);
  void crearCarpeta(string nombre);
  void modificarRutaPagina(string pagina, string rutaCarpeta);
  void restaurarPagina(string ruta);
  list<archivo> *getArchivos();

  void eliminarPagina(string ruta, bool eliminadoPermanente);
  void eliminarArchivo(string ruta);
  void eliminarContenidoEnCarpeta(string ruta);

  // Mudar luego ---------------------
  void printFavoritos();
  void printArchivo(archivo a);
  void printCarpetas();
  void printPaginas();
  void printContenidoEnCarpeta(string ruta);
  void printPaginasEliminadas();
  // ---------------------------------
  bool existeCarpeta(string ruta);
  archivo getCarpeta(string ruta);
};
#endif // !FAVORITOS FAVORITOS
