int acq_accel(){
  course_pedal = analogRead(accel_pedal);
  return course_pedal;
}
