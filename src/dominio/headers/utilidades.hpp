#include "../../estructuras/archivo.hpp"
#include "../../estructuras/item_historial.hpp"
#include <iostream>
#include <list>
#include <queue>
#include <vector>

// Posiblemente eliminar este archivo y conservar solo el .cpp
using std::list;
using std::queue;
using std::vector;

#ifndef UTILIDADES
#define UTILIDADES

enum tiempo { diaDeSemana = 0, mes = 1, dia = 2, year = 3, horaYMinutos = 4 };

string getTiempo();
vector<string> split(string texto, char caracter);
bool fechasIguales(vector<string> fecha1, vector<string> fecha2);
;
string getCabeceraFecha(vector<string> f);
int getNivel(string fuente, char caracter);
string getNivelado(int nivel);
vector<string> getLineas(string fuente);
void printNivelado(string texto, int nivel);
bool contieneSubsString(string fuente, string substring, char caracter);
string unirLineas(vector<string> lineas);
string vectorAString(vector<string> v);
archivo getArchivoDeIterador(list<archivo>::iterator iterador);
vector<archivo> getVector(list<archivo> listaArchivos);
vector<int> getNiveles(vector<archivo> vectorArchivos);
vector<int> eliminarDuplicados(vector<int> niveles);
bool esDescendiente(string nombreCarpetaPadre, string rutaArchivo);
vector<int> getNivelesUnicos(list<archivo> archivos);
bool esCarpeta(archivo b);
bool esPagina(archivo a);

#endif
