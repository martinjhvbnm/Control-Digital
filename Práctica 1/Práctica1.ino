//Practica 1: Encender todos los leds del tablero secuencialmente
#include <Controllino.h> // Librería de controllino

//Vector que contiene la secuencia deseada
int leds[10] = {CONTROLLINO_D7,CONTROLLINO_D0, CONTROLLINO_D6, CONTROLLINO_D12, CONTROLLINO_D13, CONTROLLINO_D14, CONTROLLINO_D8, CONTROLLINO_D2, CONTROLLINO_D1,CONTROLLINO_D7};

//Variable que almacena el tiempo del retardo no bloqueante
int tiempo_ms=500; 

//Variable que almacena el tiempo anterior
unsigned long t_anterior=0;

//Contador para recorrer las posiciones del vector
int contador=0;

//Funcion de configuracion
void setup() {
    //Recorrer el vector con las varialbs de los LEDs
    for (int i = 0; i < 10; i++) {
         //Establecer las mismas como salidas
        pinMode(leds[i], OUTPUT);
    }
}

//Funcion recurrente
void loop() {
    //Almacenar el tiempo actual
    unsigned long t_actual=millis();
    //Retardo no bloqueante, se ejecuta cada 500ms
    //Comparar diferencia del tiempo actual y anterior
    //Para entrar a la condicion
    if (t_actual - t_anterior >= tiempo_ms){ 
        //Verificar si el contador es menor a 9
        if (contador<9){
            //Apagar el LED en la poscion actual
            digitalWrite(leds[contador], LOW);
            //Encender el LED en la posicion siguiente
            digitalWrite(leds[contador+1], HIGH);
            //Incrementar contador en 1
            contador++;
            //Si no cuple la condicion de menor a 9
        }else{
            //Reiniciar contador para poder repetir
            contador =0;
            //Apagar el LED en la poscion actual
            digitalWrite(leds[contador], LOW);
            //Encender el LED en la posicion siguiente
            digitalWrite(leds[contador+1], HIGH);
            //Forzar a que comeince la secuiane desde el led siguiente al reiniciar
            contador=1;
        }
    }
    //Actualiza el tiempo anterior con el actual
    t_anterior=t_actual;
  }
}
