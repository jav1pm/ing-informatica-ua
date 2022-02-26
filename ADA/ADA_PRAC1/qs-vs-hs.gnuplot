#FRANCISCO JAVIER PEREZ MARTINEZ   DNI: 74384305M

##########################################################################
#Testing QuickSort:
set terminal png
set output "quickSort.png"

set xlabel "size of arrays"
set ylabel "Millions of program steps"

set yrange [0:]
set xtics ("2¹⁵" 32768, "2²º" 1048576, "2²¹" 2097152)

set title  "Quicksort"

plot "qs-vs-hs.Msteps" using 1:2 with lines title "random arrays", "qs-vs-hs.Msteps" using 1:4 with lines title "sorted arrays", "qs-vs-hs.Msteps" using 1:6 with lines title "reverse-sorted arrays"


##########################################################################
#Testing HeapSort:

set output "heapSort.png"
set title "Heapsort"


plot "qs-vs-hs.Msteps" using 1:3 with lines title "random arrays", "qs-vs-hs.Msteps" using 1:5 with lines title "sorted arrays", "qs-vs-hs.Msteps" using 1:7 with lines title "reverse-sorted arrays"

##########################################################################
#Testing QuickSort vs HeapSort (Random Arrays):

y(x)=a*x*log(x) + b 
fitFunction="fitting Quicksort time values to ..."
fit y(x) "qs-vs-hs.Msteps" using 1:2 via a,b

y2(x)=a*x*log(x) + b 
fitFunction2="fitting Heapsort time values to ...
fit y2(x) "qs-vs-hs.Msteps" using 1:3 via a,b

set output "qs-vs-hs-RA.png"
set title "Quicksort vs Heapsort(random arrays)"


plot "qs-vs-hs.Msteps" using 1:2 with lines title "Quicksort", "qs-vs-hs.Msteps" using 1:3 with lines title "Heapsort", y(x) title fitFunction, y2(x) title fitFunction2

##########################################################################
#Testing QuickSort vs HeapSort (Sorted Arrays):

y3(x)=c*x*log(x) + d 
fitFunction3="fitting Quicksort time values to ..."
fit y3(x) "qs-vs-hs.Msteps" using 1:4 via c,d

y4(x)=c*x*log(x) + d 
fitFunction4="fitting Heapsort time values to ..."
fit y4(x) "qs-vs-hs.Msteps" using 1:5 via c,d

set output "qs-vs-hs-SA.png"
set title "Quicksort vs Heapsort(sorted arrays)"


plot "qs-vs-hs.Msteps" using 1:4 with lines title "Quicksort", "qs-vs-hs.Msteps" using 1:5 with lines title "Heapsort", y3(x) title fitFunction3, y4(x) title fitFunction4

##########################################################################
#Testing QuickSort vs HeapSort (Reverse-Sorted Arrays):

y5(x)=m*x*log(x) + n
fitFunction5="fitting Quicksort time values to ..."
fit y5(x) "qs-vs-hs.Msteps" using 1:6 via m,n

y6(x)=m*x*log(x) + n 
fitFunction6="fitting Heapsort time values to ..."
fit y6(x) "qs-vs-hs.Msteps" using 1:7 via m,n

set output "qs-vs-hs-RSA.png"
set title "Quicksort vs Heapsort(reverse-sorted arrays)"


plot "qs-vs-hs.Msteps" using 1:6 with lines title "Quicksort", "qs-vs-hs.Msteps" using 1:7 with lines title "Heapsort", y5(x) title fitFunction5, y6(x) title fitFunction6



