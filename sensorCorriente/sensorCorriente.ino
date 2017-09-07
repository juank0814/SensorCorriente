float Sensibilidad=0.100;       //sensibilidad en voltios dependiendo el sensor 20A
int apagocorte=8;
void setup() {
  Serial.begin(9600);
  pinMode(apagocorte,OUTPUT);
}

void loop() {
  float Idc=calculoCorriente(500);    //obtenemos la corriente promedio de 500 muestras 
  Serial.print("Corriente: ");
  Serial.println(Idc,3);              //imprimir la corriente con 3 decimales
  delay(100);
}
float calculoCorriente(int numeroMuestras)
{
  float leerAcs712 = 0;
  float intensidad = 0;
  for(int i=0;i<numeroMuestras;i++)
  {
    leerAcs712 = analogRead(A0) * (5.0/1023.0);              //lee el canal A0 y calcula el valor en tension 
    intensidad=intensidad+(leerAcs712-2.5)/Sensibilidad;    //calculamos corriente y sumamos
  }
  intensidad=intensidad/numeroMuestras;
  if( intensidad >= 0.5){
    digitalWrite (apagocorte,HIGH);
  }
  else{
   digitalWrite (apagocorte,LOW); 
  }
  return(intensidad);
  
  
}

