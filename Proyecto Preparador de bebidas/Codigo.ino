/*
   Micro SD
   Modulo de reloj
   -Boton tactil
   -Dos relevadores
   Pantalla OLED
*/
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;
#define I2C_ADDRESS 0x3C
#define RST_PIN -1
SSD1306AsciiAvrI2c oled;

String ano;
String dia;
String mes;
String horas;
String minutos;
String segundos;
String Fecha;
String Hora;
String Bitacora;
String Imprimir;
String Nombrearchivo;

const int chipSelect = 10; //CS del modulo de memoria
const int BotonTactil = 2;
const int Bomba1 = 3;
const int Bomba2 = 4;

void setup()
{
  Serial.begin(9600);
#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0
  oled.setFont(Adafruit5x7);

  pinMode(BotonTactil, INPUT);
  pinMode(Bomba1, OUTPUT);
  pinMode(Bomba2, OUTPUT);
  RTC.begin();

  if (! RTC.isrunning())
  {
    Serial.println("RTC no está activado!");//Ajustar la fecha y hora en la que se compiló este código.

  }

  Serial.print("Inicializando tarjeta SD...");

  if (!SD.begin(chipSelect)) {
    Serial.println("No se pudo inicializar la SD, o no está conectada");
    //while (1);
  }
  else {
    Serial.println("SD inicializada!");
  }
}

void loop()
{
  ///// DESCRIPCION PANTALLA
  oled.clear();
  oled.set2X();
  oled.println("DISPENSADOR");
  oled.println("  LISTO");
  oled.println("TOCAME");
  ////////

  int estado = digitalRead(BotonTactil);
  //
  //Pantalla
  //
  if (estado == HIGH)
  {
    ////////////// NO TOCAR ESTOS AJUSTES  ///////////////////////
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
    ////////////////////////////////////////////

    oled.clear();
    oled.set2X();
    oled.println("VOY A ");
    oled.println("PREPARAR TU");
    oled.println("BEBIDA");

    digitalWrite(Bomba1, HIGH);
    digitalWrite(Bomba2, LOW);
    delay(1000);                     //Tiempo de activación de la bomba 1
    digitalWrite(Bomba1, LOW);
    digitalWrite(Bomba2, HIGH);
    delay(1000);                     //Tiempo de activación de la bomba 2
    digitalWrite(Bomba2, LOW);
    oled.clear();
    oled.set2X();
    oled.println("UN PLACER");
    oled.println("ATENDERTE");
    oled.println("ADIOS :)");
    delay(2000);
    Imprimir = Fecha + " " + Hora + " " + "TIPO DE BEBIDA:" + "AGUA CON SODA"; //MODIFICAR EL TIPO DE BEBIDA SI SE QUIERE

    File dataFile = SD.open(Bitacora, FILE_WRITE);

    // Si el archivo está disponible, escribir en el:
    if (dataFile) {
      dataFile.println(Imprimir);
      dataFile.close();
      Serial.println(Imprimir);
    }
    // Si el archivo no se puede abrir, mensaje de error:
    else {
      ///
    }
  }
}
