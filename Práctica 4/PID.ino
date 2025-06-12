#include <Controllino.h>
#include "Stone_HMI_Define.h"          // Librería ofical de HMI Stone
#include "Procesar_HMI.h"              // Librería implementada para procesar respuestas del HMI

// Definicion de variables para ecuacion de recurrencias PID
float u_actual=0;                     // Almacena la señal de control actual
float u_anterior=0;
float Ki=6.85;               // Almacena la señal de control anterior
float Kp = 0.24, Td = 0;   // Pesos de la ecuacion de recurrencias
float T=0.05;                         // Tiempo de muestreo para ecuacion de reccurencias (50ms)
float e[3];                           // Vector que almacena los errores (dimension 3)

// VARIABLES PARA PWM DEL MOTOR
const int pin_motor        = CONTROLLINO_D0;              // Pin de salida PWM al motor
int    ref = 0;                                           // Valor leído del slider del HMI
char label2_text[10];                                     // Char para mostrar el Duty Cycle en el label2 del HMI

// VARIABLES PARA CONTEO DE PULSOS y RPM
const int entrada                    = CONTROLLINO_IN1;   // Pin de entrada de pulsos
volatile unsigned long conteo_pulsos = 0;                 // Contador de pulsos
char label4_text[10];                                     // Char para mostrar las RPM en el label4 del HMI
float rpm                            = 0;                 // RPM calculadas
const uint16_t PULSOS_POR_REV        = 36;                // Número de pulsos por revolución (Datos del EPC)
const float fs                = 1/T;                      // Frecuencia de muestreo

// VARIABLES PARA CONTROLAR EL TIEMPO DE ENVIO DE DATOS AL HMI
unsigned long t_previo=0;
unsigned long t_previo1=0;

// FUNCIONES ADICIONALES 
void contarPulso();

void setup() {

  //Comunicaciones seriales
  Serial.begin(115200);   // Comunicación serial con el PC
  Serial2.begin(115200);  // Comunicación serial con el HMI

  //Establece el pin de entrada del EPC y salida del motor
  pinMode(entrada, INPUT);
  pinMode(pin_motor, OUTPUT);

  // Inicializar valores de error a 0
  e[0] = 0;  e[1] = 0;  e[2] = 0;

  //CONFIGURACION HMI
  //Inicializa el deslizador de referencia en 0
  Stone_HMI_Set_Value("slider", "slider1", NULL, 0);

  // Inicializa los valores de las graficas en 0
  STONE_push_series("line_series", "line_series1", 0); //Envía un valor del eje X a graficar en el line_series1 que se pondrá al final
  STONE_push_series("line_series", "line_series2", 0); //Envía un valor del eje X a graficar en el line_series2 que se pondrá al final
  STONE_push_series("line_series", "line_series3", 0); //Envía un valor del eje X a graficar en el line_series3 que se pondrá al final

  

  
  //Inicializa los valores de spin_box Kp, Ki, Kd: Ki diferente de cero para evitar errores por division con 0
  Stone_HMI_Set_Value("spin_box", "spin_box1", NULL, 0.01);  // Kd en 0 el valor del spin box1 en el HMI. 
  Stone_HMI_Set_Value("spin_box", "spin_box2", NULL, 0.01);  // Ki en 0 el valor del spin box2 en el HMI. 
  Stone_HMI_Set_Value("spin_box", "spin_box3", NULL, 0.001); // Ti en 0 el valor del spin box3 en el HMI. 

  //Configuracion de la interrupcion, pin externo, funcion a ejecutar, flancos de bajada
  attachInterrupt(digitalPinToInterrupt(entrada), contarPulso, FALLING);
  noInterrupts();          //Comienza apagada la interrupcion
  TCCR1A = 0b00000000;     // Todo apagado, modo normal registro A. Counter1 del ATMEGA2560
  TCCR1B = 0b00000000;     // Todo apagado, modo normal registro B. Coun ter1 del ATMEGA2560
  TCCR1B |= B00000100;     // Configuración de preescaler a 256 (BIT CS12)
  TIMSK1 |= B00000010;     // Habilitar interrupción por comparación usando el registro TIMSK1 (modo CTC)
  OCR1A = 3125;            // Establecer valor TOP para generar interrupción: Tiempo interrupcion/16 ns=0.05/16ns=3125
  interrupts();            // Enciende la interrupcion
  HMI_init();              // Inicialización del sistema de colas para procesar las respuestas del HMI
}

