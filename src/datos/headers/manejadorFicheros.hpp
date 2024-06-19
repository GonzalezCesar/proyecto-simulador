#include "../../estructuras/archivo.hpp"
#include <iostream>
#include <list>
#include <queue>

using std::list;
using std::queue;
using std::string;

#ifndef MANEJADOR_FICHEROS
#define MANEJADOR_FICHEROS

void guardarEnFichero(string nombreFichero, string contenido);
string archivoACSV(archivo a);
archivo deCSVAArchivo(string lineaCSV);
string generarCSVArchivos(list<archivo> paginasEliminadas);
string generarCSVArchivos(queue<archivo> paginasEliminadas);
void guardarFavoritos(list<archivo> paginas);
list<archivo> cargarCSVArchivos(string nombreFichero);
queue<archivo> cargarPaginasEliminadas();

#endif // !MANEJADOR_FICHEROS
