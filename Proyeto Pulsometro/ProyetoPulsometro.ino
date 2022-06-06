#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

#define I2C_ADDRESS 0x3C
#define RST_PIN -1
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"

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
String Imprimir;
String Nombrearchivo;

const int chipSelect = 10;
const int BUZZ = 5;


SSD1306AsciiAvrI2c oled;

void setup(void) {
  attachInterrupt( 0, finalCarrera, FALLING);     //Pin 2 FINAL DE CARRERA
  attachInterrupt( 1, botonPierdes, FALLING);   //Pin 3 POR SI PIERDES
  pinMode(BUZZ, OUTPUT);

  Serial.begin(115200);
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
#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif
  Serial.println("HOLA!");

  oled.setFont(Adafruit5x7);
  oled.clear();

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("No encontre el Sensor NFC");
    while (1); // halt
  }

  nfc.setPassiveActivationRetries(0xFF);

  // configure board to read RFID tags
  nfc.SAMConfig();

  Serial.println("Esperando una Tarjeta");
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
  Nombrearchivo = ano + mes + dia + ".txt";

  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  if (success) {

    String hex_value = "";
    for (uint8_t i = 0; i < uidLength; i++)
    {
      hex_value += (String)uid[i];
    }

    Serial.println("vALOR=" + hex_value);
    ///////////////////MENSAJE DE BIENVENIDA ///////////////

    ///  GUARDAR REGISTRO DEL JUGADOR    ///
    Imprimir = Fecha + " " + Hora + " " + " JUGADOR"  + hex_value;

    File dataFile = SD.open(Bitacora, FILE_WRITE);

    // Si el archivo está disponible, escribir en el:
    if (dataFile) {
      dataFile.println(Imprimir);
      dataFile.close();
      oled.clear();
      oled.set2X();
      oled.println("***********");
      oled.println(" USUARIO");
      oled.println("REGISTRADO");
      oled.println("***********");
      delay(1000);
    }

    else {
      ///// Si el archivo no se puede abrir
      oled.clear();
      oled.set2X();
      oled.println("***********");
      oled.println(" USUARIO");
      oled.println("REGISTRADO");
      oled.println("***********");
      delay(1000);
    }
    //////////// TERMINA GUARDADO DE ARCHIVO ///////////////////////////
    oled.clear();
    oled.set2X();
    oled.println("   HEY!");
    oled.println("  VAMOS A");
    oled.println("  JUGAR");
    oled.println("***********");
    delay(1500);
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("EL JUEGO");
    oled.println("COMIENZA EN");
    oled.println("*** 10 ***");
    delay(1000);
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("EL JUEGO");
    oled.println("COMIENZA EN");
    oled.println("*** 9 ***");
    delay(1000);
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("EL JUEGO");
    oled.println("COMIENZA EN");
    oled.println("*** 8 ***");
    delay(1000);
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("EL JUEGO");
    oled.println("COMIENZA EN");
    oled.println("*** 7 ***");
    delay(1000);
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("EL JUEGO");
    oled.println("COMIENZA EN");
    oled.println("*** 6 ***");
    delay(1000);
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("EL JUEGO");
    oled.println("COMIENZA EN");
    oled.println("*** 5 ***");
    delay(1000);
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("EL JUEGO");
    oled.println("COMIENZA EN");
    oled.println("*** 4 ***");
    delay(1000);
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("EL JUEGO");
    oled.println("COMIENZA EN");
    oled.println("*** 3 ***");
    delay(1000);
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("EL JUEGO");
    oled.println("COMIENZA EN");
    oled.println("*** 2 ***");
    delay(1000);
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("EL JUEGO");
    oled.println("COMIENZA EN");
    oled.println("*** 1  ***");
    delay(1000);
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("EL JUEGO");
    oled.println("COMIENZA EN");
    oled.println("AHORA!");
    delay(1000);
    digitalWrite(BUZZ, HIGH);
    delay(2000);
    digitalWrite(BUZZ, LOW);
    delay(100);
    ///
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("TIENES 30");
    oled.println("SEGUNDOS");
    oled.println("***********");
    delay(30000);

    ///
    oled.clear();
    oled.set2X();
    oled.println("***********");
    oled.println("HEY, :(");
    oled.println("PERDISTE");
    oled.println("***********");

    digitalWrite(BUZZ, HIGH);
    delay(2000);
    digitalWrite(BUZZ, LOW);
    delay(100);
    ///

  }
  else
  {
    oled.clear();
    oled.set2X();
    oled.println("HOLA, EL");
    oled.println("JUEGO \nCOMENZARA");
    oled.println("PRONTO");
    delay(2000);
    oled.clear();
    oled.println("  ACERQUE\n    SU\n    ID");
    oled.println("***********");
    delay(1000);
  }
}
void finalCarrera()
{ oled.clear();
  oled.set2X();
  oled.println("WOW");
  oled.println("GANASTE! :)");
  digitalWrite(BUZZ, HIGH);
  delay(600);
  digitalWrite(BUZZ, LOW);
  delay(100);
  digitalWrite(BUZZ, HIGH);
  delay(600);
  digitalWrite(BUZZ, LOW);
  delay(100);
  digitalWrite(BUZZ, HIGH);
  delay(600);
  digitalWrite(BUZZ, LOW);
  delay(3000);
}
void botonPierdes() {
  oled.clear();
  oled.set2X();
  oled.println("***********");
  oled.println("HEY, :(");
  oled.println("PERDISTE");
  oled.println("***********");

  digitalWrite(BUZZ, HIGH);
  delay(2000);
  digitalWrite(BUZZ, LOW);
  delay(100);
}
