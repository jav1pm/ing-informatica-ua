%% Ejercicio 4

% Cargar robot 6GDL y posiciones articulares
ejercicio2
ejercicio3

% Calcular matriz T para la posición articular qe
T1 = robot.fkine(qe)

% A partir de la matriz T, calcular qinversa
qinversa1 = robot.ikine6s(T1)
robot.plot(qinversa1)
Tinversa1 = robot.fkine(qinversa1)

% Calcular matriz T para la posición articular qs
T2 = robot.fkine(qs)

% A partir de la matriz T, calcular qinversa
qinversa2 = robot.ikine6s(T2)
robot.plot(qinversa2)
Tinversa2 = robot.fkine(qinversa2)

% Calcular matriz T para la posición articular q1
T3 = robot.fkine(q1)

% A partir de la matriz T, calcular qinversa
qinversa3 = robot.ikine6s(T3)
robot.plot(qinversa3)
Tinversa3 = robot.fkine(qinversa3)

% Calcular matriz T para la posición articular q2
T4 = robot.fkine(q2)

% A partir de la matriz T, calcular qinversa
qinversa4 = robot.ikine6s(T4)
robot.plot(qinversa4)
Tinversa4 = robot.fkine(qinversa4)