void loop() {
   

  //Retardo no bloqueante de 10ms
  if(millis()-t_previo1>=10){

    ref= HMI_get_value("slider", "slider1");     // Solicita el valor del widget slider1 (Referencia) 
        Kp= HMI_get_value("spin_box", "spin_box1")/100;  // Solicita el valor del widget spin_box1 (Kp)
        Td= HMI_get_value("spin_box", "spin_box3")/100;  // Solicita el valor del widget spin_box3 (Kd)
        Ki= HMI_get_value("spin_box", "spin_box2")/100;  // Solicita el valor del widget spin_box2 (Ki)
    t_previo1=millis();                          // Acualizar tiempo previo con tiempo actual
  }
  
  //Retardo no bloqueante de 100ms
  if(millis()-t_previo>=100){

    t_previo=millis();                                                // Almacena en tiempo previo el tiempo actual
    dtostrf(ref, 7, 2, label2_text);                                  // Convertir float a char
    dtostrf(rpm, 7, 2, label4_text);                                  // Convertir float a char
 //    Kp= HMI_get_value("spin_box", "spin_box1")/100;  // Solicita el valor del widget spin_box1 (Kp)
  //  Ti= HMI_get_value("spin_box", "spin_box2")/100;  // Solicita el valor del widget spin_box2 (Ki)
   // Td= HMI_get_value("spin_box", "spin_box3")/100;  // Solicita el valor del widget spin_box3 (Kd)
    Stone_HMI_Set_Text("label","label2",label2_text);                 // Envía el texto de referencia al label2 (Referencia)
    Stone_HMI_Set_Text("label","label4",label4_text);                 // Envía el texto de rpm al label4 (RMP)

    //Envía un valor del eje X a graficar en el line_series1
    STONE_push_series("line_series", "line_series1", ref);            // Graficar referencia     
    //Envía un valor del eje X a graficar en el line_series2
    STONE_push_series("line_series", "line_series2", rpm);            // Graficar rpms
    //Envía un valor del eje X a graficar en el line_series3
    STONE_push_series("line_series", "line_series3", 150+(int)u_actual);         // Graficar señal de control 
  }
}

// Interrupción por TIMER1 para muestrear las RPM debido a que la librería del HMI se demora mucho
ISR(TIMER1_COMPA_vect){     

  TCNT1=0;               // Resetea el timer (Timer 1 a cero)
  // Calcular RPM (pulsos por segundo / pulsos por revolución) * 60
  rpm = (float(conteo_pulsos)*60)*fs / (PULSOS_POR_REV);
  e[2] = e[1];           //Almacenar el error anterior del error anterior
  e[1] = e[0];           //Almacenar el error anterior
  e[0] = ref - rpm;      // Calculo del error actual

  if(Ki>0){ //Evitar division para 0,  Ti=(Kp/Ki)
    // Ecuacion de recurrencias del controlador PID
    u_anterior = Kp * (e[0] - e[1] + T / (Kp/Ki) * e[0] + Td / T * (e[0] - 2 * e[1] + e[2]));
  


  }
  // Sumar u anterior con u actual
  u_actual +=u_anterior;
  // Limitar la señal de 0 a 255 para PWM
  if (u_actual > 255){ //Si es mayor a 255, establece 255
    u_actual = 255;
  }
  if (u_actual < 0){ //Si es menor a 0, establece 0
    u_actual = 0;
  }
  //Escribir la senal de control PWM al pin del motor
  analogWrite(pin_motor, (int)u_actual);

  // Mostrar datos en el monitor serial
  Serial.print("\nRPM: ");
  Serial.println(rpm);
  Serial.print("Pulsos: ");
  Serial.println(conteo_pulsos);
  Serial.print("Referencia: ");
  Serial.println(ref);
  Serial.print("Señal de control U: ");
  Serial.println(u_actual);
  Serial.print("Delta_U: ");
  Serial.println(u_anterior);
  Serial.print("Erro_actual: ");
  Serial.println(e[0]);
  Serial.print("Erro_1: ");
  Serial.println(e[1]);
  Serial.print("Erro_2: ");
  Serial.println(e[2]);
  Serial.print("Kp: ");
  Serial.println(Kp);
  Serial.print("Ti: ");
  Serial.println(Ki);
  Serial.print("Td: ");
  Serial.println(Td);
  Serial.print("fs: ");
  Serial.println(fs);
  Serial.print("T: ");
  Serial.println(T);
  
  conteo_pulsos=0;  // Resetea los pulsos 
}

// Interrupción por Hardware para contar los pulsos del motor
void contarPulso() {
  conteo_pulsos++;  // Incrementar contador al detectar pulso
}
