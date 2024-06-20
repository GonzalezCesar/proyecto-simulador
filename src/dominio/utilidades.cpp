#include "headers/utilidades.hpp"
#include <algorithm>
#include <ctime>
#include <iostream>

using std::cout;

string getTiempo() {
  time_t now = time(0);
  std::tm *ptm = std::localtime(&now);
  char buffer[45];
  std::strftime(buffer, sizeof(buffer), "%A %B %d %Y %H:%M", ptm);
  return buffer;
}

// Retorna un vector de strings, cada string es un
// fragmento resultante de separar el string original a
// partir de un caracter especificado

vector<string> split(string texto, char caracter) { 
  vector<string> resultado;
  string palabra = "";

  for (auto i : texto) {
    if (i != caracter)
      palabra += i;

    else if (i == caracter) {
      resultado.push_back(palabra);
      palabra = "";
    }
  }

  resultado.push_back(palabra);
  return resultado;
}

bool fechasIguales(vector<string> fecha1, vector<string> fecha2) {

  if ((fecha1[dia] == fecha2[dia]) && (fecha1[mes] == fecha2[mes]) &&
      (fecha1[year] == fecha2[year])) {
    return true;
  }
  return false;
}

string getCabeceraFecha(vector<string> f) {
  return f[diaDeSemana] + " " + f[mes] + " " + f[dia] + ", " + f[year];
}


// Profundidad a la que se encuentra una carpeta, ejemplo:
// una subcarpeta a/b/c tiene nivel 2.

int getNivel(string fuente, char caracter) {
  int nivel = 0;
  for (auto i : fuente) {
    if (i == caracter)
      nivel++;
  }
  return nivel;
}

 // Imprime en pantalla con identación de acuerdo
// al nivel del archivo

void printNivelado(string texto,int nivel) {
  for (int i = 0; i < nivel; i++)
    cout << "    ";
  cout << texto;
}
string getNivelado(int nivel) {
  string nivelado;
  for (int i = 0; i < nivel + 1; i++)
    nivelado += "    ";
  return nivelado;
}

// Busca un substring a partir del string proporcionado
// verdadero: contiene el substring.
// falso: no lo contiene.

bool contieneSubsString(string fuente, string substring,char caracter) { 
  vector<string> vectorFuente = split(fuente, caracter);
  for (int i = 0; i < vectorFuente.size(); i++) {
    if (vectorFuente[i] == substring)
      return true;
  }
  return false;
}


// Retorna un vector de strings, resultante de dividir el
// string original al encontrar el caracter de salto \n

vector<string> getLineas(string fuente) { 
  string linea;
  vector<string> lineas;

  for (const char caracter : fuente) {
    linea += caracter;
    if (caracter == '\n') {
      lineas.push_back(linea);
      linea = "";
    }
  }
  return lineas;
}


// Convierte un vector a string

string vectorAString(vector<string> v) { 
  string resultado;
  for (int i = 0; i < v.size(); i++) {
    resultado += i;
    if (i != v.size() - 1)
      resultado += " ";
  }
  return resultado;
}


// Une un vector de strings

string unirLineas(vector<string> lineas) { 
  string resultado;
  for (int i = 0; i < lineas.size(); i++) {
    resultado += lineas[i];
  }
  return resultado;
}
// Retorna un struct archivo a partir de
// un iterador de lista archivo

archivo getArchivoDeIterador(list<archivo>::iterator iterador) { 
                                       
  archivo a{iterador->nombre, iterador->ruta, iterador->tipo};
  return a;
}
// Retorna un vector con los elementos
// de una lista de archivos

vector<archivo> getVector(list<archivo> listaArchivos) { 

  vector<archivo> vectorArchivos;
  for (auto i : listaArchivos) {
    vectorArchivos.push_back(i);
  }
  return vectorArchivos;
}

// Retorna un vector con los niveles únicos de la
// lista proporcionada, es decir sin duplicados

vector<int> getNivelesUnicos(
    list<archivo> archivos) {                               
  vector<archivo> vectorArchivos = getVector(archivos);
  vector<int> niveles = getNiveles(vectorArchivos);
  niveles = eliminarDuplicados(niveles);
  return niveles;
}

vector<int> getNiveles(vector<archivo> vectorArchivos) {
  vector<int> niveles;
  for (int i = 0; i < vectorArchivos.size(); i++) {
    int nivel = getNivel(vectorArchivos[i].ruta, '/');
    niveles.push_back(nivel);
  }
  return niveles;
}

// Elimina elementos duplicados de un
// vector (números solamente)

vector<int> eliminarDuplicados(vector<int> niveles) { 
  std::sort(niveles.begin(), niveles.end());
  vector<int>::iterator iteradorNiveles =
      std::unique(niveles.begin(), niveles.end());
  niveles.erase(iteradorNiveles, niveles.end());
  return niveles;
}

// Verifica si un archivo desciende de
// una carpeta especificada,
// verdadero: es es descendiente
// falso: no lo es

bool esDescendiente(string nombreCarpetaPadre,
                    string rutaArchivo) { 
  vector<string> rutaSegmentada = split(rutaArchivo, '/');
  for (int i = rutaSegmentada.size() - 1; i > -1; i--) {
    if (rutaSegmentada[i] == nombreCarpetaPadre) {
      return true;
    }
  }
  return false;
}
bool esCarpeta(archivo b) {
  if (b.tipo == "CARPETA")
    return true;
  return false;
}

bool esPagina(archivo a) {
  vector<string> rutaSegmentada = split(a.tipo, '-');
  if (rutaSegmentada[0] == "PAGINA")
    return true;
  return false;
}
