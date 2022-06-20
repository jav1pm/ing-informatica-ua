%% Ejercicio 8

PA10 = DynamicParams(loadPA10Params());

qs = [0 deg2rad(45) deg2rad(90) 0 deg2rad(-45) 0];
q1 = [0 deg2rad(45) deg2rad(45) 0 deg2rad(90) 0];
q2 = [deg2rad(20) deg2rad(90) deg2rad(45) deg2rad(-22.5) deg2rad(60) 0];

% añadir carga
PA10.payload(2.5, [0 0 0.1])

grav1 = PA10.gravload(qs)
grav2 = PA10.gravload(q1)
grav3 = PA10.gravload(q2)

in1 = PA10.itorque(qs, [1 0 0 0 0 0])
in2 = PA10.itorque(q1, [1 0 0 0 0 0])
in3 = PA10.itorque(q2, [1 0 0 0 0 0])

% separación 0.3m en el eje X
PA10.payload(2.5, [0.3, 0, 0.1])

grav1 = PA10.gravload(qs)
grav2 = PA10.gravload(q1)
grav3 = PA10.gravload(q2)

in1_1 = PA10.itorque(qs, [1 0 0 0 0 0])
in2_2 = PA10.itorque(q1, [1 0 0 0 0 0])
in3_3 = PA10.itorque(q2, [1 0 0 0 0 0])

% Al añadir una carga afectará a la componente gravitacional e inercial.
% Como se puede apreciar al ejectuar el programa los parámetros de ambas
% componentes varian.
