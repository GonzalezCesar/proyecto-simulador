#include "pagina_archivo.hpp"
#include <iostream>
#include <list>
using std::list;
using std::string;

#ifndef CARPETA
#define CARPETA

struct Carpeta {
  string nombre;
  string ruta;
};

// class Carpeta {
// private:
//   string nombre;
//   list<paginaArchivo> paginas;//Remover
//   list<Carpeta> subCarpetas; // Remover
//   string ruta;
//   bool tieneSubcarpeta;
//   string carpetaPadre; // Remover
//
// public:
//   Carpeta(string name, string route);
//   Carpeta(string name); // Posiblemente innecesario
//
//   void setRuta(string route);
//   void setNombre(string name);
//
//   string getNombre();
//   list<paginaArchivo> getPaginas();
//   list<Carpeta> getSubcarpetas(); // Remover luego
//   string getRuta();
//   int getNivel();
//
//   void crearCarpeta(string name); // Remover
//   bool tieneCarpetaPadre();       // Remover
//   paginaArchivo borrarPagina(string nombre);
//   void guardarPagina(string url, string nombre);
//   void printPaginas();  // Remover
//   void printCarpetas(); // Remover
//   void printContenido();
// };

#endif
