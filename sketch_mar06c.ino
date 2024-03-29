//Departamento de informatica EESTn1 Raul Scalabrini Ortiz
//Santa Teresita - Partido de la Costa - Provincia de Buenos Aires - Argentina
//https://github.com/juanreichert/timbre-escolar
// Con Arduino UNO,(RTC), Modulo Rele, Modulo I2C para LCD 2x16 
// Conexion i2C :Arduino UNO  SCL-> A5   SDA->A4  VCC->5V  GND->GND
// Conexion RTC :Arduino UNO    GND->GND VCC->5V SCL-> SCL  SDA->SDA los dos pines despues del ...12,13,GND,AREF,SDA,SCL
// Conexion Rele:Arduino UNO GND->GND  VCC->5V  IN->7
// NOTA: se debe cargar dos veces este programa 1. Con la linea  RTC.adjust(DateTime(__DATE__, __TIME__)); 
//                                              2. Sin esa linea

#include <Wire.h> 
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,4); // inicializa la interfaz I2C del LCD 16x2
RTC_DS1307 RTC;                   // inicializa el modulo RTC
int r_diaSemana;                  // almacena el resultado del dia de la semana calculado
const int timbre = 7;             // Pin 7 encargado de activar el timbre, se conecta al Rele
int segundo;
int minuto;
int hora;
int tiempo_timbre=90000; // Tiempo continuo que dura el timbre sonando, en milisegundos 5000 = 5 segundos

//////////////////////////////// Horario 1 /////////////////////////
// Hora en la que suena el timbre escrito  h1=Hora, m1=Minutos, s1=Segundos
// Cuando no se programa ninguna hora se debe dejar escrito el numero 99  
// se pueden programar 16 timbres por cada horario, _c1 indica que es el horario 1
int h1_c1=23;   int m1_c1=17;   int s1_c1=0;
int h2_c1=23;   int m2_c1=18;  int s2_c1=0;
int h3_c1=23;   int m3_c1=22;  int s3_c1=0;
int h4_c1=19;   int m4_c1=38;  int s4_c1=0;
int h5_c1=19;   int m5_c1=32;  int s5_c1=0;
int h6_c1=19;  int m6_c1=33;  int s6_c1=0;
int h7_c1=19;  int m7_c1=34;  int s7_c1=0;
int h8_c1=11;  int m8_c1=15;  int s8_c1=0;
int h9_c1=12;  int m9_c1=00;  int s9_c1=0;
int h10_c1=99; int m10_c1=0;  int s10_c1=0;
int h11_c1=99; int m11_c1=0;  int s11_c1=0;
int h12_c1=99; int m12_c1=0;  int s12_c1=0;
int h13_c1=99; int m13_c1=0;  int s13_c1=0;
int h14_c1=99; int m14_c1=0;  int s14_c1=0;
int h15_c1=99; int m15_c1=0;  int s15_c1=0;
int h16_c1=99; int m16_c1=0;  int s16_c1=0;
int h17_c1=99; int m17_c1=0;  int s17_c1=0;
int h18_c1=99; int m18_c1=0;  int s18_c1=0;
int h19_c1=99; int m19_c1=0;  int s19_c1=0;
int h20_c1=99; int m20_c1=0;  int s20_c1=0;




//reinicio de arduino
 void(* resetSoftware)(void) = 0;
