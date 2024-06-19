#include "../../datos/headers/manejadorHTML.hpp"
#include "../../dominio/headers/favoritos.hpp"
#include "../../dominio/headers/navegador.hpp"
#include "../../estructuras/archivo.hpp"
#include "../../estructuras/item_historial.hpp"
#include <iostream>
#include <list>
#include <queue>
using std::list;
using std::queue;
using std::string;

#ifndef INTERFAZ
#define INTERFAZ

class Interfaz {
private:
public:
  int getInput(int range);
  bool validarInput(string input);
  string getText(string mensaje);
  void printMenu(bool next, bool back);
  void menu(Navegador *navegador, Favoritos *favoritos);
  void menuFavoritos(Favoritos *favoritos, Navegador *navegador);
  void printTitle(string title);
  void printMenuFavoritos(Favoritos *b, bool hayPaginas, bool hayCarpetas,
                          bool hayPaginasEliminadas);
  void pause();

  void printArchivoNumerado(archivo a, int numero);
  void printFavoritos(list<archivo> archivos);
  void printArchivo(archivo a);
  int printCarpetas(list<archivo> archivos);
  int printPaginas(list<archivo> archivos);
  void printContenidoEnCarpeta(list<archivo> archivos, string ruta);
  int printPaginasEliminadas(queue<archivo> paginasEliminadas);
  void printHistorial(list<ItemHistorial> historial);
  string getItemFormateado(ItemHistorial pagina);
  void inputIncorrecto();

  // SUBMENÚS FAVORITOS
  void creacionDeCarpeta(Favoritos *favoritos);
  void organizacionDePagina(Favoritos *favoritos);
  bool navegacionAFavorito(Favoritos *favoritos, Navegador *navegador);
  void eliminarPagina(Favoritos *favoritos);
  void eliminarCarpeta(Favoritos *favoritos);
  void restaurarPagina(Favoritos *favoritos);
  void paginasEliminadas(Favoritos *favoritos);
  void generarHTML(Favoritos *favoritos);
};
#endif
