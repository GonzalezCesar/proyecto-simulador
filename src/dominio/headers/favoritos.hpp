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
  void restaurarPagina();
  bool existeCarpeta(string ruta);

  list<archivo> getArchivos();
  queue<archivo> getPaginasEliminadas();
  string getCarpetaPadre(string ruta);
  archivo getArchivoDeRuta(string ruta);
  archivo getCarpeta(string ruta);
  string getPaginaURL(string paginaRuta);
  string getRutaCarpeta(int indice);
  string getRutaPagina(int indice);
  bool hayPaginas();
  bool hayCarpetas();
  bool existePagina(string nombre);
  bool hayPaginasEliminadas();

  void eliminarPagina(string ruta, bool eliminadoPermanente);
  void eliminarArchivo(string ruta);
  void eliminarContenidoEnCarpeta(string ruta);
  string getRutaPaginaEliminada(int indice);
};
#endif // !FAVORITOS FAVORITOS
