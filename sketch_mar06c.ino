//Departamento de informatica EESTn1 Raul Scalabrini Ortiz
//Santa Teresita - Partido de la Costa - Provincia de Buenos Aires - Argentina
//Codigo funcional de RTC para el timbre escolar 06-03-2024
// Prueba de Reloj Tiempo Real (RTC) y Modulo I2C para LCD 2x16 
// Conexion i2C :Arduino UNO  SCL-> A5   SDA->A4  VCC->5V  GND->GND
// Conexion RTC :Arduino UNO    GND->GND VCC->5V SCL-> SCL  SDA->SDA los dos pines despues del ...12,13,GND,AREF,SDA,SCL
// NOTA: se debe cargar dos veces este programa 1.Con la linea 9= RTC.adjust(DateTime(__DATE__, __TIME__));
//                                              2. Sin esa linea


#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 4);
RTC_DS1307 RTC;
void setup () {
  Wire.begin(); // Inicia el puerto I2C
  RTC.begin(); // Inicia la comunicaci¢n con el RTC
  //RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
  //el anterior se usa solo en la configuracion inicial
  Serial.begin(9600); // Establece la velocidad de datos del puerto serie
  lcd.init();
  lcd.backlight();
  lcd.clear();
}
void loop() {
  DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
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
  lcd.print(now.day(), DEC);
  lcd.print("/");
  lcd.print(now.month(), DEC);
  lcd.print("/");
  lcd.print(now.year(), DEC);
  lcd.setCursor(0, 1);
  lcd.print("HORA: ");


 if (now.hour() < 10) {
    lcd.print('0' + now.hour(), DEC);
  } else {
    lcd.print( now.hour(), DEC);
  }
  
  lcd.print(":");


  


 if (now.minute() < 10) {
    lcd.print('0' + now.minute(), DEC);
  } else {
    lcd.print( now.minute(), DEC);
  }
  
  lcd.print(":");


  if (now.second() < 10) {
    lcd.print('0' + now.second(), DEC);
  } else {
    lcd.print( now.second(), DEC);
  }

  delay(1000); // La informacion se actualiza cada 1 seg.
  lcd.setCursor(0, 0);
  lcd.print("               ");
  lcd.setCursor(0, 1);
  lcd.print("               ");

}
