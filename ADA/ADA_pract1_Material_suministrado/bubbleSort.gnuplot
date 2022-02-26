set terminal png
set output "bubbleSort.png"

set xlabel "Array size"
set ylabel "CPU time (ms)

set title  "Bubble Sort: Empirical Analysis of Exact Time Complexity"

plot "bubbleSort.CPUtimes" using 1:2 with lines title "CPU Times of sample"


##########################################################################
#Testing different analytical functions to determine which best fits:

set output "bubbleSort_and_Fit-Function.png"
set title "Bubble Sort: Exact time complexity and Fit function"


#------------------------------------------------------------------------

# Testing 3 different functions:
#Uncomment the function to be tested and comment the rest:

##Fit to a linear function: 
#y(x)=a*x + b 
#fitFunction="Fitting Bubblesort time values to f(n) = n+k"
#fit y(x) "bubbleSort.CPUtimes" using 1:2 via a,b


##Fit to a (n log n + k) function: 
#y(x)=a*x*log(x) + b 
#fitFunction="Fitting Bubblesort time values to f(n) = n log(n)+k"
#fit y(x) "bubbleSort.CPUtimes" using 1:2 via a,b


##Fit to a cuadratic function: 
y(x)=a*x*x + b*x + c
fitFunction="Fitting Bubblesort time values to f(n) = n²+n+k"
fit y(x) "bubbleSort.CPUtimes" using 1:2 via a,b,c

#------------------------------------------------------------------------


#Finally draw both functions (CPU times of sample and the one that best fits) on one graph
plot "bubbleSort.CPUtimes" using 1:2 with lines title "CPU times of sample", y(x) title fitFunction  


