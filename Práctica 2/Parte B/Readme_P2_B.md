# Práctica 2_B: Control de Semáforo con Controllino 

-  Se diseña un sistema que controle dos semáforos (Semáforo A y Semáforo B) ubicados en una intersección perpendicular, usando el enfoque de máquina de estados finita(FSM).El sistema debe simular el comportamiento simple de los semáforos, de manera que nunca haya luz verde simultánea para ambos sentidos, y se respeten los tiempos estándar de duración  de cada luz.
![Circulacion vehicular simple ](imagene.png)

---
## ⚙️ Materiales requerido

- Placa **Controllino Mega**
- 6 LEDs (divididos en dos conjuntos):
  - Primer conjunto: **LED_ROJO**, **LED_AMARILLO** y **LED_VERDE**
  - Segundo conjunto: **LED_ROJO2**, **LED_AMARILLO2** y **LED_VERDE2**
---
## 🧠 Objetivo

El objetivo es demostrar el uso de:
- **Máquinas de estados** mediante `enum` y `switch`.
- **Temporización no bloqueante** con `millis()`.
- **Manipulación de múltiples salidas digitales** (LEDs) en la plataforma Controllino.

---

## 🔍 Descripción del Código

El código se divide en dos partes principales:

### 1. Definiciones y Variables

- **Definición de pines y estados:**  
  Se definen los pines para cada LED utilizando directivas `#define`. También se establecen constantes para los estados de encendido y apagado, y se define una enumeración `Estado` que representa los distintos estados del sistema:
  
  ```cpp
  #define LED_ROJO CONTROLLINO_D0
  #define LED_AMARILLO CONTROLLINO_D1
  #define LED_VERDE CONTROLLINO_D2
  
  #define LED_ROJO2 CONTROLLINO_D6
  #define LED_AMARILLO2 CONTROLLINO_D7
  #define LED_VERDE2 CONTROLLINO_D8
  
  #define encendido 1
  #define apagado 0
  
  enum Estado {
    INICIO,
    ROJO,
    VERDE,
    AMARILLO
  };
