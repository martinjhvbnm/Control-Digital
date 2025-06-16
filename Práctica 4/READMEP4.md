#  Práctica 4: Control básico de salidas digitales 
  Diseñare implementar un controlador PID que regule automáticamente la velocidad del motor DC del EPC a un valor de referencia definido por el usuario mediante la
 interfaz HMI.

---
# Materiales requeridos
 - Tablero de control con Controllino Mega integrado.
 - Fuente de alimentación del tablero.
 - Cable USB tipo B 2.0.
 - Cable USB tipo A a A.
 - PC con Arduino IDE instalado y configurado para Controllino
 - Software Stone Designer GUI.
 - 6jumpers macho ahembra largos.
 - 6jumpers macho amacholargos.
 - Destornillador plano pequeño
---
## Reto:
 Diseñar e implementar un controlador PID que regule automáticamente la velocidad
 del motor DC del EPC a un valor de referencia definido por el usuario mediante la
 interfaz HMI.
 Cada grupo de trabajo deberá implementar un sistema de control PID que cumpla
 con las siguientes condiciones:
 - La velocidad del motor debe alcanzar el valor de referencia en el menor
 tiempo posible, sin sobrepasarlo excesivamente.
 - El sistema debe mostrar estabilidad (sin oscilaciones) y un error en estado
 estacionario inferior al 5%.
 - El sistema debe mostrar en tiempo real: valor de referencia (setpoint) en el
 slider, velocidad actual (RPM), gráfica de la señal de control, comparativa
 entre referencia y velocidad actual.
 Restricciones:
 - El algoritmo PID debe ser implementado en código mediante la ecuación de
 recurrencias (no se permite el uso de librerías PID externas).

---
## Descripción general

Este sistema permite:

- Encender/apagar LED1 con el botón físico 1 (I16)
- Encender/apagar LED2 con el botón físico 2 (I17)
- Controlar la intensidad de cada LED (PWM) desde la pantalla HMI usando dos spin boxes:
  - `spin_box1`: controla el duty cycle de LED1
  - `spin_box2`: controla el duty cycle de LED2
- Mostrar los valores PWM correspondientes en el monitor serial para depuración
---
## Configuración del sistema

### Pines utilizados en el Controllino:

| Elemento       | Pin Controllino |
|----------------|-----------------|
| LED1 (PWM)     | D0              |
| LED2 (PWM)     | D1              |
| Botón LED1     | I16             |
| Botón LED2     | I17             |

### Pantalla HMI

Se comunica por `Serial2` a 115200 baudios. Se esperan dos componentes configurados:

- `spin_box1`: valor 0–100 para duty cycle de LED1
- `spin_box2`: valor 0–100 para duty cycle de LED2

La comunicación se gestiona con funciones `HMI_get_value` y `Stone_HMI_Set_Value`.

## Lógica del programa

1. **Inicialización**:
   - Se configuran pines de entrada y salida.
   - Se inicializa la comunicación serial y la pantalla HMI.

2. **Botones físicos**:
   - Se detectan flancos ascendentes para cambiar el estado de cada LED (encendido ↔ apagado).
   - Se usa una bandera por LED (`bandera`, `bandera2`) para rastrear su estado.
3. **Control PWM**:
   - Solo si el LED está encendido (bandera == 1), se lee el valor del HMI y se mapea de 0–100 a 0–255 para el `analogWrite`.
---
## Archivos

- `main.ino`: Código principal del sistema
- `Procesar_HMI.h`: Módulo que contiene funciones auxiliares para comunicarse con la pantalla HMI
- `Stone_HMI_Define.h`: Definiciones específicas para el modelo de pantalla Stone usado

## Ejemplo de interfaz HMI
![Interfaz HMI con spin boxes](pantallap3.png)
