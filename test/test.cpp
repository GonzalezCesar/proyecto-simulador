#include "../src/datos/headers/manejadorFicheros.hpp"
#include "../src/datos/headers/manejadorHTML.hpp"
#include "../src/dominio/headers/favoritos.hpp"
#include "../src/dominio/headers/historial.hpp"
#include "../src/dominio/headers/navegador.hpp"
#include "../src/dominio/headers/utilidades.hpp"
#include <iostream>

#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define GREEN "\x1B[32m"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void menuFavoritos(Favoritos *favoritos, Navegador *n);
void test_1(); // Prueba de visita páginas con fechas distintas.
void test_2(); // Prueba de de funcionamiento de navegador junto a historial.
void test_3(); // Prueba de guardado en favoritos
void menu();   // Menu de comandos con las funcionalidades del navegador.

int main() { menu(); }

//-------------------------------------------------//
int getInput() {
  int opt;
  cout << "\n>>: ";
  cin >> opt;
  return opt;
}
string getText(string mensaje) {
  string text;
  cout << "\n" + mensaje << " >>: ";
  getline(cin, text);
  return text;
}

void printMenu(bool next, bool back) {

  auto color1 = RED;
  auto color2 = RED;

  if (next) {
    color1 = GREEN;
  }
  if (back) {
    color2 = GREEN;
  }
  cout << "1.- Nueva pagina" << endl;
  cout << color1 << "2.- Siguiente pagina" << RESET << endl;
  cout << color2 << "3.- Pagina anterior" << RESET << endl;
  cout << "4.- Ver historial." << endl;
  cout << "5.- Guardar en favoritos" << endl;
  cout << "6.- Menu favoritos" << endl;
  cout << "7.- Salir" << endl;
}

void printTitle(string title) {
  cout << " -------------- " << GREEN + title + RESET + " -------------- \n\n";
}

void pause() {
  cout << "\nPresione enter para continuar.";
  getchar();
}
//---------------------------------------------------------------MENU
void menu() {
  Navegador navegador;
  Favoritos favoritos;
  navegador.setHome();
  int opt = 0;
  while (opt != 7) {
    system("clear");
    printTitle(navegador.getPaginaActual());
    bool back = navegador.hayPaginaAnterior();
    bool next = navegador.hayPaginaSiguiente();
    printMenu(next, back);
    cout << endl;
    opt = getInput();

    system("clear");
    switch (opt) {
    case 1: {
      printTitle("PAGINA NUEVA");
      cin.ignore();
      string url = getText("Ingrese la URL");
      navegador.irNuevaPagina(url);
      break;
    }
    case 2: {
      if (navegador.hayPaginaSiguiente())
        navegador.irSiguentePagina();
      break;
    }
    case 3: {
      if (navegador.hayPaginaAnterior())
        navegador.irPaginaAnterior();
      break;
    }
    case 4:
      printTitle("HISTORIAL");
      if (!navegador.historial.estaVacio()) {
        navegador.historial.printHistorial();
      } else
        cout << "Vacío" << endl;
      cin.get();
      pause();
      break;
    case 5: {
      printTitle("GUARDAR FAVORITO");
      cout << "--> " + navegador.getPaginaActual() << endl << endl;
      cin.ignore();
      string nombrePagina = getText("Ingrese el nombre");
      favoritos.guardarPagina(nombrePagina, navegador.getPaginaActual());
      break;
    }
    case 6: {
      menuFavoritos(&favoritos, &navegador);
      break;
    }
    case 7:
      break;
    }
  }
}

