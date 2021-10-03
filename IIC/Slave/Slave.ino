//EL MASTER ES LA PLACA QUE VA A SER PROGRAMADA CONSTANTEMENTE POR EL USUARIO

#include <Wire.h>

#define Slave_Address 2


typedef struct {

  uint8_t  Comando;
  uint8_t  Valor;
  }
Tipo_Mensaje;

Tipo_Mensaje Mensaje;

//--------------------------------  FUNCIONES  ----------------------------------------------
void receiveEvent(int howMany);
void requestEvent();

void setup() {

  Serial.begin(9600);


  Wire.begin(Slave_Address);    /* join i2c bus with address 8 */
  delay(50);          
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
}

void loop() {
 
  delay(1000);
}


// function that executes whenever data is received from master
void receiveEvent(int howMany) {
  
  Wire.readBytes((byte*)& Mensaje, sizeof Mensaje);

  Serial.print("Comando: ");Serial.println(Mensaje.Comando);
  Serial.print("Valor: ");Serial.println(Mensaje.Valor);
  Serial.println("------RECEPCION TERMINADA-------");
}

// function that executes whenever data is requested from master
void requestEvent() {
 
  Mensaje.Comando=2;
  Mensaje.Valor=222;

  Wire.write((byte *) & Mensaje, sizeof Mensaje);  /*send string on request */
}
