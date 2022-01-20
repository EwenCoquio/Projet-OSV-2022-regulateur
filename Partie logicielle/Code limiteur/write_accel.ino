void write_accel(int x){
  analogWrite(sortie_accel, x);  //la valeur de x est codé sur 8 bits (255 etant la valeur max)
}
