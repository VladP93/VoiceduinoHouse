#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

VR myVR(2,3);    // 2:RX 3:TX, you can choose your favourite pins.

uint8_t records[7]; // save record
uint8_t buf[64];

int pinVentilador = 4;
int pinLuces = 5;
int pinAlarma1 = 10;
int pinAlarma2 = 11;
int pinAlarma3 =  12;
int ledSala = 6;
int ledCocina = 9;
int ledBanio = 8;
int ledCuarto = 7;
int analogo = 0;
boolean alarmab = false;

#define Ventilador (0)
#define Alarma (1)
#define Sala (2)
#define Cocina (3)
#define Banio (4)
#define Cuarto (5)
#define Apagar (6)

void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  /** initialize */
  myVR.begin(9600);
  
  Serial.begin(115200);

  Serial.println("Bienvenido");

   pinMode(pinVentilador, OUTPUT);
   pinMode(pinAlarma1, OUTPUT);
   pinMode(pinAlarma2, OUTPUT);
   pinMode(pinAlarma3, OUTPUT);
   pinMode(ledSala, OUTPUT);
   pinMode(ledCocina, OUTPUT);
   pinMode(ledBanio, OUTPUT);
   pinMode(ledCuarto, OUTPUT);
   
   digitalWrite(pinVentilador, LOW);
   digitalWrite(pinAlarma1, HIGH);
   digitalWrite(pinAlarma2, HIGH);
   digitalWrite(pinAlarma3, HIGH);
   analogWrite(ledSala, analogo);
   digitalWrite(ledCocina, LOW);
   digitalWrite(ledBanio, LOW);
   digitalWrite(ledCuarto, LOW);

  if (myVR.load((uint8_t)Ventilador) >= 0) {
 Serial.println("Ventilador loaded");
 }

 if (myVR.load((uint8_t)Alarma) >= 0) {
 Serial.println("Ventana loaded");
 }

 if (myVR.load((uint8_t)Sala) >= 0) {
 Serial.println("Sala loaded");
 }

 if (myVR.load((uint8_t)Cocina) >= 0) {
 Serial.println("Cocina loaded");
 }

 if (myVR.load((uint8_t)Banio) >= 0) {
 Serial.println("Banio loaded");
 }

 if (myVR.load((uint8_t)Cuarto) >= 0) {
 Serial.println("Cuarto loaded");
 }

 if (myVR.load((uint8_t)Apagar) >= 0) {
 Serial.println("Apagar loaded");
 }
}

void loop()
{
 int ret;
 ret = myVR.recognize(buf, 50);
 if (ret > 0) {
  switch (buf[1]) {
    case Ventilador:
      digitalWrite(pinVentilador, !digitalRead(pinVentilador));
      break;
    case Alarma:
      alarmab = !alarmab;
      break;
    case Sala:
      Serial.println(analogo);
       if(analogo == 0){
        analogo=96;
        analogWrite(ledSala, analogo);
       } else if(analogo == 96){
        analogo=160;
        analogWrite(ledSala, analogo);
       } else if(analogo == 160){
        analogo=255;
        analogWrite(ledSala, analogo);
       } else if(analogo == 255){
        analogo=0;
        analogWrite(ledSala, analogo);
       }
      break;
    case Cocina:
      digitalWrite(ledCocina, !digitalRead(ledCocina));
      break;
    case Banio:
      digitalWrite(ledBanio, !digitalRead(ledBanio));
      break;
    case Cuarto:
      digitalWrite(ledCuarto, !digitalRead(ledCuarto));
      break;
    case Apagar:
      digitalWrite(ledSala, LOW);
      digitalWrite(ledCocina, LOW);
      digitalWrite(ledBanio, LOW);
      digitalWrite(ledCuarto, LOW);
      digitalWrite(pinVentilador, LOW);
      break;
    default:
      Serial.println("Record function undefined");
      break;
   }
 /** voice recognized */
  printVR(buf);
  }
  if(alarmab){
        digitalWrite(pinAlarma1, HIGH);
        digitalWrite(pinAlarma2, HIGH);
        digitalWrite(pinAlarma3, LOW);
        delay(100);
        digitalWrite(pinAlarma1, HIGH);
        digitalWrite(pinAlarma2, LOW);
        digitalWrite(pinAlarma3, HIGH);
        delay(100);
        digitalWrite(pinAlarma1, LOW);
        digitalWrite(pinAlarma2, HIGH);
        digitalWrite(pinAlarma3, HIGH);
        delay(100);
        digitalWrite(pinAlarma1, LOW);
        digitalWrite(pinAlarma2, LOW);
        digitalWrite(pinAlarma3, LOW);
        delay(100);
        digitalWrite(pinAlarma1, HIGH);
        digitalWrite(pinAlarma2, HIGH);
        digitalWrite(pinAlarma3, HIGH);
        delay(100);
        digitalWrite(pinAlarma1, LOW);
        digitalWrite(pinAlarma2, LOW);
        digitalWrite(pinAlarma3, LOW);
        delay(100);
        digitalWrite(pinAlarma1, HIGH);
        digitalWrite(pinAlarma2, HIGH);
        digitalWrite(pinAlarma3, HIGH);
        delay(100);
        digitalWrite(pinAlarma1, LOW);
        digitalWrite(pinAlarma2, LOW);
        digitalWrite(pinAlarma3, LOW);
        delay(100);
        digitalWrite(pinAlarma1, HIGH);
        digitalWrite(pinAlarma2, HIGH);
        digitalWrite(pinAlarma3, HIGH);
        delay(100);
      }


      if(analogRead(A0)<400){
        digitalWrite(pinLuces,HIGH);
        //Serial.println(analogRead(A0));
      }else{
        digitalWrite(pinLuces,LOW);
        //Serial.println(analogRead(A0));
      }

      
}

