//Practica 2: Encender todos los leds del tablero secuencialmente

#include <Controllino.h> // Librería de controllino

int leds[10] = {CONTROLLINO_D7,CONTROLLINO_D0, CONTROLLINO_D6, CONTROLLINO_D12, CONTROLLINO_D13, CONTROLLINO_D14, CONTROLLINO_D8, CONTROLLINO_D2, CONTROLLINO_D1,CONTROLLINO_D7};
int tiempo_ms=500;
unsigned long t_anterior=0;
int contador=0;


void setup() {
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
  
  if (t_actual - t_anterior >= tiempo_ms){ 

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
    t_anterior=t_actual;
  }
}
