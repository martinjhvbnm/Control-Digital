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

Estado estado_actual = INICIO;
unsigned long tiempo_actual = 0;
unsigned long tiempo_anterior = 0;
unsigned long duracion_estado = 0;

void setup() {
  pinMode(LED_rojo1, OUTPUT);
  pinMode(LED_amarillo1, OUTPUT);
  pinMode(LED_verde1, OUTPUT);
  pinMode(LED_rojo2, OUTPUT);
  pinMode(LED_amarillo2, OUTPUT);
  pinMode(LED_verde2, OUTPUT);

  // Iniciar con todos los LEDs apagados
  apagarTodo();
}

void loop() {
  tiempo_actual = millis();

  switch (estado_actual) {

    case INICIO:
      // Parpadeo amarillo1 y rojo2 por 2.5 s
      if (tiempo_actual - tiempo_anterior >= 500) {
        static bool parpadeo = false;
        parpadeo = !parpadeo;
        digitalWrite(LED_amarillo1, parpadeo);
        digitalWrite(LED_rojo2, parpadeo);
        tiempo_anterior = tiempo_actual;
        duracion_estado += 500;
      }

      if (duracion_estado >= 2500) {
        apagarTodo();
        estado_actual = ROJO;
        tiempo_anterior = tiempo_actual;
        duracion_estado = 0;
      }
      break;

    case ROJO:
      digitalWrite(LED_rojo1, encendido);
      digitalWrite(LED_verde2, encendido);

      if (tiempo_actual - tiempo_anterior >= 3000) {
        apagarTodo();
        estado_actual = VERDE;
        tiempo_anterior = tiempo_actual;
      }
      break;

    case VERDE:
      digitalWrite(LED_verde1, encendido);
      digitalWrite(LED_amarillo2, encendido);

      if (tiempo_actual - tiempo_anterior >= 2000) {
        apagarTodo();
        estado_actual = AMARILLO;
        tiempo_anterior = tiempo_actual;
      }
      break;

    case AMARILLO:
      digitalWrite(LED_amarillo1, encendido);
      digitalWrite(LED_rojo2, encendido);

      if (tiempo_actual - tiempo_anterior >= 2000) {
        apagarTodo();
        estado_actual = ROJO;
        tiempo_anterior = tiempo_actual;
      }
      break;

    default:
      estado_actual = INICIO;
      tiempo_anterior = tiempo_actual;
      break;
  }
}

//  Función para apagar todos los LEDs
void apagarTodo() {
  digitalWrite(LED_rojo1, LOW);
  digitalWrite(LED_amarillo1, LOW);
  digitalWrite(LED_verde1, LOW);
  digitalWrite(LED_rojo2, LOW);
  digitalWrite(LED_amarillo2, LOW);
  digitalWrite(LED_verde2, LOW);
}
