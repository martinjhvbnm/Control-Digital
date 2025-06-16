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
---
## Reto:
- Ampliar el programa actual para controlar dos LEDs de forma independiente, utilizando elementos de la interfaz gráfica (spin boxes) para regular el brillo de
 cada LED y botones físicos del tablero para encender y apagar cada uno de ellos.
Descripción de la actividad:
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
## Descripción general

Este sistema permite:

- Encender/apagar LED1 con el botón físico 1 (I16)
- Encender/apagar LED2 con el botón físico 2 (I17)
- Controlar la intensidad de cada LED (PWM) desde la pantalla HMI usando dos spin boxes:
  - `spin_box1`: controla el duty cycle de LED1
  - `spin_box2`: controla el duty cycle de LED2
- Mostrar los valores PWM correspondientes en el monitor serial para depuración

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
   - Si no está encendido, se muestra un mensaje de advertencia por el monitor serial.

## Archivos

- `main.ino`: Código principal del sistema
- `Procesar_HMI.h`: Módulo que contiene funciones auxiliares para comunicarse con la pantalla HMI
- `Stone_HMI_Define.h`: Definiciones específicas para el modelo de pantalla Stone usado

## Ejemplo de interfaz HMI
![Interfaz HMI con spin boxes](docs/hmi_example.png)
