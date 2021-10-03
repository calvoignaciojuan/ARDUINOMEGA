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
void EventoAlRecibirInfo(int MessageSize);  //funcion que se ejecuta cuando recibo datos por IIC
void EventoAlPedirmeInfo();

void setup() {

  Serial.begin(9600);

  Wire.begin(Slave_Address);    /* join i2c bus with address*/
  delay(50);          
  Wire.onReceive(EventoAlRecibirInfo); /* register receive event */
  Wire.onRequest(EventoAlPedirmeInfo); /* register request event */
}

void loop() {
 
}


// function that executes whenever data is received from master
void EventoAlRecibirInfo(int MessageSize) {
  
  Wire.readBytes((byte*)& Mensaje, sizeof Mensaje); //guarda en variable mensaje lo recibido

  Serial.print("Comando: ");Serial.println(Mensaje.Comando);
  Serial.print("Valor: ");Serial.println(Mensaje.Valor);
  Serial.println("------RECEPCION TERMINADA-------");
}

// function that executes whenever data is requested from master
void EventoAlPedirmeInfo() {
 
  Mensaje.Comando=2;
  Mensaje.Valor=Mensaje.Valor*2; //multiplica por 2 el valor recibido, como para darme cuenta que esta cambiando algo

  Wire.write((byte *) & Mensaje, sizeof Mensaje);  /*send string on request */
}
