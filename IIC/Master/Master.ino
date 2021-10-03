//EL MASTER ES LA PLACA QUE VA A SER PROGRAMADA CONSTANTEMENTE POR EL USUARIO

#include <Wire.h>

#define Slave_Address 2

typedef struct {

  uint8_t  Comando;
  uint8_t  Valor;

  }
Formato_Info;

Formato_Info Mensaje;

//--------------------------------  FUNCIONES  ----------------------------------
void EnviarInfoaEsclavo(Formato_Info Mensaje);
void RecibirInfoDeEsclavo(Formato_Info Mensaje);


void setup() {
  
  Serial.begin(9600);

  Wire.begin(); //no parametes = Master
  delay(50);
  
}
int i=0;

void loop() {
 
  //  Write Data  
  Mensaje.Comando=i;
  Mensaje.Valor=i*2;
  EnviarInfoaEsclavo(Mensaje);
  i=i+1;
  delay(1000);
  
  RecibirInfoDeEsclavo(Mensaje);
  
  delay(1000);
}

//--------------------------------   ENVIAR INFO A ESCLAVO   ----------------------------------
//envia info a esclavo
void EnviarInfoaEsclavo(Formato_Info Mensaje){
  
  Wire.beginTransmission(Slave_Address); /* begin with device address */
  Wire.write ((byte *) & Mensaje, sizeof Mensaje);  /* sends struct */
  Wire.endTransmission();    /* stop transmitting */

  Serial.print("Comando: ");Serial.println(Mensaje.Comando);
  Serial.print("Valor: ");Serial.println(Mensaje.Valor);
  Serial.println("------INFO ENVIADA A ESCLAVO-------");

}
 
//--------------------------------    PEDIR INFO DE ESCLAVO   ----------------------------------
void RecibirInfoDeEsclavo(Formato_Info Mensaje){
  
  // Request Data
  Wire.requestFrom(Slave_Address, sizeof Mensaje);  
  Wire.readBytes((byte*)&Mensaje, sizeof Mensaje);

  Serial.print("Comando: ");Serial.println(Mensaje.Comando);
  Serial.print("Valor: ");Serial.println(Mensaje.Valor);
  Serial.println("------MENSAJE RECIBIDO DEL SLAVE -------");

}
