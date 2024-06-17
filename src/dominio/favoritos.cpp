#include "headers/favoritos.hpp"
#include "../estructuras/archivo.hpp"
#include "headers/utilidades.hpp"
#include <algorithm>
#include <codecvt>
#include <iostream>

using std::cout;
using std::endl;
using std::list;
using std::queue;
using std::string;
using std::vector;

Favoritos::Favoritos() {}

void Favoritos::crearCarpeta(string ruta) {
  archivo nuevaCarpeta;
  vector<string> rutaSegmentada = split(ruta, '/');
  nuevaCarpeta.tipo = "CARPETA";
  nuevaCarpeta.nombre = rutaSegmentada[rutaSegmentada.size() - 1];
  nuevaCarpeta.ruta = ruta;
  archivos.push_front(nuevaCarpeta);
}

list<archivo> *Favoritos::getArchivos() { return &archivos; }

void Favoritos::guardarPagina(string nombre, string url) {
  archivo nuevaPagina;
  nuevaPagina.tipo = "PAGINA-" + url;
  nuevaPagina.nombre = nombre;
  nuevaPagina.ruta = nombre;
  archivos.push_back(nuevaPagina);
}

void Favoritos::printFavoritos() {
  for (auto archivo : archivos) {
    printArchivo(archivo);
  }
}

void Favoritos::modificarRutaPagina(string pagina, string rutaCarpeta) {

  for (auto iterador = archivos.begin(); iterador != archivos.end();
       ++iterador) {
    if (iterador->nombre == pagina) {
      iterador->ruta = rutaCarpeta + "/" + iterador->nombre;
      break;
    }
  }
}

bool Favoritos::existeCarpeta(string ruta) {
  for (auto archivo : archivos) {
    if (archivo.tipo == "CARPETA")
      return true;
  }
  return false;
}

void Favoritos::eliminarPagina(string ruta, bool eliminadoPermanente) {

  list<archivo>::iterator iteradorPagina = archivos.begin();
  while (iteradorPagina != archivos.end()) {
    if (iteradorPagina->ruta == ruta) {
      archivo pagina = getArchivoDeIterador(iteradorPagina);
      if (!eliminadoPermanente)
        actualizarPaginasBorradas(pagina);
      iteradorPagina = archivos.erase(iteradorPagina);
      break;
    } else {
      ++iteradorPagina;
    }
  }
}

void Favoritos::copiarQueue(queue<archivo> copia) {
  int size = copia.size();
  for (int i = 0; !copia.empty(); i++) {
    paginasEliminadas.push(copia.front());
    copia.pop();
  }
}

void Favoritos::printPaginasEliminadas() {
  queue<archivo> copiaPaginasEliminadas = paginasEliminadas;

  for (int i = 0; i < paginasEliminadas.size(); i++) {
    cout << copiaPaginasEliminadas.front().nombre << endl;
    copiaPaginasEliminadas.pop();
  }
}

void Favoritos::actualizarPaginasBorradas(archivo pagina) {
  paginasEliminadas.push(pagina);
  if (paginasEliminadas.size() == 5) {
    paginasEliminadas.pop();
  }
}

void Favoritos::restaurarPagina(string ruta) {
  queue<archivo> copiaPaginasEliminadas;
  archivo pagina = getArchivoDeRuta(ruta);

  for (int i = 0; !paginasEliminadas.empty(); i++) {
    archivo pagina = paginasEliminadas.front();
    paginasEliminadas.pop();
    if (pagina.ruta == ruta) {
      archivos.push_back(pagina);
    } else if (pagina.ruta != ruta) {
      copiaPaginasEliminadas.push(pagina);
    }
  }
  copiarQueue(copiaPaginasEliminadas);
}

archivo Favoritos::getArchivoDeRuta(string ruta) {
  archivo a;
  for (auto archivo : archivos) {
    if (archivo.ruta == ruta) {
      a.nombre = archivo.nombre;
      a.ruta = archivo.ruta;
      a.tipo = archivo.tipo;
      break;
    }
  }
  return a;
}

//-----------------------------------------------------------------------------INTERFAZ
void Favoritos::printContenidoEnCarpeta(string ruta) {
  vector<string> rutaSegmentada = split(ruta, '/');

  string nombreCarpeta = rutaSegmentada[rutaSegmentada.size() - 1];
  for (list<archivo>::iterator archivo = archivos.begin();
       archivo != archivos.end(); archivo++) {

    if ((esDescendiente(nombreCarpeta, archivo->ruta)) &&
        (archivo->ruta != ruta))
      printArchivo(getArchivoDeIterador(archivo));
  }
}

void Favoritos::printCarpetas() {
  for (list<archivo>::iterator iteradorArchivo = archivos.begin();
       iteradorArchivo != archivos.end(); iteradorArchivo++) {
    archivo elementoArchivo = getArchivoDeIterador(iteradorArchivo);
    if (esCarpeta(elementoArchivo))
      printArchivo(elementoArchivo);
  }
};

void Favoritos::printPaginas() {
  for (list<archivo>::iterator iteradorArchivo = archivos.begin();
       iteradorArchivo != archivos.end(); iteradorArchivo++) {
    archivo elementoArchivo = getArchivoDeIterador(iteradorArchivo);
    if (esPagina(elementoArchivo))
      printArchivo(elementoArchivo);
  }
};

void Favoritos::printArchivo(archivo a) {
  if (esCarpeta(a))
    cout << " + " << a.ruta << endl;
  else
    cout << a.ruta << endl;
}

//_---------------------------------------------------------------------------------

