run: #Compila y ejecuta el programa, al culminar ejecución borra el ejecutable
	@g++ test.cpp ../src/dominio/historial.cpp ../src/dominio/navegador.cpp ../src/dominio/utilidades.cpp ../src/dominio/favoritos.cpp ../src/datos/manejadorHTML_.cpp ../src/datos/manejadorFicheros.cpp -o test
	@./test
	@rm test

nav: #Compila el programa
	@g++ test.cpp ../src/dominio/historial.cpp ../src/dominio/navegador.cpp ../src/dominio/utilidades.cpp ../src/dominio/favoritos.cpp ../src/datos/manejadorHTML_.cpp ../src/datos/manejadorFicheros.cpp -o test

navc: #Alternativa al anterior
	@g++ -std=c++11 test.cpp ../src/dominio/historial.cpp ../src/dominio/navegador.cpp ../src/dominio/utilidades.cpp ../src/dominio/favoritos.cpp ../src/datos/manejadorHTML_.cpp ../src/datos/manejadorFicheros.cpp -o test



