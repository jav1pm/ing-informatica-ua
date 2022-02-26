#!/bin/bash

DIRPRAC=.

MAXTIME=10 	   # Tiempo máximo de ejecución (en segundos) de una prueba
PRINCIPAL=./prac3	# Nombre del ejecutable de la práctica
ENT=$DIRPRAC/pruebas	   # Directorio con los ficheros de pruebas de entrada
SAL=$DIRPRAC/salida-correcta-esperada	   # Directorio con los ficheros de salidas correctas
OBT=salida-obtenida       # Directorio con los ficheros obtenidos tras la ejecución de la práctica
VAL="valgrind -q"  # Si valgrind no está instalado, quitar "valgrind -q" de esta linea (quedaría VAL=""). Ojo: La práctica debe probarse siempre con valgrind antes de la entrega.
npruebasa=25	   # Número de pruebas a ejecutar del autocorrector


mata=./mata
comparefiles=./comparefiles
meikfail=../makefile-autocorrector


# -------------- generar y compilar los ficheros auxiliares mata.c y comparefiles.cc -----
function genMata() {

if ! test -x mata ; then  # si ya existe no se genera
echo "#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

const int TAMMAXFICH=300000;
int f;int segundos,st;
int segejec=0;
char *nfsal=NULL;
void SeAcabo(int i){
  fprintf(stderr,\"ERROR, tiempo de ejecución agotado... (%d segundos)\\n\",segundos);
  fflush(stderr);
  kill(f,SIGKILL);
  exit(-1);
}
void SeAcaboFich(int i){
  fprintf(stderr,\"ERROR, fichero de salida muy grande (cuelgue?)... \\n\");
  fflush(stderr);
  kill(f,SIGKILL);
  exit(-1);
}
int FicheroGrande() {
  struct stat s;  int ret=0;
  if (nfsal != NULL) {
    stat(nfsal,&s);
    if (s.st_size > TAMMAXFICH) ret = 1;
  }
  return ret;
}
void Control(int i){
  segejec++;
  if (segejec >= segundos) SeAcabo(i);
  else if (FicheroGrande()) SeAcaboFich(i);
  else alarm(1);
}
void Salir(int i){exit(1);}
int main(int argc,char *argv[]){
  if (argc < 4) exit(1);
  segundos = atoi(argv[1]);
  nfsal = argv[2];
  signal(SIGALRM,Control);
  signal(SIGCHLD,Salir);
  alarm(1);
  if ((f = fork()) == 0) execvp(argv[3],&argv[3]);
  else wait(&st);
}
" > mata.c
gcc -o mata mata.c
fi
}

function genComparefiles() {

if ! test -x comparefiles ; then # si ya existe no se genera
echo "#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
  int salida=0;

  if (argc!=3) cout << \"Sintaxis: \" << argv[0] << \" <obtenido.txt> <correcto.txt>\" << endl;
  else
  {
    ifstream fo(argv[1]);
    ifstream fc(argv[2]);
    if (fo.is_open() && fc.is_open())
    {
      string so,sc,tmp;

      fo >> tmp;
      while (!fo.eof() || tmp.length()!=0)
      {
        so=so+tmp;
        tmp=\"\";
        fo >> tmp;
      }
      fc >> tmp;
      while (!fc.eof() || tmp.length()!=0)
      {
        sc=sc+tmp;
        tmp=\"\";
        fc >> tmp;
      }

      // ignorar los '-' en las líneas
      string scok, sook;
      for (unsigned int i=0; i<so.length(); i++)
        if (so[i]!='-') sook=sook+so[i];
      for (unsigned int i=0; i<sc.length(); i++)
        if (sc[i]!='-') scok=scok+sc[i];

      if (sook!=scok) {
        exit(-1);
      }
    }
    else {
      cout << \"Fichero \" << argv[1] << \" o \" << argv[2] << \" no encontrado\" << endl;
      exit(-1);
    }
  }
  exit(0);
  return salida;
}
" > comparefiles.cc

g++ -o comparefiles comparefiles.cc

fi
}

echo "*********************************************************"
echo "Autocorrector P2p3 "


# Comprobar si está valgrind instalado
hayValgrind=$(which valgrind)
if test "$hayValgrind" == "" ; then
  echo "AVISO: El corrector se ejecutará sin valgrind, por lo que es posible que"
  echo "el resultado de la corrección no sea fiable. Para comprobar realmente que la"
  echo "práctica es correcta, debes probar el corrector en un ordenador Linux"
  echo "con valgrind instalado antes de la entrega."
  echo
  read -p "Pulsa [Enter] para continuar"
  VAL=""
fi


echo " Generando ficheros auxiliares... "
genMata
genComparefiles
rm -f mata.c
rm -f comparefiles.cc

let npruebas=$npruebasa
pok=0;
noeje=0


function pruebaok() {
        echo "OK"
        let pok++;
}

# Compilacion
echo
echo "*********************************************************"
echo " Compilando..."
echo "*********************************************************"
#rm -rf src/*.o
#rm -f $PRINCIPAL


cd src
make -f $meikfail clean > /dev/null
make -f $meikfail 2>&1

if [ $? -ne 0 ]; then
	echo "LA PRACTICA NO COMPILA"
else
  mv $PRINCIPAL ..
  cd -

  if [ "$#" -ne 0 ]
  then
    npruebas=0
    noeje=1
  fi


  # Ejecucion y comprobacion de la salida

  echo

  echo
  echo "*********************************************************"
  echo " Ejecutando y comprobando salida a la vez..."
  echo " Deberían funcionar estas pruebas de entrada/salida y TAMBIEN las pruebas unitarias"
  echo "*********************************************************"

  for i in `ls $ENT`
  do
        if [ "$npruebas" -eq 0 ]
        then
          break
        fi

        bn=$(basename $i .txt)

	echo "Prueba $bn"

	tempfile=`mktemp /tmp/prog2iiXXXXX`

	# Ejecucion del programa
	$mata $MAXTIME $OBT/${bn}.salida-obtenida $VAL $PRINCIPAL $args < $ENT/$i > $OBT/${bn}.salida-obtenida 2> $tempfile

	if test -s $tempfile; then
		echo "ERROR DE EJECUCION..."
		cat $tempfile
		rm -rf $OBT/${bn}.salida-obtenida $tempfile
	else
		$comparefiles $OBT/${bn}.salida-obtenida $SAL/${bn}.salida-esperada
		if [ $? -ne 0 ]; then
			diff -EwB $OBT/${bn}.salida-obtenida $SAL/${bn}.salida-esperada 2>&1
		else
  		  pruebaok $i
		fi
	fi
	echo "--------------------------"
  done

  if [ $noeje -eq 1 ]; then
        echo -e "\nAVISO: no se ejecutan las pruebas de entrada/salida\n"
  else
   if [ $pok -eq $npruebas ]; then
	echo -e "\nTODAS LAS PRUEBAS DEL AUTOCORRECTOR FUNCIONAN\n"
   else
	echo -e "\nOJO: FALLAN" $[npruebas-pok] "PRUEBAS DEL AUTOCORRECTOR\n"
   fi
  fi


  echo "*********************************************************"
  echo " Ejecutando las pruebas unitarias del autocorrector..."
  echo "*********************************************************"

  if test -s ./p2TestRunner ; then
     tempfile=`mktemp /tmp/prog2iiXXXXX`
     tempfile2=`mktemp /tmp/prog2iiXXXXX`

     ./mata $MAXTIME $tempfile2 $VAL ./p2TestRunner > $tempfile2 2> $tempfile
     sgr=$(grep "\.OK\!$" $tempfile)
     if test "$sgr" != "" ; then
         echo -e "\nTODAS LAS PRUEBAS UNITARIAS DEL AUTOCORRECTOR FUNCIONAN\n"

     else
         echo -e "\nFALLA ALGUNA PRUEBA UNITARIA DEL AUTOCORRECTOR:\n"
         cat $tempfile

	echo
     fi

     rm -f $tempfile
     rm -f $tempfile2

  else
        echo "NO COMPILAN LAS PRUEBAS UNITARIAS DEL AUTOCORRECTOR"
  fi;

fi
