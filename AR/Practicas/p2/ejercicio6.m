%% Ejercicio 6

PA10 = DynamicParams(loadPA10Params());

qs = [0 deg2rad(45) deg2rad(90) 0 deg2rad(-45) 0];
q1 = [0 deg2rad(45) deg2rad(45) 0 deg2rad(90) 0];
q2 = [deg2rad(20) deg2rad(90) deg2rad(45) deg2rad(-22.5) deg2rad(60) 0];

tau = PA10.rne(qs, [0 0 0 0 0 0], [0 0 0 0 0 0])
tau = PA10.rne(q1, [0 0 0 0 0 0], [0 0 0 0 0 0])
tau = PA10.rne(q2, [0 0 0 0 0 0], [0 0 0 0 0 0])
