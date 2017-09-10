//sensor de corriente 
#include <Wire.h>

void setup() {
  Wire.begin();        // activar el bus I2C (dirección opcional para el maestro)
  Serial.begin(9600);  // inicio serial para salida
}

void loop() {
  Wire.requestFrom(7, 1);    // solicita 1 byte del dispositivo esclavo # 7

  while (Wire.available()) { // esclavo puede enviar menos de lo solicitado
    byte sensadoCorriente = Wire.read(); // recibe un byte como carácter
    Serial.println(sensadoCorriente, BIN);        // imprimir el carácter
  }

  delay(500);
}
