#  Práctica 2: Control básico de salidas digitales 
Este proyecto implementa un sistema de **dos secuencias de encendido de LEDs** utilizando la placa **Controllino**.
El usuario puede seleccionar entre dos patrones de iluminación presionando botones físicos, y también puede detener
la secuencia con un tercer botón.

---
# Materiales requeridos
 - Tablero de control con Controllino Mega integrado.
 - Fuente de alimentación del tablero.
 - Cable USB tipo B 2.0.
 - PC con Arduino IDE instalado y configurado para Controllino

## Objetivo

- Utilizar los tres botones del tablero de pruebas para controlar el patrón de  encendido de los LED ubicados en forma de matriz 3x3. Tanto los botones
 como los LED ya se encuentran conectados directamente al Controllino  Mega.
---

##  Entradas y salidas

| Elemento              | Pin Controllino |
|-----------------------|------------------|
| Botón Secuencia 1     | `CONTROLLINO_I16` |
| Botón Secuencia 2     | `CONTROLLINO_I17` |
| Botón Reinicio        | `CONTROLLINO_I18` |
| Salidas LEDs (secuencia) | `CONTROLLINO_D7`, `CONTROLLINO_D0`, `CONTROLLINO_D6`,
  `CONTROLLINO_D12`, `CONTROLLINO_D13`, `CONTROLLINO_D14`,
  `CONTROLLINO_D8`, `CONTROLLINO_D2`, `CONTROLLINO_D1`, `CONTROLLINO_D7` |
| Salidas LEDs (secuencia) | `CONTROLLINO_D0`, `CONTROLLINO_D7`, `CONTROLLINO_D1`,
  `CONTROLLINO_D2`, `CONTROLLINO_D8`, `CONTROLLINO_D14`,
  `CONTROLLINO_D13`, `CONTROLLINO_D12`, `CONTROLLINO_D6`, `CONTROLLINO_D0` |  

---

## Comportamiento

- Al presionar el **botón de secuencia 1**, se encienden los LEDs en el orden definido por el arreglo `leds1[]`.
- Al presionar el **botón de secuencia 2**, los LEDs se encienden siguiendo el orden en `leds2[]`.
- Al presionar el **botón de reinicio**, se apagan todos los LEDs y se detiene la secuencia.

El sistema usa **temporización no bloqueante** con `millis()` para permitir una ejecución fluida sin detener el programa.

---

## Lógica de control

```cpp
// Lectura de botones cambia la bandera
if (digitalRead(boton_secuencia1) == HIGH) bandera = 1;
if (digitalRead(boton_secuencia2) == HIGH) bandera = 0;
if (digitalRead(boton_reinicio) == HIGH) bandera = 2;
