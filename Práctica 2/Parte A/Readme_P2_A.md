#  Práctica 2: Control básico de salidas digitales 
Este proyecto implementa un sistema de **dos secuencias de encendido de LEDs** utilizando la placa **Controllino**. El usuario puede seleccionar entre dos patrones de iluminación presionando botones físicos, y también puede detener la secuencia con un tercer botón.

---

## Objetivo

Implementar control digital de salidas utilizando **temporización no bloqueante (`millis`)**, **arreglos** y **lectura de botones** en una placa **Controllino**. Este tipo de control es útil en sistemas industriales donde múltiples salidas deben activarse en orden con tiempos definidos.

---

##  Hardware requerido

- 1 Placa **Controllino Mini / Maxi / Mega**
- 10 salidas digitales conectadas a LEDs (con resistencias)
- 3 botones (entradas digitales)
- Cables y protoboard

---

##  Entradas y salidas

| Elemento              | Pin Controllino |
|-----------------------|------------------|
| Botón Secuencia 1     | `CONTROLLINO_I16` |
| Botón Secuencia 2     | `CONTROLLINO_I17` |
| Botón Reinicio        | `CONTROLLINO_I18` |
| Salidas LEDs (secuencia) | `D0`, `D1`, `D2`, `D6`, `D7`, `D8`, `D12`, `D13`, `D14` |

---

## 🔄 Comportamiento

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
