#include "headers/manejadorFicheros.hpp"
#include <fstream>

using std::ofstream;

void guardarEnFichero(string nombreFichero, string contenido) {
  ofstream fichero(nombreFichero);
  fichero << contenido;
  fichero.close();
}
