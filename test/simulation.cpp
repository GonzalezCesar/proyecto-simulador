#include "../src/include/historial.hpp"
#include "../src/include/item_historial.hpp"
#include "../src/include/navegador.hpp"
#include "../src/include/utilidades.hpp"
#include <ctime>
#include <iostream>
#include <list>
#include <vector>

#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define GREEN "\x1B[32m"

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;
using std::vector;

//---------- Llamar a cualquiera de las siguientes funciones al main para
// usarlas---------//.

void test_1(); // Prueba de visita páginas con fechas distintas.
void test_2(); // Prueba de de funcionamiento de navegador junto a historial.
void menu();   // Menu de comandos con las funcionalidades del navegador.

int main() { menu(); }

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
  navegador.irNuevaPagina("https://google.com");
  navegador.irNuevaPagina("https://youtube.com");
  navegador.irNuevaPagina("https://facebook.com");
  navegador.historial.printHistorial();
}

int getInput() {
  int opt;
  cout << "\n>>: ";
  cin >> opt;
  return opt;
}
string getText() {
  string text;
  cout << "\n>>: ";
  cin >> text;
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
  cout << "5.- Salir" << endl;
}

void printTitle(string title) {
  cout << " -------------- " << GREEN + title + RESET + " -------------- \n\n";
}

void pause() {
  cout << "\nPresione enter para continuar.";
  getchar();
}

void menu() {
  Navegador navegador;
  navegador.setHome();
  int opt = 0;
  while (opt != 5) {
    system("clear");
    printTitle(navegador.getPaginaActual());
    bool back = navegador.hayPaginaAnterior();
    bool next = navegador.hayPaginaSiguiente();
    printMenu(next, back);
    cout << endl;
    opt = getInput();

    switch (opt) {
    case 1: {
      system("clear");
      printTitle("PAGINA NUEVA");
      cout << "\nIngrese la URL.";
      string url = getText();
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
      system("clear");
      printTitle("HISTORIAL");
      if (!navegador.historial.estaVacio()) {
        navegador.historial.printHistorial();
      } else
        cout << "Vacío" << endl;
      cin.get();
      pause();
      break;
    }
  }
}
