#include "dominio/headers/favoritos.hpp"
#include "dominio/headers/navegador.hpp"
#include "presentacion/headers/interfaz.hpp"
#include <iostream>

int main() {
  Navegador navegador;
  Favoritos favoritos;
  Interfaz interfaz;

  interfaz.menu(&navegador, &favoritos);
}
