#include "headers/interfaz.hpp"
#include "../datos/headers/manejadorFicheros.hpp"
#include "../datos/headers/manejadorHTML.hpp"
#include "../dominio/headers/favoritos.hpp"
#include "../dominio/headers/navegador.hpp"
#include "../dominio/headers/utilidades.hpp"
#include "../estructuras/archivo.hpp"
#include "../estructuras/item_historial.hpp"
#include <iostream>
#include <list>
#include <queue>

#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define GREEN "\x1B[32m"

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::queue;
using std::string;

void Interfaz::pause() {
  cout << "\nPresione enter para continuar.";
  getchar();
}

//---------------------------------------------------------------- MENÚS
void Interfaz::menu(Navegador *navegador, Favoritos *favoritos) {
  navegador->setHome();
  int opt = 0;
  while (opt != 7) {
    system("clear");
    printTitle(navegador->getPaginaActual());
    bool back = navegador->hayPaginaAnterior();
    bool next = navegador->hayPaginaSiguiente();
    printMenu(next, back);
    cout << endl;
    opt = getInput(7);
    if (opt == 0) {
      inputIncorrecto();
    }
    system("clear");
    switch (opt) {
    case 1: {
      printTitle("PAGINA NUEVA");
      // cin.ignore();
      string url = getText("Ingrese la URL");
      navegador->irNuevaPagina(url);
      break;
    }
    case 2: {
      if (navegador->hayPaginaSiguiente())
        navegador->irSiguentePagina();
      break;
    }
    case 3: {
      if (navegador->hayPaginaAnterior())
        navegador->irPaginaAnterior();
      break;
    }
    case 4:
      printTitle("HISTORIAL");
      if (!navegador->historial.estaVacio()) {
        printHistorial(navegador->historial.getHistorial());
      } else
        cout << "Vacío" << endl;
      cin.get();
      pause();
      break;
    case 5: {
      printTitle("GUARDAR FAVORITO");
      cout << "--> " + navegador->getPaginaActual() << endl << endl;
      // cin.ignore();
      string nombrePagina = getText("Ingrese el nombre");
      favoritos->guardarPagina(nombrePagina, navegador->getPaginaActual());
      break;
    }
    case 6: {
      menuFavoritos(favoritos, navegador);
      break;
    }
    case 7:
      break;
    }
  }
}

void Interfaz::menuFavoritos(Favoritos *favoritos, Navegador *navegador) {
  int opt = 0;

  while (opt != 9) {
    system("clear");
    printTitle("DIRECTORIOS");
    printFavoritos(favoritos->getArchivos());
    cout << "--------------------------------" << endl;
    printMenuFavoritos(favoritos, favoritos->hayPaginas(),
                       favoritos->hayCarpetas(),
                       favoritos->hayPaginasEliminadas());
    cout << endl;
    opt = getInput(9);

    system("clear");
    switch (opt) {
    case 1: {
      if (favoritos->hayPaginas()) {
        if (navegacionAFavorito(favoritos, navegador))
          opt = 9;
      }
      break;
    }
    case 2: {
      if ((favoritos->hayPaginas()) && (favoritos->hayCarpetas())) {
        organizacionDePagina(favoritos);
      }
      break;
    }
    case 3: {
      creacionDeCarpeta(favoritos);
      break;
    }
    case 4: {
      if (favoritos->hayPaginas()) {
        eliminarPagina(favoritos);
      }
      break;
    }
    case 5: {
      if (favoritos->hayCarpetas()) {
        eliminarCarpeta(favoritos);
      }
      break;
    }
    case 6: {
      if (favoritos->hayPaginasEliminadas()) {
        restaurarPagina(favoritos);
      }
      break;
    }
    case 7: {
      paginasEliminadas(favoritos);
      break;
    }
    case 8: {
      generarHTML(favoritos);
      break;
    }
    case 9:
      break;
    }
  }
}

//-------------------------------------------------------- OPERACIONES FAVORITOS

void Interfaz::creacionDeCarpeta(Favoritos *favoritos) {
  printTitle("CREACIÓN DE CARPETA");
  cout << "Para crear subcarpetas:" << endl;
  cout << "--> ruta_de_carpeta/nombre_de_carpeta_nueva" << endl;
  printCarpetas(favoritos->getArchivos());
  // cin.ignore();

  favoritos->crearCarpeta(getText("Introduzca el nombre de la carpeta"));
}
void Interfaz::organizacionDePagina(Favoritos *favoritos) {
  printTitle("ORGANIZACIÓN DE PÁGINA");
  int elementos = printPaginas(favoritos->getArchivos());
  cout << endl;
  cout << "Seleccione la pagina a organizar." << endl;
  int indice = getInput(elementos);
  if (indice != 0) {
    string ruta = favoritos->getRutaPagina(indice);
    string nombre = favoritos->getArchivoDeRuta(ruta).nombre;
    int elementos2 = printCarpetas(favoritos->getArchivos());
    cout << endl;
    cout << "Seleccione la carpeta contenedora." << endl;
    int indice2 = getInput(elementos2);
    string ruta2 = favoritos->getRutaCarpeta(indice2);
    favoritos->modificarRutaPagina(nombre, ruta2);
  } else
    inputIncorrecto();
}

