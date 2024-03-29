/*
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#include <SD.h>
#include <SPI.h>
#include "RTClib.h"

#define I2C_ADDRESS 0x3C
#define RST_PIN -1
RTC_DS1307 RTC;

SSD1306AsciiAvrI2c oled;
const int MQ_PIN = 2;                         //Pin del sensor de Alcohol
const int MQ_DELAY = 2000;

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

const int chipSelect = 10;

void setup(void) {
#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif

  oled.setFont(Adafruit5x7);
  oled.clear();
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    while (1);
  }
  nfc.setPassiveActivationRetries(0xFF);
  nfc.SAMConfig();

  RTC.begin();
  SD.begin(chipSelect);

  }
  void loop(void) {
    boolean success;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
    uint8_t uidLength;
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
    DateTime now = RTC.now();
    ano = now.year();
    mes = now.month();
    dia = now.day();
    horas = now.hour();
    minutos = now.minute();
    segundos = now.second();
    Fecha = ano + "/" + mes + "/" + dia;
    Hora = horas + ":" + minutos + ":" + segundos;
    /////////////////////////////////////////////
    Nombrearchivo = ano + mes + dia + ".txt";
    /////////////////////////////////////////////
    if (success) {
      bool state = digitalRead(MQ_PIN);                                                               
      String hex_value = "";
      for (uint8_t i = 0; i < uidLength; i++)
      {
        hex_value += (String)uid[i];
      }


      if (!state) {
        Imprimir = Fecha + " " + Hora + " " + "UID: " + hex_value  + "Estado: " + "Positivo";
        File dataFile = SD.open(Bitacora, FILE_WRITE);

        // Si el archivo está disponible, escribir en el:
        if (dataFile) {
          dataFile.println(Imprimir);
          dataFile.close();
        }
        else {
        }

        oled.clear();
        oled.set2X();
        oled.println(" NO \nAprobado");
      }
      else
      {
        /////////////////////////////////////////////
        Imprimir = Fecha + " " + Hora + " " + "UID: " + hex_value  + "Estado: " + "Negativo";
        File dataFile = SD.open(Nombrearchivo, FILE_WRITE);
        if (dataFile) {
          dataFile.println(Imprimir);
          dataFile.close();
        }
        else {
        }
      }
    }
    else
    {
      oled.clear();
      oled.println("BIENVENIDO");
      oled.set2X();
      oled.println("\nACERQUE SU \nTARJETA");
      oled.println("\nAcerquese al sensor");

    }
  }*/
