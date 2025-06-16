# Práctica 1: Manejo de Salidas Digitales con Controllino Mega

Enestapráctica se utilizará el módulo Controllino Mega para encender una secuencia de focos LED conectados en el tablero de prácticas. Elcódigo será desarrollado
utilizando la librería _Controllino.h_, lo que permitirá familiarizarse con el uso  de variables predefinidas para manipular las salidas digitales del dispositivo.
El objetivo es comprender cómo utilizar dichas variables para generar una secuencia de encendido de focos LED, tal como se haría en una aplicación de control
secuencial básica en automatización.

##  Materiales requeridos
 - Tablero de control con Controllino Mega integrado.
 - Fuente de alimentación del tablero.
 - Cable USB tipo B 2.0.
 - PC con Arduino IDE instalado y configurado para Controllino
## Requisitos:
 - Usar punteros
 - Usar retardos no bloqueantes.
## Reto
 Usar el Controllino Mega para controlar un amatriz de 9 LEDs del tablero, dispuestos en una cuadrícula de 3x3. Los LEDs deben encenderse uno por uno siguiendo un  patrón en espiral, en el siguiente orden:

| LED1  | LED2  | LED3  |

| LED4  | LED5  | LED6  |

| LED7  | LED8  | LED9  |
- Orden de encendido:  1 → 2 → 3 → 6 → 9 → 8 → 7 → 4 → 5 y se repite.
- Asigna un pin digital a cada LED usando variables predefinidas de la librería  _Controllino.h_.
- CadaLEDdebeencenderse durante 500 ms y luego apagarse, justo en ese  instante se enciende el siguiente.
- Al finalizar, la secuencia se debe reiniciar.
### Módulos de software del sistema
- Práctica1.ino
### Descripción del funcionamiento
La descripción de cada módulo de software es la siguiente:
- LED[10]: Vector que contiene la secuencia deseada
- void setup:Funcion de configuracion, recorrer el vector mediante un for con las variables de los LEDs para establecer las mismas como salidas, se usa el retardo no bloqueante, para comparar el tiempo actual y el anterior para entrar a la condicion de apagar el led actual y encender el siguiente, ademas de incrementar en esta funcion recurrente un contador, y al finalizar actualiza el tiempo anterior con el actual. 
- void loop(): Almacenar el tiempo actual, 


 

