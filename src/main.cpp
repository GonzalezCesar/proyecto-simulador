#include "datos/headers/manejadorFicheros.hpp"
#include "dominio/headers/favoritos.hpp"
#include "dominio/headers/navegador.hpp"
#include "estructuras/archivo.hpp" //Remover
#include "presentacion/headers/interfaz.hpp"
#include <iostream>
#include <list>

using std::list;
using std::queue;

int main() {
  Navegador navegador;
  Favoritos favoritos;
  Interfaz interfaz;

  list<archivo> archivos = cargarCSVArchivos("favoritos.csv");
  queue<archivo> paginasEliminadas = cargarPaginasEliminadas();

  favoritos.setArchivos(archivos);
  favoritos.setPaginasEliminadas(paginasEliminadas);

  interfaz.menu(&navegador, &favoritos);

  // archivo one{"one", "root/loco/chon/one", "PAGINA - https://www.one.com"};
  // archivo two{"two", "root/two", "PAGINA - https://www.two.com"};
  // archivo three{"three", "root/choni/three", "PAGINA -
  // https://www.three.com"}; archivo c1{"loco", "root/loco", "CARPETA"};
  // archivo c2{"chon", "root/loco/chon", "CARPETA"};
  // archivo c3{"choni", "root/choni", "CARPETA"};
  //
  // list<archivo> favoritos;
  //
  // favoritos.push_back(one);
  // favoritos.push_back(two);
  // favoritos.push_back(three);
  // favoritos.push_back(c1);
  // favoritos.push_back(c2);
  // favoritos.push_back(c3);
  //
  // string contenidoCSV = generarCSVArchivos(favoritos);
  // guardarEnFichero("testeando.csv", contenidoCSV);
  // list<archivo> c = cargarCSVArchivos("testeando.csv");
  // interfaz.printFavoritos(favoritos);
  // interfaz.printFavoritos(c);
}
