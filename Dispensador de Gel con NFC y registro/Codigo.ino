#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#include "SSD1306AsciiWire.h"

#include "Adafruit_MLX90614.h"
#include <SD.h>
#include <SPI.h>
#include "RTClib.h"

RTC_DS1307 RTC;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();  ///////////////
#define I2C_ADDRESS 0x3C
#define RST_PIN -1
SSD1306AsciiWire oled;
int i = 0;
const int sensorPin = 9;               //Pin digital 15 Modulo TACTIL
const int rele = 8;                     //Pin digital 2 para RELEVADOR
const int Trigger = 2;                  //Pin digital 2 para el Trigger del sensor
const int Echo = 3;                     //Pin digital 3 para el Echo del sensor
const int chipSelect = 10;              //Pin del CS del modulo SD
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
void setup(void) {
  Wire.begin();
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
  nfc.begin();
  mlx.begin();
  RTC.begin();
  SD.begin(chipSelect);
  pinMode(sensorPin, INPUT);
  pinMode(rele, OUTPUT);
  pinMode(Trigger, OUTPUT);             //pin como salida TRIG
  pinMode(Echo, INPUT);                 //pin como entrada ECHO
  digitalWrite(Trigger, LOW);           //Inicializamos el pin con 0

  nfc.setPassiveActivationRetries(0xFF);
  nfc.SAMConfig();
  oled.setFont(Adafruit5x7);
  digitalWrite(rele, HIGH); //Mantener el rele apagado desde su inicio
  oled.clear();
  oled.set2X();
  oled.println("***********");
  oled.println("INICIANDO \nDISPENSADOR \n DE GEL...");
  oled.println("");
  delay(1000);
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
  Nombrearchivo = ano + mes + dia + ".txt";

  if (success) {
    String hex_value = "";
    for (uint8_t i = 0; i < uidLength; i++)
    {
      hex_value += (String)uid[i];
    }
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("...ID...");
    oled.println("DETECTADA");
    oled.println("***********");
    delay(800);
    oled.clear();
    oled.set2X();
    oled.println("  TOMARE \n   SU\nTEMPERATURA");
    delay(3000);
    oled.clear();
    oled.print("TEMPERARUTA:\n");
    oled.print(    mlx.readObjectTempC());  //////////////
    //oled.println("    30");
    oled.println("\n GRADOS C");
    delay(2000);
    oled.clear();
    oled.println("***********");
    oled.println("   GEL?");
    oled.println("COLOQUE SU\n  MANO");
    //oled.println("***********");
    delay(3000);
    int estado = digitalRead(sensorPin);
    long t;                                  //tiempo que demora en llegar el eco
    long d;                                  //distancia en centimetros
    long x;
    digitalWrite(Trigger, HIGH);
    delayMicroseconds(10);                   //Enviamos un pulso de 10us
    digitalWrite(Trigger, LOW);
    t = pulseIn(Echo, HIGH);                //obtenemos el ancho del pulso
    d = t / 59;
    x = d;

    if (estado == HIGH && x <= 10) {
      oled.clear();
      oled.set2X();
      oled.println("***********");
      oled.println("DESPACHANDO\n  GEL\n   :) ");
      digitalWrite(rele, LOW);       //Activa relevador para despachar el gel
      delay(3000);                     //Tiempo de activación
      digitalWrite(rele, HIGH);        //Descativa relevador para despachar el gel
      delay(200);
      Imprimir1 = Fecha + " " + Hora + " " + "UID" + hex_value + "Temperatura: " + mlx.readObjectTempC() + ""  + " GEL: " + " SI"; /////
      File dataFile = SD.open(Nombrearchivo, FILE_WRITE);

      if (dataFile) {
        dataFile.println(Imprimir1);
        dataFile.close();
        oled.clear();
        oled.set2X();
        oled.println("***********");
        oled.println("  ADIOS .... ");
        oled.println("***********");
      }
      else {
        /*
        oled.clear();
        oled.set2X();
        oled.println("   ERROR \n    DE\n REGISTRO\n    :(");
        delay(2000);
        */
        oled.clear();
        oled.println("***********");
        oled.println("  ADIOS .... ");
        oled.println("***********");
        delay(1000);

      }
    }
    else {
      oled.clear();
      oled.set2X();
      oled.println("***********");
      oled.println("  NO QUISO\n  GEL :( ");
      oled.println("***********");
      delay(3000);
      oled.clear();
      oled.set2X();
      oled.println("***********");
      oled.println("  ADIOS .... ");
      oled.println("***********");
      delay(3000);
      File dataFile = SD.open(Nombrearchivo, FILE_WRITE);
      Imprimir = Fecha + " " + Hora + " " + "UID" + hex_value + "Temperatura: " + mlx.readObjectTempC()  + "GEL: " + "NO";    //

      if (dataFile) {
        dataFile.println(Imprimir);
        dataFile.close();

      }
      else {
        /*
        oled.clear();
        oled.set2X();
        oled.println("   ERROR \n    DE\n REGISTRO\n    :(");
        delay(2000);
        */
        oled.clear();
        oled.println("***********");
        oled.println("  ADIOS .... ");
        oled.println("***********");
        delay(1000);
      }
    }
    delay(500);
  }
  else {
    digitalWrite(rele, HIGH); 
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("ACERQUE SU \nCREDENCIAL");
    oled.println("***********");
    oled.set2X();
    delay(500);


  }
}
