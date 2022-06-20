%% Ejercicio 5

% Cargar robot 6GDL
ejercicio2

% Robot planar
L10 = Link ([0 0 1 0]);
L11 = Link ([0 0 1 0]);
L12 = Link ([0 0 1 0]);

planar = [L10 L11 L12];
planar = SerialLink(planar, 'name', 'planar');

% ------ ROBOT PA10 ------ %
% El robot se encuentra al límite de su espacio de trabajo 
q = [0 pi/2 0 0 0 0];

% vector coordenadas random para probar
qrand = [0 rand 0 0 0 rand];

% Matriz Jacobiana
J = jacob0(robot,q)

% Determinante = nulo
DetJ = det(J)

robot.plot(qrand);
figure
robot.plot(q);
% ------ ROBOT PA10 ------ %

% ------ ROBOT PLANAR ------ %
qplanar = [1 0 0];
Jplanar = jacob0(planar, qplanar)
planar.plot(qplanar);
% ------ ROBOT PLANAR ------ %