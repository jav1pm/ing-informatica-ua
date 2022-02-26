# Historial de versiones
# 2.0 (17/03/2020): corregido un error que hacía que la práctica no se recompilara para algunos ficheros de prueba
#

#Si tus ficheros de prueba no comienzan por "tad", cambia "tad*.cpp" por el prefijo de tus ficheros, por ejemplo "prueba*.cpp":
for FILE in *tavlcalendarioC/tad*.cpp ; do
	#valgrind --tool=memcheck --leak-check=full ./tad
	echo "Evaluando $FILE"
	#Si tu Makefile espera que el fichero que contiene el programa principal se llame tad.cpp, cambia la siguiente línea por: cp $FILE src/tad.cpp
	cp $FILE src/tad.cpp 
        rm -f ./tad
	make
	./tad > $FILE.out
	diff -b -B -i $FILE.out $FILE.sal
	if [ "$?" == "0" ]; then
		echo "OK"
	else
		echo "ERROR"
	fi
done