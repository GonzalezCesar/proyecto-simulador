#include "../include/utilidades.hpp"
#include <ctime>
#include <iostream>
#include <vector>

string getTiempo() {
  time_t now = time(0);
  std::tm *ptm = std::localtime(&now);
  char buffer[45];
  std::strftime(buffer, sizeof(buffer), "%A %B %d %Y %H:%M", ptm);
  return buffer;
}

vector<string> split(string texto, char caracter) {
  vector<string> resultado;
  string palabra = "";

  for (auto i : texto) {
    if (i != ' ')
      palabra += i;

    else if (i == ' ') {
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
