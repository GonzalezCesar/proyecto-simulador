run: #Compila y ejecuta el programa, al culminar ejecución borra el ejecutable
	@g++ ../src/main.cpp ../src/dominio/historial.cpp ../src/dominio/navegador.cpp ../src/dominio/utilidades.cpp ../src/dominio/favoritos.cpp ../src/datos/manejadorHTML.cpp ../src/datos/manejadorFicheros.cpp ../src/presentacion/interfaz.cpp -o navegador
	@./navegador
	@rm navegador.exe

nav: #Compila el programa
	@g++ ../src/main.cpp ../src/dominio/historial.cpp ../src/dominio/navegador.cpp ../src/dominio/utilidades.cpp ../src/dominio/favoritos.cpp ../src/datos/manejadorHTML.cpp ../src/datos/manejadorFicheros.cpp ../src/presentacion/interfaz.cpp -o navegador

navc: #Alternativa al anterior
	@g++ -std=c++11 ../src/main.cpp ../src/dominio/historial.cpp ../src/dominio/navegador.cpp ../src/dominio/utilidades.cpp ../src/dominio/favoritos.cpp ../src/datos/manejadorHTML.cpp ../src/datos/manejadorFicheros.cpp ../src/presentacion/interfaz.cpp -o navegador



