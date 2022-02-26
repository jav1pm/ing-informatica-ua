#FRANCISCO JAVIER PEREZ MARTINEZ   DNI: 74384305M

##########################################################################
# pow2_1 pow2_2 pow2_3
##########################################################################

set terminal png
set output "pow2.png"

set xlabel "n"
set ylabel "Llamadas Recursivas"

set xrange [0:200]
set yrange [0:1000]

set title  "Coste de las funciones pow2()"

plot "pow2.llamadasRecursivas" using 1:2 with lines title "pow2(n) = 2·pow2(n-1)",\
     "pow2.llamadasRecursivas" using 1:3 with lines title "pow2(n) = pow2(n/2)·pow2(n/2)",\
     "pow2.llamadasRecursivas" using 1:4 with lines title "pow2(n) = (pow2(n/2))²"
     



