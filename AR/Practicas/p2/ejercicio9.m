%% Ejercicio 9

PA10 = DynamicParams(loadPA10Params());
qh = [0 0 0 0 0 0];
q1 = [0 deg2rad(45) deg2rad(45) 0 deg2rad(90) 0];
q2 = [deg2rad(20) deg2rad(90) deg2rad(45) deg2rad(-22.5) deg2rad(60) 0];
qs = [0 deg2rad(45) deg2rad(90) 0 deg2rad(-45) 0];

[q, qd, qdd] = jtraj(qh, q1, 50);
PA10.plot(q);
plot(qd);
pause(2);

[q, qd, qdd] = jtraj(qh, q2, 50);
PA10.plot(q);
plot(qd);
pause(2);

[q, qd, qdd] = jtraj(qh, qs, 50);
PA10.plot(q);
plot(qd);