void printMenuFavoritos() {

  cout << "1. Ir a pagina." << endl;
  cout << "2. Organizar pagina." << endl;
  cout << "3. Crear carpeta." << endl;
  cout << "4. Eliminar pagina." << endl;
  cout << "5. Eliminar carpeta." << endl;
  cout << "6. Restaurar favorito." << endl;
  cout << "7. Ver últimos favoritos eliminados." << endl;
  cout << "8. Ver HTML." << endl;
  cout << "9. Salir." << endl;
}
//-----------------------------------------------------------------MENU
//FAVORITOS
void menuFavoritos(Favoritos *b, Navegador *n) {
  ManejadorHTML h;
  int opt = 0;

  while (opt != 9) {
    system("clear");
    printTitle("DIRECTORIOS");
    b->printFavoritos();
    cout << "--------------------------------" << endl;
    printMenuFavoritos();
    cout << endl;
    opt = getInput();

    system("clear");
    switch (opt) {
    case 1: {
      printTitle("NAVEGAR A FAVORITO");
      b->printPaginas();
      cout << endl;
      cin.ignore();
      string ruta = getText("Ingrese la ruta de la pagina");
      string url = b->getPaginaURL(ruta);
      n->irNuevaPagina(url);
      opt = 9;
      break;
    }
    case 2: {
      printTitle("ORGANIZACIÓN DE PÁGINA");
      b->printPaginas();
      cout << endl;
      cout << "Seleccione la pagina a organizar." << endl;
      cin.ignore();
      int indice = getInput();
      string ruta = b->getRutaPagina(indice);
      string nombre = b->getArchivoDeRuta(ruta).nombre;
      b->printCarpetas();
      cout << endl;
      cout << "Seleccione la carpeta contenedora." << endl;
      int indice2 = getInput();
      string ruta2 = b->getRutaCarpeta(indice2);
      b->modificarRutaPagina(nombre, ruta2);
      break;
    }
    case 3: {
      printTitle("CREACIÓN DE CARPETA");

      cout << "Para crear subcarpetas:" << endl;
      cout << "--> ruta_de_carpeta/nombre_de_carpeta_nueva" << endl;

      b->printCarpetas();
      cin.ignore();
      b->crearCarpeta(getText("Introduzca el nombre de la carpeta"));
      break;
    }
    case 4: {
      printTitle("ELIMINAR PAGINA");
      b->printPaginas();
      cin.ignore();
      cout << "Seleccione la pagina a eliminar" << endl;
      int indice = getInput();
      string ruta = b->getRutaPagina(indice);
      b->eliminarPagina(ruta, false);
      break;
    }
    case 5: {
      printTitle("ELIMINAR CARPETA");
      b->printCarpetas();
      cin.ignore();
      int indice = getInput();
      string ruta = b->getRutaCarpeta(indice);
      cout << "\nLos siguientes elementos serán borrados: " << endl;
      b->printContenidoEnCarpeta(ruta);
      cin.get();
      pause();
      b->eliminarContenidoEnCarpeta(ruta);
      break;
    }
    case 6: {
      printTitle("RESTAURAR PAGINA");
      b->printPaginasEliminadas();
      cout << "----------------------------------" << endl;
      cin.ignore();
      cout << "Seleccione la pagina a restaurar" << endl;
      int indice = getInput();
      string ruta = b->getRutaPaginaEliminada(indice);
      b->restaurarPagina(ruta);
      break;
    }
    case 7: {
      printTitle("ULTIMAS PAGINAS ELIMINADAS");
      b->printPaginasEliminadas();
      cin.get();
      pause();
      break;
    }
    case 8: {
      printTitle("VISTA HTML");
      h.setArchivos(*b->getArchivos());
      string html = h.getHTML();
      cout << html << endl;
      guardarEnFichero("favoritos_navegador.html", html);
      cin.get();
      pause();
      break;
    }
    case 9:
      break;
    }
  }
}

void test_1() {

  Historial historial;

  vector<string> tiempo = split(getTiempo(), ' ');
  tiempo[mes] = "March";

  ItemHistorial a;
  a.url = "https://www.google.com";
  ItemHistorial b;
  b.url = "https://www.youtube.com";

  ItemHistorial c; // Todas con fecha de marzo-----------------
  c.url = "https://www.facebook.com";
  c.fecha = tiempo;
  ItemHistorial d;
  d.url = "https://www.x.com";
  d.fecha = tiempo;

  ItemHistorial e;
  e.url = "https://www.instagram.com";
  e.fecha = tiempo;
  ItemHistorial f;
  f.url = "https://www.youtube.com";
  f.fecha = tiempo;

  tiempo[mes] = "April"; // Todas con fecha de abril------------
  ItemHistorial g;
  g.url = "https://www.instagram.com";
  g.fecha = tiempo;
  ItemHistorial h;
  h.url = "https://www.youtube.com";
  h.fecha = tiempo;

  historial.agregarPagina("https://www.google.com");
  historial.agregarPagina("https://www.youtube.com");

  historial.addTesting(c);
  historial.addTesting(d);
  historial.addTesting(e);
  historial.addTesting(f);
  historial.addTesting(g);
  historial.addTesting(h);

  historial.printHistorial();
}

void test_2() {
  Navegador navegador;
  navegador.irNuevaPagina("https://www.google.com");
  navegador.irNuevaPagina("https://www.youtube.com");
  navegador.irNuevaPagina("https://www.facebook.com");
  navegador.historial.printHistorial();
}

void test_3() {
  Favoritos b;
  ManejadorHTML h;
  b.guardarPagina("a", "http://www.a.com");
  b.guardarPagina("b", "http://www.b.com");
  b.guardarPagina("c", "http://www.c.com");
  b.printFavoritos();
}