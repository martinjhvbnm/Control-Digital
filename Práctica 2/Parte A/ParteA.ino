// Práctica 2: Encendido y apagado de un LED del tablero mediante dos botones
#include <Controllino.h> //Librería de controllino

//const int led             = CONTROLLINO_D0;    // Salida D0 del controllino
const int boton_encendido = CONTROLLINO_I16;   // Entrada I16 del controllino
const int boton_apagado   = CONTROLLINO_I17;   // Entrada I17 del controllino
const int boton_reinicio   = CONTROLLINO_I18;   // Entrada I17 del controllino

int leds[10] = {CONTROLLINO_D7,CONTROLLINO_D0, CONTROLLINO_D6, CONTROLLINO_D12, CONTROLLINO_D13, CONTROLLINO_D14, CONTROLLINO_D8, CONTROLLINO_D2, CONTROLLINO_D1,CONTROLLINO_D7};
int leds2[10] = {CONTROLLINO_D0, CONTROLLINO_D7,CONTROLLINO_D1, CONTROLLINO_D2, CONTROLLINO_D8, CONTROLLINO_D14, CONTROLLINO_D13, CONTROLLINO_D12, CONTROLLINO_D6,CONTROLLINO_D0};
int tiempo_ms=500;
unsigned long t_anterior=0;
int contador=0;
int contador2=0;
int bandera=2;



void setup() {
// pinMode(led, OUTPUT);   // led como salida
  pinMode(boton_encendido, INPUT);  // boton_encendido como entrada
  pinMode(boton_apagado, INPUT);  // boton_apagado como entrada
  pinMode(boton_reinicio, INPUT);  // boton_apagado como entrada
  pinMode(CONTROLLINO_D0, OUTPUT);  // Salida digital D0
  pinMode(CONTROLLINO_D1, OUTPUT);  // Salida digital D1
  pinMode(CONTROLLINO_D2, OUTPUT);  // Salida digital D2
  pinMode(CONTROLLINO_D6, OUTPUT);  // Salida digital D6
  pinMode(CONTROLLINO_D7, OUTPUT);  // Salida digital D7
  pinMode(CONTROLLINO_D8, OUTPUT);  // Salida digital D8
  pinMode(CONTROLLINO_D12, OUTPUT); // Salida digital D12
  pinMode(CONTROLLINO_D13, OUTPUT); // Salida digital D13
  pinMode(CONTROLLINO_D14, OUTPUT); // Salida digital D14
}

void loop() {
     unsigned long t_actual=millis();
     if (digitalRead(boton_encendido) == HIGH ) {
    // digitalWrite(led, HIGH);  // Encender LED
    bandera=1;
    digitalWrite(leds2[contador2], LOW);
    digitalWrite(leds[contador], LOW);
    contador=0;
    contador2=0;
  }
    if (digitalRead(boton_apagado) == HIGH ) {
      // digitalWrite(led, HIGH);  // Encender LED
      bandera=0;
      digitalWrite(leds2[contador2], LOW);
      digitalWrite(leds[contador], LOW);
      contador=0;
      contador2=0;
  }
  if (digitalRead(boton_reinicio) == HIGH ) {
    // digitalWrite(led, HIGH);  // Encender LED
    bandera=2;}

if (t_actual - t_anterior >= tiempo_ms){
  // Encender el led con el botonI16
  if(bandera==1){
    if (contador<9){
      digitalWrite(leds[contador], LOW);
      digitalWrite(leds[contador+1], HIGH);
            contador++;
    }else{

      contador =0;
      digitalWrite(leds[contador], LOW);
      digitalWrite(leds[contador+1], HIGH);
    contador=1;
    }
  }
  else if(bandera==0){ 
        if (contador2<9){
      digitalWrite(leds2[contador2], LOW);
      digitalWrite(leds2[contador2+1], HIGH);
            contador2++;
    }else{

      contador2=0;
      digitalWrite(leds2[contador2], LOW);
      digitalWrite(leds2[contador2+1], HIGH);
    contador2=1;
    }

  }
  else{
    digitalWrite(leds2[contador2], LOW);
    digitalWrite(leds[contador], LOW);
    contador=0;
    contador2=0;

  };
        t_anterior=t_actual;

  }

  delay(10); // Pequeño retardo para evitar rebotes
}
