#include "item_historial.hpp"
#include <iostream>
#include <vector>

using std::vector;

#ifndef UTILIDADES
#define UTILIDADES

enum tiempo { diaDeSemana = 0, mes = 1, dia = 2, year = 3, horaYMinutos = 4 };

string getTiempo();
vector<string> split(string texto, char caracter);
bool fechasIguales(vector<string> fecha1, vector<string> fecha2);
;
string getCabeceraFecha(vector<string> f);
#endif
