void ISR_R1_IR(void)
{
  detachInterrupt(R1);
  if (lock == 1){
      ctr++;
  }
  Serial.println("R1 HIGH");
  calcTime();  
}

void ISR_R2_IR(void)
{
  detachInterrupt(R2);
  if (lock == 1){
      ctr++;
  }
  Serial.println("R2 HIGH");
  calcTime();
}

void calcTime()
{
  switch(lock){
    case 1:
      switch(ctr)
    {
      case 1:
      //do start timer
       radarTimer.resume();
      break;
      case 2:
        radarTimer.pause();
        speed = 50 / timePassed; //calcs the distance divided by the time between the two modules;
        speed = speed * 10; //in order to get a correct result for the unit m/s we need to multiply speed by 10
        if(timePassed < 100){
          I2C_LCD(cM);
          delay(500);
          I2C_LCD("ERROR");
          Serial.println("ERROR -> Accidental Trigger?"); //if the Trigger of both happens too fast, which is most likely the result of a error, it prints this out instead
        }
        else {
          Serial.print("speed: ");
          Serial.println(speed); //speed is calculated in meter / s
          Serial.print("time: ");
          Serial.println(timePassed);
          I2C_LCD(cM);
          delay(500);
          I2C_LCD(String(speed) + " m/s");
          delay(2000); //temp value to wait until reset
        }  
        attachInterrupt(digitalPinToInterrupt(R1), ISR_R1_IR, RISING);
        attachInterrupt(digitalPinToInterrupt(R2), ISR_R2_IR, RISING);
      break;
      default: //default kann ggf errors vermeiden. (temporary)
        ctr = 0;
      break;
      }
    break;
    case 0:
    Serial.println("BT LOCK ENABLED");
    break;
    
  }
 
}