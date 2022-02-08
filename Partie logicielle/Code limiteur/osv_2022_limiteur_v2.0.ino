#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

//definition des pins
const int accel_pedal = 1; //pedale sur le pin 1
const int limiteur_state = 34 ; //on place le switch du limiteur sur un pin digital (en bas)
const int sortie_accel = 7;  //sortie du signal qui va vers le controleur

//definitions des autres variables
int sw_lim;

void setup() {
  Serial.begin(115200);
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

void write_accel_lim(int x, int y) {
  x = map(x, 0, 1023 , 0, y);  //y est la valeur de notre vitesse max cap
  analogWrite(sortie_accel, x);
}

void loop() {
#ifdef DEBUG
  Serial.println("********************");
#endif
  if (digitalRead(limiteur_state)) {
    write_accel(acq_accel());
    Serial.println("limiteur desactive");
  }
  else {
    write_accel_lim(acq_accel(), 125);

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
