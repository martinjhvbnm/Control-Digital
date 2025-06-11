#include <Controllino.h>

// Botones de control
const int boton_secuencia1 = CONTROLLINO_I16;
const int boton_secuencia2 = CONTROLLINO_I17;
const int boton_reinicio   = CONTROLLINO_I18;

// Arreglos con secuencias de LEDs
int leds1[10] = {
  CONTROLLINO_D7, CONTROLLINO_D0, CONTROLLINO_D6,
  CONTROLLINO_D12, CONTROLLINO_D13, CONTROLLINO_D14,
  CONTROLLINO_D8, CONTROLLINO_D2, CONTROLLINO_D1, CONTROLLINO_D7
};

int leds2[10] = {
  CONTROLLINO_D0, CONTROLLINO_D7, CONTROLLINO_D1,
  CONTROLLINO_D2, CONTROLLINO_D8, CONTROLLINO_D14,
  CONTROLLINO_D13, CONTROLLINO_D12, CONTROLLINO_D6, CONTROLLINO_D0
};

const int tiempo_ms = 500;
unsigned long t_anterior = 0;
int contador = 0;
int bandera = 2;  // 1 = secuencia 1, 0 = secuencia 2, 2 = apagado

void setup() {
  // Configurar pines de LED como salida y apagarlos
  for (int i = 0; i < 10; i++) {
    pinMode(leds1[i], OUTPUT);
    pinMode(leds2[i], OUTPUT);
    digitalWrite(leds1[i], LOW);
    digitalWrite(leds2[i], LOW);
  }

  // Configurar botones como entrada
  pinMode(boton_secuencia1, INPUT);
  pinMode(boton_secuencia2, INPUT);
  pinMode(boton_reinicio, INPUT);
}

void loop() {
  unsigned long t_actual = millis();

  // Cambiar bandera según botón presionado
  if (digitalRead(boton_secuencia1) == HIGH) {
    bandera = 1;
    contador = 0;
  }
  if (digitalRead(boton_secuencia2) == HIGH) {
    bandera = 0;
    contador = 0;
  }
  if (digitalRead(boton_reinicio) == HIGH) {
    bandera = 2;
    contador = 0;

    // Apagar todos los LEDs de ambas secuencias
    for (int i = 0; i < 10; i++) {
      digitalWrite(leds1[i], LOW);
      digitalWrite(leds2[i], LOW);
    }
  }

  // Temporización no bloqueante
  if (t_actual - t_anterior >= tiempo_ms) {
    t_anterior = t_actual;

    // Apagar todos los LEDs primero
    for (int i = 0; i < 10; i++) {
      digitalWrite(leds1[i], LOW);
      digitalWrite(leds2[i], LOW);
    }

    // Encender uno solo dependiendo de la secuencia activa
    if (bandera == 1) {
      digitalWrite(leds1[contador], HIGH);
    } else if (bandera == 0) {
      digitalWrite(leds2[contador], HIGH);
    }

    // Avanzar al siguiente LED
    contador = (contador + 1) % 10;
  }

  delay(10); // Antirebote básico
}
