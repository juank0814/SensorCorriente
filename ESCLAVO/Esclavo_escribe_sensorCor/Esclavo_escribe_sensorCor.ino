//Aplicando Filtro a las lecturas del ACS712
//usaremos la media aritmética de varias lecturas consecutivas, 
//simplemente hay que sumar la lecturas y dividirlas en el número de muestras.
//La cantidad de muestras para calcular el promedio depende del nivel de ruido que tengan.

#include <Wire.h>         //libreria para comunicacion I2C

#define ApagoCorte 8 
#define ApagoCoag 7

float Sensibilidad=0.100;       //sensibilidad en voltios dependiendo el sensor 20A
//float Idc;
//float IdcCoag;
byte Corte;
byte Coag;
byte Dato_Corriente = 0x00;
byte Base;

void setup() {
  Serial.begin(9600);
  Wire.begin(7);                  //unirse al bus I2C con la dirección # 7
  Wire.onRequest(requestSens);    
  
  pinMode(ApagoCorte,OUTPUT);
  pinMode(ApagoCoag,OUTPUT);
}

void loop() {
  float Idc=CORTE_C_REQUEST(500);               //obtenemos la corriente promedio de 500 muestras 
  float IdcCoag=COAG_C_REQUEST(500);            //obtenemos la corriente promedio de 500 muestras
  Salida_Corriente();
  delay(200);
}
//función que se ejecuta cuando los datos son solicitados por el maestro
// esta función está registrada como un evento, vea setup ()

float CORTE_C_REQUEST(int numeroMuestras)
{
  float VoltajeSensorCOR = 0;
  float intensidad_Cor = 0;

  for(int i=0;i<numeroMuestras;i++)                     //ciclo donde sumamos las 500 muestras
  {
    VoltajeSensorCOR = analogRead(A3) * (5.0/1023.0);              //lee el canal A0 y calcula el valor en tension 
    intensidad_Cor=intensidad_Cor+(VoltajeSensorCOR-2.5087)/Sensibilidad;    //calculamos corriente y sumamos
  }
  intensidad_Cor=intensidad_Cor/numeroMuestras;
  if( intensidad_Cor >= 0.1){
    digitalWrite (ApagoCorte,HIGH);
    Corte =0x02;
  }
  else{
   digitalWrite (ApagoCorte,LOW);
   Corte =0x00; 
  }
  return(intensidad_Cor);
}

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////COAGULACION ////////////////////////////////////////////

  float COAG_C_REQUEST(int numeroMuestras1)
{
  float VoltajeSensorCOAG = 0;
  float intensidad_Coag = 0;
 
  for(int j=0;j<numeroMuestras1;j++)                               //ciclo donde sumamos las 500 muestras
  {
    VoltajeSensorCOAG = analogRead(A2) * (5.0/1023.0);              //lee el canal A1 y calcula el valor en tension 
    intensidad_Coag=intensidad_Coag+(VoltajeSensorCOAG-2.497)/Sensibilidad;    //calculamos corriente y sumamos
  }
  intensidad_Coag=intensidad_Coag/numeroMuestras1;
  if( intensidad_Coag >= 0.1){
    digitalWrite (ApagoCoag,HIGH);
    Coag = 0x01;
  }
  else{
   digitalWrite (ApagoCoag,LOW);
   Coag = 0x00; 
  }
return(intensidad_Coag);
}

void requestSens ()
{
  Wire.write(Dato_Corriente); //responder con mensaje de 6 bytes como esperaba el maestro
}

void Salida_Corriente ()
{
  Dato_Corriente =  (Corte|Coag)|Base; 
}


