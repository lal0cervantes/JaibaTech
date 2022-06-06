#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <SPI.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#include <SD.h>
#include "RTClib.h"

#define I2C_ADDRESS 0x3C
#define RST_PIN -1

#define Sober 120   // Define valor Max para sobrio
#define Drunk 400   // Define valor Min para Ebrio

#define MQ3pin 0      //PIN del MQ3
float sensorValue;
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
SSD1306AsciiAvrI2c oled;

RTC_DS1307 RTC;
String ano;
String dia;
String mes;
String horas;
String minutos;
String segundos;
String Fecha;
String Hora;
String Bitacora;
String Nombrearchivo;
String Imprimir;
String Imprimir1;
const int chipSelect = 10;    /////////Pin del CS del modulo
void setup(void) {
#ifdef __DEBUG__
  delay(100);
#endif

#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif

  oled.setFont(Adafruit5x7);
  oled.clear();
  oled.set2X();
  oled.println("BIENVENIDO");
  oled.set1X();

  nfc.begin();

  RTC.begin();
  SD.begin(chipSelect);
}

void loop(void) {
  DateTime now = RTC.now();
  ano = now.year();
  mes = now.month();
  dia = now.day();
  horas = now.hour();
  minutos = now.minute();
  segundos = now.second();
  Fecha = ano + "/" + mes + "/" + dia;
  Hora = horas + ":" + minutos + ":" + segundos;
  Nombrearchivo = dia + mes + ano + ".txt";
  if (nfc.tagPresent()) {
    NfcTag tag = nfc.read();
    oled.clear();
    oled.set2X();
    oled.println("TARJETA\nENCONTRADA");
    oled.set1X();
    oled.println("Tu ID: es\n");
    oled.println(tag.getUidString());
    delay(1000);
    oled.clear();
    oled.set2X();
    oled.println("PREPARATE\nPARA\nSOPLAR");
    oled.set1X();
    delay(1000);
    sensorValue = analogRead(MQ3pin);
    if (sensorValue < Sober) {
      //Serial.println("ESTADO SOBRIO");
      oled.clear();
      oled.set2X();
      oled.println("ESTADO:\nSOBRIO");
      oled.set1X();
      Imprimir = Fecha + " " + Hora + " " + "UID: " + tag.getUidString()  + " Estado: " + "SOBRIO";
      File dataFile = SD.open(Nombrearchivo, FILE_WRITE);
      if (dataFile) {
        dataFile.println(Imprimir);
        dataFile.close();
      }
      else {
      }
    } else if (sensorValue >= Sober && sensorValue < Drunk) {
      //Serial.println("ESTADO DENTRO DEL LIMITE LEGAL");
      oled.clear();
      oled.set2X();
      oled.println("ESTADO:\nCONSULTAR\nAUTORIZACION");
      oled.set1X();
    } else {
      //Serial.println("EBRIO");
      oled.clear();
      oled.set2X();
      oled.println("ESTADO:\nEBRIO");
      oled.set1X();
      Imprimir1 = Fecha + " " + Hora + " " + "UID: " + tag.getUidString()  + " Estado: " + "EBRIO";
      File dataFile = SD.open(Nombrearchivo, FILE_WRITE);
      if (dataFile) {
        dataFile.println(Imprimir1);
        dataFile.close();
      }
      else {
      }
    }
  }
  else {
    oled.clear();
    oled.println("HOLA");
    oled.set2X();
    oled.println("\nACERCA TU \nTARJETA");
    oled.set1X();
  }

  delay(2000);
}
