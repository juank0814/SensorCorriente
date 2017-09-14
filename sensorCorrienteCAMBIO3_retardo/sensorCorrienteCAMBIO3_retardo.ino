//Aplicando Filtro a las lecturas del ACS712
//usaremos la media aritmética de varias lecturas consecutivas, 
//simplemente hay que sumar la lecturas y dividirlas en el número de muestras.
//La cantidad de muestras para calcular el promedio depende del nivel de ruido que tengan.
float Idc = 0;
float Sensibilidad=0.100;       //sensibilidad en voltios dependiendo el sensor 20A
#define ApagoCorte 8
const float umbralCorte=0.2;

void setup() {
  Serial.begin(9600);
  pinMode(ApagoCorte,OUTPUT);
 }

void loop() {
  
   Idc=calculoCorriente(100,100);    //obtenemos la corriente promedio de 10 muestras 
   Serial.print("I_Cor: ");
   Serial.println(Idc,3);              //imprimir la corriente con 3 decimales
   //delay(2000);
   
}

  float calculoCorriente(int numeroMuestras, int muestreo)
  {
    float VoltajeSensorCOR = 0;
    float intens;
    float intensidad = 0;
    float intensidadMayor=0;

     for(int j=0;j<muestreo;j++)    //VALOR MAYOR
     {
      
      /*for(int i=0;i<numeroMuestras;i++) //PROMEDIO
      {
        VoltajeSensorCOR = analogRead(A0) * (5.0/1023.0);              //lee el canal A0 y calcula el valor en tension 
        intensidad=intensidad+(VoltajeSensorCOR-2.5085)/Sensibilidad;    //calculamos corriente y sumamos
        //Serial.print("  IntensidadACUMULADA: ");
        //Serial.println(intensidad,3);
      }
      intens=intensidad/numeroMuestras;
      intensidad = abs(intens);
      */  //Se va a suspender este codigo para pruebas
      

      VoltajeSensorCOR = analogRead(A0) * (5.0/1023.0);
      
       
      if (intensidad>intensidadMayor){
        intensidadMayor=intensidad;
      }
    }
    //Serial.print("  intensidadMayor: ");
    //Serial.println(intensidadMayor,3);
   
    if( intensidadMayor >= umbralCorte){
      digitalWrite (ApagoCorte,HIGH);
    }
    else{
      digitalWrite (ApagoCorte,LOW); 
    }
    return(intensidadMayor);
}

