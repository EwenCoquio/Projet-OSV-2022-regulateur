const int accel_pedal = 1; //pedale sur le pin 1 
const int sortie_accel = 7;
int course_pedal;



void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(accel_pedal, INPUT);
  pinMode(sortie_accel, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  acq_accel();
  Serial.println(acq_accel());
  write_accel(210);
}