////////////////////////////////// Void Setup() ///////////
void setup () { 
  
 pinMode(timbre, OUTPUT);                    // Configura como salida el pin 7
 Wire.begin();                               
 RTC.begin();                                // Inicia la comunicaci¢n con el RTC
 
//RTC.adjust(DateTime(__DATE__, __TIME__)); // Lee la fecha y hora del PC (Solo en la primera carga)

                                             // el anterior se usa solo en la configuracion inicial luego se pone como comentario
                                             // y se vuelve a cargar el programa sin esa linea.
 Serial.begin(9600);                         // Establece la velocidad de datos del puerto serie a 9600
 lcd.init();
 lcd.backlight();                            // Coloca luz de fondo al LCD
 lcd.clear();                                // Borra el  LCD
} 
////////////////////////////////// Void loop() ///////////
void loop(){
 DateTime now = RTC.now();          // Obtiene la fecha y hora del RTC
 
 int contacto1 = 1200; //seteado manualmente porque no usamos selectores
 //int contacto1 = analogRead(A0);    //Lee el valor de los contactos para escoger el horario
 int contacto2 = analogRead(A1);
 int contacto3 = analogRead(A2);
 int contacto4 = analogRead(A3);    // contacto que activa o desactiva los fines de semana

  Serial.print(now.day(), DEC); // Dia
  Serial.print('/');
  Serial.print(now.month(), DEC); // Mes
  Serial.print('/');
  Serial.print(now.year(), DEC); // Anio
  Serial.print(' ');
  Serial.print(now.hour(), DEC); // Horas
  Serial.print(':');
  Serial.print(now.minute(), DEC); // Minutos
  Serial.print(':');
  Serial.print(now.second(), DEC); // Segundos
 Serial.println();

  lcd.setCursor(0, 0);
  lcd.print("FECHA:");
  lcd.print(' ');
  lcd.setCursor(11, 0);
  lcd.print(now.day(), DEC);
  lcd.print("/");
  lcd.print(now.month(), DEC);
  lcd.print("/");
  lcd.print(now.year(), DEC);
  lcd.setCursor(0, 1);
  lcd.print("HORA: ");
 lcd.print(now.hour(), DEC);
 lcd.print(":");
 lcd.print(now.minute(), DEC);
// lcd.print(":");
//   if (now.second() < 10) {
//    lcd.print('0' + now.second(), DEC);
//  } else {
//    lcd.print( now.second(), DEC);
//  }
 segundo=now.second();
 minuto=now.minute();
 hora=now.hour();

 if (contacto4 <= 1000){     // si el contacto 4 esta desactivado, despliega -e- entre semana funciona el timbre
    lcd.setCursor(16,0);
    //lcd.print("e");
    Serial.print("-e-"); 
 }
 else {                      // si el contacto 4 esta activado, despliega -F- el Fin de semana funciona el timbre
   lcd.setCursor(12,0);
  // lcd.print("F");
   Serial.print("-F-");
 }
 
 int r_diaSemana=dia_de_semana();   // llama a la funcion que calcula el dia de la semana y lo almacena en r_diaSemana
 
 if ((r_diaSemana == 6 || r_diaSemana == 0)&&(contacto4 <= 1000)){  // si el contacto4 de Fin de semana esta apagado y es fin de semana no hace nada
 }
 else {
   if (contacto1 >= 1000)   // Si el contacto 1 esta activo (Horario 1)    
     horario_1();           // llama a la funcion que activa el horario 1

//   if (contacto2 >= 1000)  // Si el contacto 2 esta activo (Horario 2)
//     horario_2();          // llama a la funcion que activa el horario2
//
//   if (contacto3 >= 1000)  // Si el contacto 1 esta activo (Horario 3)
//     horario_3();          // llama a la funcion que activa el horario 3
 }
 
 digitalWrite(timbre, LOW);     // apaga el timbre
 delay(500);                    // La informaci¢n se actualiza cada 1/2 seg.
 lcd.setCursor(9,0);            // Borra parte de la pantalla del LCD
 lcd.print("                ");
 lcd.setCursor(8,1);
 lcd.print("                ");
}   //////////////////////////////// Fin del void loop(), inician las Funciones/////////////////////////

