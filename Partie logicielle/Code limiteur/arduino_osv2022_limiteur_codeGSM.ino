#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <SoftwareSerial.h>

#define DEBUG 0

//definition des pins
const int accel_pedal = A2; //pedale sur le pin 1
const int limiteur_state = 34 ; //on place le switch du limiteur sur un pin digital (en bas)
const int sortie_accel = 7;  //sortie du signal qui va vers le controleur

//definitions des autres variables
int sw_lim;


SoftwareSerial sim800l(52, 50); // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted

void setup() {
  sim800l.begin(9600); //baud rate du module sim800L (max)
  Serial.begin(115200);
  Serial.println("Starting ...");
  sim800l.println("AT");
  Serialcom();
  sim800l.println("AT+CMGF=1");     // Configuring TEXT mode
  Serialcom();
  sim800l.println("AT+CNMI=2,2,0,0,0"); //The way to handle the SMS received, check the module manual, to sum up: store the text or transfert it to serial or other number....
  Serialcom();
  pinMode(accel_pedal, INPUT);
  pinMode(sortie_accel, OUTPUT);
  pinMode(limiteur_state, INPUT);
}

int acq_accel() {
  return analogRead(accel_pedal);
}

void write_accel(int x) {
  x = map(x, 0, 1023 , 0, 250);  //on va utiliser la fonction map afin de lisser la courbe de la tension
  analogWrite(sortie_accel, x);  //la valeur de x est codé sur 8 bits (255 etant la valeur max)
}

void write_accel_lim(int x, int y) {
  x = map(x, 0, 1023 , 0, y);  //y est la valeur de notre vitesse max cap
  analogWrite(sortie_accel, x);
}

void loop() {
  Serialcom();
#ifdef DEBUG
  Serial.println("********************");
#endif
  if (digitalRead(limiteur_state)) {
    write_accel(acq_accel());
    Serial.println("limiteur desactive");
  }
  else {
    write_accel_lim(acq_accel(), 50);

    Serial.println("limiteur active");
  }
#ifdef DEBUG
  Serial.print("valeur de la course de la pedale : ");
  Serial.println(analogRead(accel_pedal));
  Serial.print("valeur de la sortie : ");
  Serial.println(analogRead(sortie_accel));
#endif
  delay(500);
}

void Serialcom()
{
  delay(500);
  while (Serial.available())                                                                     // IDE serial l serial  sim800L
  {
    sim800l.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (sim800l.available())                                                                     //serialsim800L l serial dial IDE
  {
    Serial.write(sim800l.read());//Forward what Software Serial received to Serial Port
  }
}
