%% Ejercicio 2

% Objeto Link ([theta, d, a, alpha, límite, offset])
L1 = Link ([0 0.317 0 -pi/2 0]);
L2 = Link ([0 0 0.45 0 0 -pi/2]);
L3 = Link ([0 0 0 pi/2 0 pi/2]);
L4 = Link ([0 0.48 0 -pi/2 0]);
L5 = Link ([0 0 0 pi/2 0]);
L6 = Link ([0 0.07 0 0 0]);

% Introducir límites articulares
L1.qlim = [-177, 177];
L2.qlim = [-64, 124];
L3.qlim = [-107, 158];
L4.qlim = [-255, 255];
L5.qlim = [-165, 165];
L6.qlim = [-255, 255];

L = [L1 L2 L3 L4 L5 L6];

robot = SerialLink(L, 'name', 'PA10_6GDL')
robot.n
robot.links
