clc %Limpiar consola
% Cargar los datos desde el archivo .txt
datos = load('datosmotor.txt');

% Separar columnas
tiempo = datos(:,1);
voltaje_entrada = datos(:,2);
salida_motor = datos(:,3);


% Parametros de la funcion de transferencia
deltay=5.4;
K = (deltay-0)/(4.988-0)  % Ganancia
punto63=63.2*(1/100)*deltay
thetatau=0.55;            
theta=0.2;                % Tiempo muerto
tau=thetatau-theta;       %Constante de tiempo

s = tf('s'); % Variable simbólica s
G = K / (tau*s + 1); % Función de transferencia
% Respuesta al escalón unitario
% Simular respuesta al escalón de 5V
t = 0:0.01:10; % Tiempo de simulación
[y, t] = step(G, t); % Respuesta al escalón unitario
y5 = 5 * y;          % Escalón de 5V

% Graficar funcion de transferencia
figure;
plot(t, y5, 'b', 'LineWidth', 1.5);
xlabel('Tiempo (s)');
ylabel('Respuesta de salida');
title('Respuesta al escalón de 5V');
grid on;
% Graficar entrada y salida
figure;
plot(tiempo, voltaje_entrada, 'b', 'LineWidth', 1.5); hold on;
plot(tiempo, salida_motor, 'r', 'LineWidth', 1.5);
xlabel('Tiempo (s)');
ylabel('Amplitud');
title('Voltaje de Entrada y Salida del Motor vs Tiempo');
legend('Voltaje de entrada', 'Salida del motor');
grid on;

%Constantes para el controlador PID del sistema
pidtune(G,'PID')
