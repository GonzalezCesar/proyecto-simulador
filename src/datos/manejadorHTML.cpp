#include "headers/manejadorHTML.hpp"
#include "../dominio/headers/utilidades.hpp"
#include <iostream>

using std::cout;
using std::endl;

string header = "<!DOCTYPE html>\n"
                "<html>\n<head>\n    <meta charset=\"UTF-8\">\n"
                "    <meta name= \"favoritos.html\" content= \"Favoritos\">\n"
                "    <title>Favoritos</title>\n</head>\n<body>\n"
                "    <h1>Favoritos</h1>\n";

string ManejadorHTML::getHTML() { return favoritosHTML; }

void ManejadorHTML::unirHTML() {
  string listas = generarListasHTML();
  string cierre = "\n</body>\n</html>";
  favoritosHTML = header + listas + cierre;
}

void ManejadorHTML::setArchivos(list<archivo> listaArchivos) {
  archivos = listaArchivos;
}

string ManejadorHTML::generarListasHTML() { // Restorna un strings con las
                                            // listas de favoritos en HTML
                                            // (únicamente las listas en HTML)
  vector<archivo> archivosOrdenados = getOrdenadoPorNivel();
  string file;
  for (auto iteradorArchivo : archivosOrdenados) {
    if (esCarpeta(iteradorArchivo)) {
      string elemento = formatearCarpeta(iteradorArchivo) + "\n";
      insertarEnRuta(file, elemento, iteradorArchivo.ruta);

    } else if (esPagina(iteradorArchivo)) {
      string elemento = formatearPagina(iteradorArchivo) + "\n";
      insertarEnRuta(file, elemento, iteradorArchivo.ruta);
    }
  }
  return file;
}

string ManejadorHTML::formatearCarpeta(
    archivo carpeta) { // Formatea un struct archivo a lista HTML, como es una
                       // carpeta contenrá otros elementos
  int nivel = getNivel(carpeta.ruta, '/');
  string identacion = getNivelado(nivel);
  string comentario = crearComentario(carpeta.ruta);
  string formatoCarpeta = identacion + "<li>" + carpeta.nombre + "\n" +
                          identacion + "<ul>\n" + comentario + "\n" +
                          identacion + "</li>\n" + identacion + "</ul>";
  return formatoCarpeta;
}

string ManejadorHTML::formatearPagina(
    archivo pagina) { // Formatea un struct archivo a HTML, es elemento de
                      // alguna carpeta
  int nivel = getNivel(pagina.ruta, '/');
  string identacion = getNivelado(nivel);
  string url = split(pagina.tipo, '-')[1];
  string formatoPagina = identacion + "<li>" + "<a href=" + url + ">" +
                         pagina.nombre + "</a></li>";
  return formatoPagina;
}

string ManejadorHTML::crearComentario(string comentario) {
  comentario = "<!-- " + comentario + " -->";
  return comentario;
}

vector<archivo>
ManejadorHTML::getOrdenadoPorNivel() { // Ordena las carpetas y páginas de menor
                                       // a mayor nivel
  vector<archivo> archivosOrdenados;
  list<archivo> listaArchivos = archivos;
  vector<int> niveles = getNivelesUnicos(listaArchivos);

  for (int i = 0; i < niveles.size(); i++) {
    for (auto iteradorArchivo : listaArchivos) {
      int nivel = getNivel(iteradorArchivo.ruta, '/');
      if ((nivel == niveles[i]) && (esCarpeta(iteradorArchivo))) {
        archivosOrdenados.push_back(iteradorArchivo);
      }
    }
  }
  for (int i = 0; i < niveles.size(); i++) {
    for (auto iteradorArchivo : listaArchivos) {
      int nivel = getNivel(iteradorArchivo.ruta, '/');
      if ((nivel == niveles[i]) && (esPagina(iteradorArchivo))) {
        archivosOrdenados.push_back(iteradorArchivo);
      }
    }
  }
  return archivosOrdenados;
}

string ManejadorHTML::removerIdentacion(string linea) {
  string result;
  bool check = false;
  for (int i = 0; i < linea.length(); i++) {

    if (check)
      result += linea[i];
    else if (linea[i] != ' ') {
      result += linea[i];
      check = true;
    }
  }
  return result;
}

void ManejadorHTML::insertarEnRuta(
    string &html, string elemento,
    string
        ruta) { // Inserta el elemento de favoritos en la línea que corresponde
  bool check = false;
  vector<string> lineasHTML = getLineas(html);
  if (lineasHTML.size() == 0) {
    html += elemento;
    return;
  }
  for (int i = 0; i < lineasHTML.size(); i++) {
    string linea = removerIdentacion(lineasHTML[i]);
    if (contieneSubsString(lineasHTML[i], "<!--", ' ')) {
      string nombreCarpeta = getNombreDeArchivo(lineasHTML[i]);
      if (esDescendiente(nombreCarpeta, ruta)) {
        lineasHTML.insert(lineasHTML.begin() + i, elemento);
        check = true;
        break;
      }
    }
  }

  if (!check)
    html += elemento;
  else {
    html = unirLineas(lineasHTML);
  }
}

string ManejadorHTML::getNombreDeArchivo(
    string comentario) { // Extrae el nombre de una carpeta apartir de un
                         // comentario HTML
  string rutaPrevia = getRutaDeComentario(comentario);
  vector<string> comentarioSegmentado = split(rutaPrevia, '/');
  int size = comentarioSegmentado.size();
  string nombre = comentarioSegmentado[size - 1];
  return nombre;
}

string ManejadorHTML::getRutaDeComentario(
    string comentario) { // Remueve la simbología del comentario en HTML y
                         // retorna el contenido
  string comentarioSinEspacios = removerIdentacion(comentario);
  vector<string> vectorComentario = split(comentarioSinEspacios, ' ');
  vectorComentario.pop_back();
  string ruta;

  for (int i = 1; i < vectorComentario.size(); i++) {
    ruta += vectorComentario[i];
    if (i != vectorComentario.size() - 1)
      ruta += " ";
  }
  return ruta;
}
