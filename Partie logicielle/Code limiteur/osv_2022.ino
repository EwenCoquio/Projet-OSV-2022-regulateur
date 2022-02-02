#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>

//definition des pins
const int accel_pedal = 1; //pedale sur le pin 1
const int limiteur_state = A6 ; //on place le switch du limiteur sur un pin digital (en bas)
const int sortie_accel = 7;  //sortie du signal qui va vers le controleur

//definitions des autres variables
int sw_lim;
int lim_flag = 0;                 // LED status flag


void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(accel_pedal, INPUT);
  pinMode(sortie_accel, OUTPUT);
  pinMode(limiteur_state, INPUT);

}

int acq_accel() {
  return analogRead(accel_pedal);
}

void write_accel(int x) {
  analogWrite(sortie_accel, x);  //la valeur de x est codé sur 8 bits (255 etant la valeur max)
}

void loop() {
//le limiteur est desactive
  if (analogRead(limiteur_state) >990) {
    write_accel(acq_accel());
    Serial.println("********************");
    Serial.println("limiteur desactive");
    Serial.print("valeur de la sortie : ");
    Serial.println(analogRead(sortie_accel));
    Serial.print("valeur de la course de la pedale : ");
    Serial.println(analogRead(accel_pedal));
  }
//le limiteur est active
  else if(analogRead(limiteur_state) <300) {
    write_accel(100);
    Serial.println("********************");
    Serial.println("limiteur active");
    Serial.print("valeur de la sortie : ");
    Serial.println(analogRead(sortie_accel));
    Serial.print("valeur de la course de la pedale : ");
    Serial.println(analogRead(accel_pedal));
  }

}
