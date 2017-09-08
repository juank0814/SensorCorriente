//Aplicando Filtro a las lecturas del ACS712
//usaremos la media aritmética de varias lecturas consecutivas, 
//simplemente hay que sumar la lecturas y dividirlas en el número de muestras.
//La cantidad de muestras para calcular el promedio depende del nivel de ruido que tengan.

float Sensibilidad=0.100;       //sensibilidad en voltios dependiendo el sensor 20A
float Vsensor=0;
int ApagoCorte=8;
int ApagoCoag=7;
int estadoBotonCor=0;
int estadoBotonCoag=0;
int Cor_on=2;
int Coag_on=3;

void setup() {
  Serial.begin(9600);
  pinMode(ApagoCorte,OUTPUT);
  pinMode(ApagoCoag,OUTPUT);
  pinMode(Cor_on,INPUT); //Establecemos el pin 2 BotonCorte como entrada
  pinMode(Coag_on,INPUT); //Establecemos el pin 3 BotonCoag como entrada
}

void loop() {
  float Idc=calculoCorriente(500);    //obtenemos la corriente promedio de 500 muestras 
 
  estadoBotonCor=digitalRead(Cor_on);  //almacena la lectura digital 
  if(estadoBotonCor == HIGH){
  Vsensor=analogRead(A0);
  }
   estadoBotonCoag=digitalRead(Coag_on);
  if(estadoBotonCoag == HIGH){
   Vsensor=analogRead(A1);
  }
  Serial.print("CorrienteCor: ");
  Serial.println(Idc,3);              //imprimir la corriente con 3 decimales
  delay(100);
}
float calculoCorriente(int numeroMuestras)
{
  float VoltajeSensorCOR = 0;
  float VoltajeSensorCOAG = 0;
  float intensidad = 0;
   
  for(int i=0;i<numeroMuestras;i++)                               //ciclo donde sumamos las 500 muestras
  {
    VoltajeSensorCOR = Vsensor * (5.0/1023.0);              //lee el canal A0 y calcula el valor en tension 
    intensidad=intensidad+(VoltajeSensorCOR-2.5087)/Sensibilidad;    //calculamos corriente y sumamos
  }
  intensidad=intensidad/numeroMuestras;
  if( intensidad >= 0.5){
    digitalWrite (ApagoCorte,HIGH);
  }
  else{
   digitalWrite (ApagoCorte,LOW); 
  }
  return(intensidad);
}

