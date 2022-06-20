%% Ejercicio 1

% Rotación de -90º sobre U y de 90º sobre V --> postmultiplicar
tr = transl(-3,10,10) * trotx(-90) * troty(90);

%redondea y muestra la matriz
disp(round(tr));

% Graficar el resultado de la transformación
trplot(tr);