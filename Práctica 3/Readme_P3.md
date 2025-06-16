#  Práctica 3: Control básico de salidas digitales 
 Esta práctica tiene como objetivo controlar el brillo de un foco LED mediante
 modulación por ancho de pulso (PWM), utilizando una interfaz gráfica en una
 pantalla HMI (Human-Machine Interface). El valor del duty cycle será enviado
 desde la HMI al microcontrolador a través de comunicación serial, empleando
 la librería correspondiente. Esto permite ajustar dinámicamente la intensidad
 luminosa del LED desde la interfaz.
 Para esta práctica se usará la HMI configurada con un widget Spin Box, que envía
 valores de 0 a 100 correspondientes al porcentaje del duty cycle, el cual ajusta el
 valor del PWM de una salida digital.

---
# Materiales requeridos
 - Tablero de control con Controllino Mega integrado.
 - Fuente de alimentación del tablero.
 - Cable USB tipo B 2.0.
 - Cable USB tipo A a A.
 - PC con Arduino IDE instalado y configurado para Controllino
 - Software Stone Designer GUI.

## Reto:
- Ampliar el programa actual para controlar dos LEDs de forma independiente, utilizando elementos de la interfaz gráfica (spin boxes) para regular el brillo de
 cada LED y botones físicos del tablero para encender y apagar cada uno de ellos.
 1. Descripción de la actividad:
 - Agregar un segundo widget tipo SpinBox a la interfaz gráfica. Este segundo  SpinBox permitirá controlar el duty cycle (porcentaje deciclodetrabajoPWM)
 del segundo LED conectado al tablero.
 - Configurar dos botones físicos en el tablero:– Elprimer botón físico controlará el encendido/apagado del primer LED.– Elsegundo
 botón físico controlará el encendido/apagado del segundo  LED.
- La acción de los botones físicos debe ser independiente del valor del SpinBox:
- El botón únicamente habilitará o deshabilitará el encendido del LED,
 pero el brillo será determinado por el valor actual del SpinBox asociado.
- El sistema debe garantizar que, si un LED está apagado por el botón físico,
 no se active aunque se modifique el SpinBox correspondiente (hasta que el  botón vuelva a presionarse).
---
