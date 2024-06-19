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
}
