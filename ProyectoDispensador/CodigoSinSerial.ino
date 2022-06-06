#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <SPI.h>
#include "RTClib.h"

RTC_DS1307 RTC;
LiquidCrystal_I2C lcd(0x27, 16, 2); //CAMBIAR LA DIRECCIÓN DE LA PANTALLA

String ano;
String dia;
String mes;
String horas;
String minutos;
String segundos;
String Fecha;
String Hora;
String Bitacora;
String Imprimir0;
String Imprimir1;
String Imprimir2;
String Imprimir3;
String Nombrearchivo;

///// PINES DEL SALIDAS/////////
const int RELE = A0;
const int BUZZ = A1;
const int chipSelect = 10;
const byte Filas = 4;
const byte Cols = 4;
unsigned long db;


byte Pins_Filas[] = {9, 8, 7, 6};
byte Pins_Cols[] = {5, 4, 3, 2 };
char keypress = 0;
char Teclas [ Filas ][ Cols ] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
Keypad Teclado1 = Keypad(makeKeymap(Teclas), Pins_Filas, Pins_Cols, Filas, Cols);

void setup()
{
  pinMode(RELE , OUTPUT);
  pinMode(BUZZ , OUTPUT);
  RTC.begin();
  if (! RTC.isrunning())
  {
  }

  if (!SD.begin(10)) {
  }
  else {
  }

  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("INICIANDO");
  lcd.setCursor(3, 1);
  lcd.print("DISPENSADOR");
  delay(2000);
  lcd.clear();


  db = millis();

}

void loop()
{
  //// NO TOCAR, VARAIBLES DEL MODULO RTC + SD ////
  DateTime now = RTC.now();
  ano = now.year();
  mes = now.month();
  dia = now.day();
  horas = now.hour();
  minutos = now.minute();
  segundos = now.second();
  Fecha = ano + "/" + mes + "/" + dia;
  Hora = horas + ":" + minutos + ":" + segundos;
  Nombrearchivo = ano + mes + dia + ".txt";
  ////////////////////////////////////////////////

  char pulsacion = Teclado1.getKey() ;

  if (pulsacion != 0 && millis() - db >= 100UL)
  {
    /////     255ML
    if (pulsacion == 'A')
    {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("DESPACHANDO:");
      lcd.setCursor(5, 1);
      lcd.print("255ml");
      digitalWrite(RELE, HIGH);
      digitalWrite(BUZZ, HIGH);   //COMENTAR SI NO QUIERE QUE EL BUZZER SUENE
      delay(1000);                 //AJUSTAR TIEMPO DE ACTIVACION PARA ESTA CANTIDAD
      digitalWrite(RELE, LOW);
      digitalWrite(BUZZ, LOW);
      lcd.setCursor(3, 1);
      lcd.print("ADIOS...");
      delay(500);
      lcd.clear();
      Imprimir0 = Fecha + " " + Hora + " " + "Cantidad:" + "225" + "ml";

      File dataFile = SD.open(Bitacora, FILE_WRITE);

      if (dataFile) {
        dataFile.println(Imprimir0);
        dataFile.close();
      }
      else {
      }
    }
    else if (pulsacion == 'B') //Prende
    {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("DESPACHANDO:");
      lcd.setCursor(5, 1);
      lcd.print("600ml");
      digitalWrite(RELE, HIGH);
      digitalWrite(BUZZ, HIGH);   //COMENTAR SI NO QUIERE QUE EL BUZZER SUENE
      delay(1000);                 //AJUSTAR TIEMPO DE ACTIVACION PARA ESTA CANTIDAD
      digitalWrite(RELE, LOW);
      digitalWrite(BUZZ, LOW);
      lcd.setCursor(3, 1);
      lcd.print("ADIOS...");
      delay(1000);
      lcd.clear();
      Imprimir1 = Fecha + " " + Hora + " " + "Cantidad:" + "600" + "ml";

      File dataFile = SD.open(Bitacora, FILE_WRITE);

      // Si el archivo está disponible, escribir en el:
      if (dataFile) {
        dataFile.println(Imprimir1);
        dataFile.close();
      }
      else {
      }
    }
    else if (pulsacion == 'C') //Parpadero 500ms
    { lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("DESPACHANDO:");
      lcd.setCursor(3, 1);
      lcd.print("1000 ml");
      digitalWrite(RELE, HIGH);
      digitalWrite(BUZZ, HIGH);   //COMENTAR SI NO QUIERE QUE EL BUZZER SUENE
      delay(2000);                 //AJUSTAR TIEMPO DE ACTIVACION PARA ESTA CANTIDAD
      digitalWrite(RELE, LOW);
      digitalWrite(BUZZ, LOW);
      lcd.setCursor(3, 1);
      lcd.print("ADIOS...");
      delay(1000);
      lcd.clear();
      Imprimir2 = Fecha + " " + Hora + " " + "Cantidad:" + "1000" + "ml";

      File dataFile = SD.open(Bitacora, FILE_WRITE);

      if (dataFile) {
        dataFile.println(Imprimir2);
        dataFile.close();
      }
      else {
      }
    }
    else if (pulsacion == 'D') //Parpadero 1000ms
    { lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("DESPACHANDO:");
      lcd.setCursor(3, 1);
      lcd.print("2000 ml");
      digitalWrite(RELE, HIGH);
      digitalWrite(BUZZ, HIGH);   //COMENTAR SI NO QUIERE QUE EL BUZZER SUENE
      delay(3000);                 //AJUSTAR TIEMPO DE ACTIVACION PARA ESTA CANTIDAD
      digitalWrite(RELE, LOW);
      digitalWrite(BUZZ, LOW);
      lcd.setCursor(3, 1);
      lcd.print("ADIOS...");
      delay(1000);
      lcd.clear();
      Imprimir3 = Fecha + " " + Hora + " " + "Cantidad:" + "2000" + "ml";

      File dataFile = SD.open(Bitacora, FILE_WRITE);

      // Si el archivo está disponible, escribir en el:
      if (dataFile) {
        dataFile.println(Imprimir3);
        dataFile.close();
      }
      else {
      }
    }
    
    else if (pulsacion != 'A' or pulsacion != 'B' or pulsacion != 'C' or pulsacion != 'D' ) {

      lcd.clear();
      lcd.setCursor(8, 0);
      lcd.print("INTENTE");
      lcd.setCursor(4, 1);
      lcd.print("NUEVAMENTE ");
      digitalWrite(BUZZ, HIGH);  
      delay(200);
      digitalWrite(BUZZ, LOW);  
      delay(100);  
      digitalWrite(BUZZ, HIGH);  
      delay(200);
      digitalWrite(BUZZ, LOW);  
      delay(100);
      digitalWrite(BUZZ, HIGH);  
      delay(200);
      digitalWrite(BUZZ, LOW);  
      delay(2000);
    }

    db = millis();
  }
  else {
    lcd.setCursor(1, 0);
    lcd.print("PRESIONE LA");
    lcd.setCursor(1, 1);
    lcd.print("TECLADESEADA");
  }
}