void Favoritos::eliminarContenidoEnCarpeta(string ruta) {
  vector<string> rutaSegmentada = split(ruta, '/');
  string nombreCarpeta = rutaSegmentada[rutaSegmentada.size() - 1];

  auto iteradorArchivo = archivos.begin();
  while (iteradorArchivo != archivos.end()) {
    // Check if descendant and remove safely
    if (esDescendiente(nombreCarpeta, iteradorArchivo->ruta)) {
      iteradorArchivo =
          archivos.erase(iteradorArchivo); // Advance iterator after erase
    } else {
      ++iteradorArchivo; // Move to the next element if not a descendant
    }
  }
}

void Favoritos::eliminarArchivo(string ruta) {
  list<archivo>::iterator iteradorArchivo = archivos.begin();
  while (iteradorArchivo != archivos.end()) {
    archivo a = getArchivoDeIterador(iteradorArchivo);
    if (iteradorArchivo->ruta == ruta) {
      iteradorArchivo = archivos.erase(iteradorArchivo);
      break;
    } else {
      ++iteradorArchivo;
    }
  }
}

// vector<archivo> Favoritos::getOrdenadoPorNivel() {
//   vector<archivo> archivosOrdenados;
//   vector<int> niveles = getNivelesUnicos(archivos);
//
//   for (int i = 0; i < niveles.size(); i++) {
//     for (auto iteradorArchivo : archivos) {
//       int nivel = getNivel(iteradorArchivo.ruta, '/');
//       if ((nivel == niveles[i]) && (esCarpeta(iteradorArchivo))) {
//         archivosOrdenados.push_back(iteradorArchivo);
//       }
//     }
//   }
//   for (int i = 0; i < niveles.size(); i++) {
//     for (auto iteradorArchivo : archivos) {
//       int nivel = getNivel(iteradorArchivo.ruta, '/');
//       if ((nivel == niveles[i]) && (esPagina(iteradorArchivo))) {
//         archivosOrdenados.push_back(iteradorArchivo);
//       }
//     }
//   }
//   return archivosOrdenados;
// }

// string Favoritos::crearComentario(string comentario) {
//   comentario = "<!-- " + comentario + " -->";
//   return comentario;
// }
//
// string Favoritos::generarListasHTML() {
//   vector<archivo> archivosOrdenados = getOrdenadoPorNivel();
//   string file;
//   for (auto iteradorArchivo : archivosOrdenados) {
//     if (esCarpeta(iteradorArchivo)) {
//       string elemento = formatearCarpeta(iteradorArchivo) + "\n";
//       insertarEnRuta(file, elemento, iteradorArchivo.ruta);
//
//     } else if (esPagina(iteradorArchivo)) {
//       string elemento = formatearPagina(iteradorArchivo) + "\n";
//       insertarEnRuta(file, elemento, iteradorArchivo.ruta);
//     }
//   }
//   return file;
// }
//
// string Favoritos::formatearCarpeta(archivo carpeta) {
//   int nivel = getNivel(carpeta.ruta, '/');
//   string identacion = getNivelado(nivel);
//   string comentario = crearComentario(carpeta.ruta);
//   string formatoCarpeta = identacion + "<ul>\n" + identacion + "<li>" +
//                           carpeta.nombre + "\n" + identacion + comentario +
//                           "\n" + identacion + "</>\n" + identacion +
//                           "<\\ul>";
//   return formatoCarpeta;
// }
//
// string Favoritos::formatearPagina(archivo pagina) {
//   int nivel = getNivel(pagina.ruta, '/');
//   string identacion = getNivelado(nivel);
//   string formatoPagina = identacion + "<li>" + pagina.nombre + "</>";
//   return formatoPagina;
// }
// string Favoritos::getRutaDeComentario(string comentario) {
//   string comentarioSinEspacios = removerIdentacion(comentario);
//   vector<string> vectorComentario = split(comentarioSinEspacios, ' ');
//   return vectorComentario[1];
// }
//
// string Favoritos::removerIdentacion(string linea) {
//   string result;
//   bool check = false;
//   for (int i = 0; i < linea.length(); i++) {
//
//     if (check)
//       result += linea[i];
//     else if (linea[i] != ' ') {
//       result += linea[i];
//       check = true;
//     }
//   }
//   return result;
// }
//
// void Favoritos::insertarEnRuta(string &html, string elemento, string ruta) {
//   bool check = false;
//   vector<string> lineasHTML = getLineas(html);
//   if (lineasHTML.size() == 0) {
//     html += elemento;
//     return;
//   }
//   for (int i = 0; i < lineasHTML.size(); i++) {
//     string linea = removerIdentacion(lineasHTML[i]);
//     if (contieneSubsString(lineasHTML[i], "<!--", ' ')) {
//       string nombreCarpeta = getNombreDeArchivo(lineasHTML[i]);
//       if (esDescendiente(nombreCarpeta, ruta)) {
//         lineasHTML.insert(lineasHTML.begin() + i, elemento);
//         check = true;
//         break;
//       }
//     }
//   }
//
//   if (!check)
//     html += elemento;
//   else {
//     html = unirLineas(lineasHTML);
//   }
// }
//
// int Favoritos::getLineaComentario(vector<string> lineas) {
//   for (int i = 0; i < lineas.size(); i++) {
//     if (contieneSubsString(lineas[i], "<!--", ' '))
//       return i;
//   }
//   return -1;
// }
//
// string Favoritos::getNombreDeArchivo(string comentario) {
//   string rutaPrevia = getRutaDeComentario(comentario);
//   vector<string> comentarioSegmentado = split(rutaPrevia, '/');
//   int size = comentarioSegmentado.size();
//   string nombre = comentarioSegmentado[size - 1];
//   return nombre;
// }
//
// string Favoritos::getHTML() {
//   string html;
//   string listas = generarListasHTML();
//   return html;
// }