bool Interfaz::navegacionAFavorito(Favoritos *favoritos, Navegador *navegador) {
  printTitle("NAVEGAR A FAVORITO");
  int elementos = printPaginas(favoritos->getArchivos());
  cout << "Seleccione la pagina." << endl;
  // cin.ignore();
  int opcion = getInput(elementos);
  if (opcion != 0) {
    string ruta = favoritos->getRutaPagina(opcion);
    string url = favoritos->getPaginaURL(ruta);
    navegador->irNuevaPagina(url);
    return true;
  } else {
    inputIncorrecto();
    return false;
  }
}

void Interfaz::eliminarPagina(Favoritos *favoritos) {
  printTitle("ELIMINAR PAGINA");
  int elementos = printPaginas(favoritos->getArchivos());
  cout << "Seleccione la pagina a eliminar" << endl;
  int indice = getInput(elementos);
  if (indice != 0) {
    string ruta = favoritos->getRutaPagina(indice);
    favoritos->eliminarPagina(ruta, false);
  } else
    inputIncorrecto();
}

void Interfaz::eliminarCarpeta(Favoritos *favoritos) {
  printTitle("ELIMINAR CARPETA");
  int elementos = printCarpetas(favoritos->getArchivos());
  cout << "elementos: " << elementos << endl;
  int indice = getInput(elementos);
  cout << "indice: " << elementos << endl;
  if (indice != 0) {
    string ruta = favoritos->getRutaCarpeta(indice);
    cout << "\nLos siguientes elementos serán borrados: " << endl;
    printContenidoEnCarpeta(favoritos->getArchivos(), ruta);
    pause();
    favoritos->eliminarContenidoEnCarpeta(ruta);
  } else
    inputIncorrecto();
}

void Interfaz::restaurarPagina(Favoritos *favoritos) {
  printTitle("RESTAURAR PAGINA");
  int elementos = printPaginasEliminadas(favoritos->getPaginasEliminadas());
  cout << "----------------------------------" << endl;
  cout << "Seleccione la pagina a restaurar" << endl;
  int indice = getInput(elementos);
  if (indice != 0) {
    string ruta = favoritos->getRutaPaginaEliminada(indice);
    favoritos->restaurarPagina(ruta);
  } else
    inputIncorrecto();
}

void Interfaz::paginasEliminadas(Favoritos *favoritos) {
  printTitle("ULTIMAS PAGINAS ELIMINADAS");
  printPaginasEliminadas(favoritos->getPaginasEliminadas());
  // cin.get();
  pause();
}

void Interfaz::generarHTML(Favoritos *favoritos) {
  ManejadorHTML h;
  printTitle("GENERADO DE HTML");
  cout << "\nSe ha generado el archivo HTML de los siguientes elementos:\n\n";
  printFavoritos(favoritos->getArchivos());
  h.setArchivos(favoritos->getArchivos());
  h.unirHTML();
  string html = h.getHTML();
  guardarEnFichero("favoritos_navegador.html", html);
  // cin.get();
  pause();
}

