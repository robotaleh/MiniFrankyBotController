/////////////////////////////////////////////////////////////////////////////
// Programa de control a distancia de MiniFrankyBot mediante BT            //
// Se usa un gamepad de la Nintendo64 gracias a la librería N64Controler.h //
/////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////
// Librería de control del gamepad. //
//////////////////////////////////////
#include <N64Controller.h>
#include <Comandos.h>

/////////////////////////////////
// Pin de conexión del gamepad //
/////////////////////////////////
#define PIN_GAMEPAD 12

#define BATERIA A7

#define LED_ONOFF 9
#define LED_STATE 10
#define PIN_STATE 2


/////////////////////////////////////
// Objeto controlador del gamepad. //
/////////////////////////////////////
N64Controller FrankyController(PIN_GAMEPAD);

// Bandera para saber si se han enviado comandos en un ciclo de ejecución.
bool comandos_enviados = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_ONOFF, OUTPUT);
  pinMode(PIN_STATE, INPUT);
  pinMode(LED_STATE, OUTPUT);
  digitalWrite(LED_ONOFF, HIGH);
  // Inicializa el controlador del gamepad y espera para normalizar su estado.
  FrankyController.begin();
    analogWrite(LED_ONOFF, 80);
  delay(500);
}

void loop() {
  analogWrite(LED_ONOFF, 80);

  digitalWrite(LED_STATE, digitalRead(PIN_STATE));

  //Resetea la bandera de envío de comandos
  comandos_enviados = false;

  // Actualiza el estado de los botones del gamepad.
  FrankyController.update();

  //
  if (FrankyController.L()) {
    comandos_enviados = true;
    Serial.print(BRAZO_IZQUIERDO);
  }
  if (FrankyController.R()) {
    comandos_enviados = true;
    Serial.print(BRAZO_DERECHO);
  }
  if (FrankyController.D_up()) {
    comandos_enviados = true;
    Serial.print(ADELANTE);
  }
  if (FrankyController.C_up()) {
    comandos_enviados = true;
    Serial.print(AIRKICK);
  }
  if (FrankyController.C_right()) {
    comandos_enviados = true;
    Serial.print(LOWKICK_DERECHA);
  }

  if(comandos_enviados){
    digitalWrite(LED_ONOFF, LOW);
    delay(100);
  }
  delay(30);
}