/////////////////////////////// Funcion que activa el Timbre //////////////////////////////////
void activar_timbre(){
    digitalWrite(timbre, HIGH); 
    lcd.setCursor(0,0);
    lcd.print("SONANDO  ");
    Serial.println("Timbre Activo");
    delay(tiempo_timbre);
    resetSoftware(); 
}
/////////////////////////////// Calcula el dia de la Semana //////////////////////////////////
int dia_de_semana(){
 // Encuentar el dia de la semana de una fecha
 int n_dia;
 int r_dia;
 int n_mes;
 int t_mes;
 int n_anno;
 int d_anno;
 int t_siglo=6;

 DateTime now = RTC.now(); //fecha y hora del RTC
 lcd.setCursor(7,0);

 n_anno=(now.year()-2000);
 d_anno=n_anno/4;
 n_dia=now.day();
 n_mes=now.month();

 switch (n_mes) {
    case 1:
      t_mes=0;
      break;
    case 2:
      t_mes=3;
      break;
    case 3:
      t_mes=3;
      break;
    case 4:
      t_mes=6;
      break;
    case 5:
      t_mes=1;
      break;
    case 6:
      t_mes=4;
      break;
    case 7:
      t_mes=6;
      break;
    case 8:
      t_mes=2;
      break;
    case 9:
      t_mes=5;
      break;
    case 10:
      t_mes=0;
      break;
    case 11:
      t_mes=3;
      break;
    case 12:
      t_mes=5;
      break;
    default: 
      t_mes=t_mes;
    break;
 }

 r_dia=n_dia+t_mes+n_anno+d_anno+t_siglo;
 r_dia = r_dia % 7;

 switch (r_dia) {
    case 1:
       lcd.print("Lun");
        Serial.print(" Lun ");
      break;
      case 2:
       lcd.print("Mar");
       Serial.println(" Mar ");
      break;
      case 3:
       lcd.print("Mie");
       Serial.print(" Mie ");
      break;
      case 4:
       lcd.print("Jue");
       Serial.print(" Jue ");
      break;
      case 5:
       lcd.print("Vie");
       Serial.print(" Vie ");
      break;
      case 6:
       lcd.print("Sab");
       Serial.print(" Sab ");
      break;
      case 0:
       lcd.print("Dom");
       Serial.print(" Dom ");
      break;
      default: 
       lcd.print("---");
       Serial.print(" ---");
      break;
 } 
 return r_dia; 
}

/////////////////////Condicional del Horario 1  //////////////////////////////////
void horario_1(){ 
//   lcd.setCursor(13,0);
//   lcd.print("1");
   Serial.print("Horario_1 ");
   if ((hora==h1_c1) && (minuto==m1_c1) && (segundo==s1_c1))  activar_timbre();
   if ((hora==h2_c1) && (minuto==m2_c1) && (segundo==s2_c1))  activar_timbre();
   if ((hora==h3_c1) && (minuto==m3_c1) && (segundo==s3_c1))  activar_timbre();
   if ((hora==h4_c1) && (minuto==m4_c1) && (segundo==s4_c1))  activar_timbre();
   if ((hora==h5_c1) && (minuto==m5_c1) && (segundo==s5_c1))  activar_timbre();
   if ((hora==h6_c1) && (minuto==m6_c1) && (segundo==s6_c1))  activar_timbre();
   if ((hora==h7_c1) && (minuto==m7_c1) && (segundo==s7_c1))  activar_timbre();
   if ((hora==h8_c1) && (minuto==m8_c1) && (segundo==s8_c1))  activar_timbre();
   if ((hora==h9_c1) && (minuto==m9_c1) && (segundo==s9_c1))  activar_timbre();
   if ((hora==h10_c1) && (minuto==m10_c1) && (segundo==s10_c1))  activar_timbre();
   if ((hora==h11_c1) && (minuto==m11_c1) && (segundo==s11_c1))  activar_timbre();
   if ((hora==h12_c1) && (minuto==m12_c1) && (segundo==s12_c1))  activar_timbre();
   if ((hora==h13_c1) && (minuto==m13_c1) && (segundo==s13_c1))  activar_timbre();
   if ((hora==h14_c1) && (minuto==m14_c1) && (segundo==s14_c1))  activar_timbre();
   if ((hora==h15_c1) && (minuto==m15_c1) && (segundo==s15_c1))  activar_timbre();
   if ((hora==h16_c1) && (minuto==m16_c1) && (segundo==s16_c1))  activar_timbre();
   if ((hora==h17_c1) && (minuto==m17_c1) && (segundo==s17_c1))  activar_timbre();
   if ((hora==h18_c1) && (minuto==m18_c1) && (segundo==s18_c1))  activar_timbre();
   if ((hora==h19_c1) && (minuto==m19_c1) && (segundo==s19_c1))  activar_timbre();
   if ((hora==h20_c1) && (minuto==m20_c1) && (segundo==s20_c1))  activar_timbre();     
}