//---------------------------------------------------------------------------
// PRINTS
void Interfaz::printMenu(bool next, bool back) {
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

void Interfaz::printTitle(string title) {
  cout << " -------------- " << GREEN + title + RESET + " -------------- \n\n";
}
void Interfaz::printMenuFavoritos(Favoritos *b, bool hayPaginas,
                                  bool hayCarpetas, bool hayPaginasEliminadas) {

  string color1 = RED;
  string color2 = RED;
  string color3 = RED;
  string color4 = RED;
  if (b->hayPaginas())
    color1 = "";
  if (b->hayCarpetas())
    color2 = "";
  if (b->hayPaginasEliminadas())
    color3 = "";
  if ((b->hayCarpetas()) && (b->hayPaginas()))
    color4 = "";

  cout << color1 << "1. Ir a pagina." << RESET << endl;
  cout << color4 << "2. Organizar pagina." << RESET << endl;
  cout << "3. Crear carpeta." << endl;
  cout << color1 << "4. Eliminar pagina." << RESET << endl;
  cout << color2 << "5. Eliminar carpeta." << RESET << endl;
  cout << color3 << "6. Restaurar favorito." << RESET << endl;
  cout << "7. Ver últimos favoritos eliminados." << endl;
  cout << "8. Generar HTML." << endl;
  cout << "9. Salir." << endl;
}

void Interfaz::printContenidoEnCarpeta(list<archivo> archivos, string ruta) {
  vector<string> rutaSegmentada = split(ruta, '/');

  string nombreCarpeta = rutaSegmentada[rutaSegmentada.size() - 1];
  for (list<archivo>::iterator archivo = archivos.begin();
       archivo != archivos.end(); archivo++) {

    if ((esDescendiente(nombreCarpeta, archivo->ruta)) &&
        (archivo->ruta != ruta))

      printArchivo(getArchivoDeIterador(archivo));
  }
}

int Interfaz::printCarpetas(list<archivo> archivos) {
  int conteo = 0;
  for (list<archivo>::iterator iteradorArchivo = archivos.begin();
       iteradorArchivo != archivos.end(); iteradorArchivo++) {
    archivo elementoArchivo = getArchivoDeIterador(iteradorArchivo);

    if (esCarpeta(elementoArchivo)) {
      printArchivoNumerado(elementoArchivo, conteo);
      conteo++;
    }
  }
  return conteo;
};

int Interfaz::printPaginas(list<archivo> archivos) {
  int conteo = 0;

  for (list<archivo>::iterator iteradorArchivo = archivos.begin();
       iteradorArchivo != archivos.end(); iteradorArchivo++) {

    archivo elementoArchivo = getArchivoDeIterador(iteradorArchivo);

    if (esPagina(elementoArchivo)) {
      printArchivoNumerado(elementoArchivo, conteo + 1);
      conteo++;
    }
  }
  return conteo;
};

void Interfaz::printArchivo(archivo a) {
  if (esCarpeta(a))
    cout << " + " << a.ruta << endl;
  else
    cout << a.ruta << endl;
}
void Interfaz::printArchivoNumerado(archivo a, int numero) {
  if (esCarpeta(a))
    cout << numero << ". + " << a.ruta << endl;
  else
    cout << numero << ". " << a.ruta << endl;
}

int Interfaz::printPaginasEliminadas(queue<archivo> paginasEliminadas) {
  int i = 1;
  if (paginasEliminadas.empty())
    return 0;
  queue<archivo> copiaPaginasEliminadas = paginasEliminadas;
  for (i = 0; i < paginasEliminadas.size(); i++) {
    cout << i + 1 << ". " << copiaPaginasEliminadas.front().nombre << endl;
    copiaPaginasEliminadas.pop();
  }
  return i;
}

void Interfaz::printFavoritos(list<archivo> archivos) {
  for (auto archivo : archivos) {
    printArchivo(archivo);
  }
}

void Interfaz::printHistorial(list<ItemHistorial> paginas_registradas) {
  list<ItemHistorial>::iterator pagina;
  vector<string> fechaActual = paginas_registradas.begin()->fecha;
  string cabecera = getCabeceraFecha(fechaActual);
  cout << cabecera << endl;

  for (auto const &pagina : paginas_registradas) {
    if (fechasIguales(fechaActual, pagina.fecha))
      cout << getItemFormateado(pagina) << endl;
    else {
      string cabecera = getCabeceraFecha(pagina.fecha);
      fechaActual = pagina.fecha;
      cout << cabecera << endl;
      cout << getItemFormateado(pagina) << endl;
    }
  }
}

string Interfaz::getItemFormateado(ItemHistorial pagina) {
  return pagina.fecha[horaYMinutos] + " - " + pagina.url;
}

//--------------------------------------------------------------------------VALIDACIONES
void Interfaz::inputIncorrecto() {
  printf(RED "\nOpcion invalida.\n" RESET);
  pause();
}

string Interfaz::getText(string mensaje) {
  string text;
  cout << "\n" + mensaje << GREEN << " >>: " << RESET;
  getline(cin, text);
  return text;
}

int Interfaz::getInput(int range) { // Entrada de datos numérica
  string input;
  cout << GREEN << ">>: " << RESET;
  getline(std::cin, input);
  if (!validarInput(input))
    return 0;

  int inputOpcion = stoi(input);

  if ((inputOpcion) > 0 && (inputOpcion <= range)) {
    return stoi(input);
  }

  else
    return 0;
}

bool Interfaz::validarInput(string input) { // Valida entra de datos numéricas
  if (input == "")
    return false;        // verdadero: solo hay números en el string dado
  for (auto i : input) { // falso:hay otros caracteres
    if (isalpha(i))
      return false;
  }
  return true;
}
