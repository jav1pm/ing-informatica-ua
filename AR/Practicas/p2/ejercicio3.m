%% Ejercicio 3

% Cargar robot 6GDL
ejercicio2

% Posición de home
qh = [0 0 0 0 0 0]
Tqh = robot.fkine(qh)
robot.plot(qh)

% Posición de escape
qe = [0 deg2rad(30) deg2rad(90) 0 deg2rad(60) 0]
Tqe = robot.fkine(qe)
robot.plot(qe)

% Posición de seguridad
qs = [0 deg2rad(45) deg2rad(90) 0 deg2rad(-45) 0]
Tqs = robot.fkine(qs)
robot.plot(qs)

% Posición q1
q1 = [0 deg2rad(45) deg2rad(45) 0 deg2rad(90) 0]
Tq1 = robot.fkine(q1)
robot.plot(q1)

% Posición q2
q2 = [deg2rad(20) deg2rad(90) deg2rad(45) deg2rad(-22.5) deg2rad(60) 0]
Tq2 = robot.fkine(q2)
robot.plot(q2)