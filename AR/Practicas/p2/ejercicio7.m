%% Ejercicio 7

PA10 = DynamicParams(loadPA10Params())
qs = [0 deg2rad(45) deg2rad(90) 0 deg2rad(-45) 0];
q1 = [0 deg2rad(45) deg2rad(45) 0 deg2rad(90) 0];
q2 = [deg2rad(20) deg2rad(90) deg2rad(45) deg2rad(-22.5) deg2rad(60) 0];

% Par debido a la gravedad G
% componente gravitacional de la dinámica del robot
PA10.gravity = [0 0 1.62]
G0 = PA10.gravload(qs)
G1 = PA10.gravload(q1)
G2 = PA10.gravload(q2)

% Par debido a la inercia M
% componente inercial de la dinámica del robot
M0 = PA10.itorque(qs, [1 0 0 0 0 0])
M1 = PA10.itorque(q1, [0 1 0 0 0 0])
M2 = PA10.itorque(q2, [0 0 1 0 0 0])

% Matriz de Coriolis C
C0 = PA10.coriolis(qs, [pi/2 0 pi 0 0 0])
C1 = PA10.coriolis(q1, [1 0 pi/2 0 0 0])
C2 = PA10.coriolis(q2, [1 0 pi 0 0 0])
