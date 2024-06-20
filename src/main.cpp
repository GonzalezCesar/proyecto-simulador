#include "datos/headers/manejadorFicheros.hpp"
#include "dominio/headers/favoritos.hpp"
#include "dominio/headers/navegador.hpp"
#include "presentacion/headers/interfaz.hpp"
#include <iostream>

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
