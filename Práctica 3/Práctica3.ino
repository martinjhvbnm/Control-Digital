#include <Controllino.h>
#include "Stone_HMI_Define.h"
#include "Procesar_HMI.h"

const int led              = CONTROLLINO_D0; // Salida digital D0 
const int led2              = CONTROLLINO_D1; // Salida digital D1
const int boton_led1 = CONTROLLINO_I16;   // Entrada I16 del controllino e/a
const int boton_led2   = CONTROLLINO_I17;   // Entrada I17 del controllino e/a
int       pwmValue         = 0;              // valor convertido (0-255)
int       pwmValue2         = 0;              // valor convertido (0-255)
float     dutyCyclePercent = 0;              // valor en porcentaje (0-100)
float     dutyCyclePercent2 = 0;              // valor en porcentaje (0-100)
int estado_ac=0;
int estado_ant=0;
int bandera=0;
int bandera2=0;

// Estados anteriores de los botones
int estadoBoton1Anterior = LOW;
int estadoBoton2Anterior = LOW;

void setup() {
  Serial.begin(115200);   // Comunicación serial con el PC
  Serial2.begin(115200);  // Comunicación serial con el HMI
  pinMode(led, OUTPUT);   // led como salida
  pinMode(led2, OUTPUT);   // led como salida
  pinMode(boton_led1, INPUT);  // boton_encendido/apagado como entrada
  pinMode(boton_led2, INPUT);  // boton_apagado/apagado como entrada
  HMI_init();             // Inicializa el sistema de colas para las respuestas el HMI
  Stone_HMI_Set_Value("spin_box", "spin_box1", NULL, 0);  // Pone en 0 el valor del spin box en el HMI. 
  Stone_HMI_Set_Value("spin_box", "spin_box2", NULL, 0);  // Pone en 0 el valor del spin box en el HMI. 

}

void loop() {
  dutyCyclePercent=HMI_get_value("spin_box", "spin_box1"); // Obtiene el valor del spin_box1
  dutyCyclePercent2=HMI_get_value("spin_box", "spin_box2"); // Obtiene el valor del spin_box1
//if(digitalRead(estado) == LOW ){

/////////////////////

    // Lectura y detección de flanco para botón 1
  int estadoBoton1 = digitalRead(boton_led1);
  if (estadoBoton1 == HIGH && estadoBoton1Anterior == LOW) {
    bandera++;
    if (bandera > 2) bandera = 1;

  }
  estadoBoton1Anterior = estadoBoton1;

  // Control del LED1 según bandera
  if (bandera == 1) {
    digitalWrite(led, HIGH);  // Encender LED
  } else if (bandera == 2) {
     digitalWrite(led, LOW);  // APAGAR LED
    bandera = 0;
  }


/////////////////////

/////////////////////

    // Lectura y detección de flanco para botón 2
  int estadoBoton2 = digitalRead(boton_led2);
  if (estadoBoton2 == HIGH && estadoBoton2Anterior == LOW) {
    bandera2++;
    if (bandera2 > 2) bandera2 = 1;

  }
  estadoBoton2Anterior = estadoBoton2;

  // Control del LED1 según bandera
  if (bandera2 == 1) {
    digitalWrite(led2, HIGH);  // Encender LED
  } else if (bandera2 == 2) {
     digitalWrite(led2, LOW);  // APAGAR LED
    bandera2 = 0;
  }


/////////////////////






  
  if (dutyCyclePercent >= 0 && dutyCyclePercent <=100 && bandera==1){
      
    pwmValue = map(dutyCyclePercent, 0, 100, 0, 255);      // Mapea el valor de duty cycle en porcentaje a valores de 0 a 255
    analogWrite(led, pwmValue);
    Serial.print("Duty cycle (%): ");
    Serial.print(dutyCyclePercent);
    Serial.print(" -> PWM value: ");
    Serial.println(pwmValue);
  }else {
    Serial.println("Ingresa un valor entre 0 y 100 o encienda el led");
  }
  if (dutyCyclePercent2 >= 0 && dutyCyclePercent2 <=100 && bandera2==1){
      
    pwmValue2 = map(dutyCyclePercent2, 0, 100, 0, 255);      // Mapea el valor de duty cycle en porcentaje a valores de 0 a 255
    analogWrite(led2, pwmValue2);
    Serial.print("Duty cycle (%): ");
    Serial.print(dutyCyclePercent2);
    Serial.print(" -> PWM value2: ");
    Serial.println(pwmValue2);
  }else {
    Serial.println("Ingresa un valor entre 0 y 100 o encienda el led2");
  }
}
