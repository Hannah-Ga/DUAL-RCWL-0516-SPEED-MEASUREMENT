#include <SoftwareSerial.h>
#include <LiquidCrystal_PCF8574.h>

#define R1 D6
#define R2 D7
#define BTRX D2 //BLE Recieve
#define BTTX D3 //BLE Transmit

SoftwareSerial SerialBT(BTRX, BTTX);


static HardwareTimer radarTimer = HardwareTimer(TIM2);  // Timerinstanz sowie Timeruaswahl
LiquidCrystal_PCF8574 lcd (0x27); // LCD-Adresse auf 0x27 für 16 Zeichen und 2 Zeilen ein


String message; //String for BLE messages
String cM = "                "; //clear message
double timePassed, speed;
int ctr; //lock is for bt enabling and disabling
double R1S, R2S;
int lock = 1;



void setup() {
  // put your setup code here, to run once:
  SerialBT.begin(9600);
  Serial.begin(115200);
  Serial.println("BT connecting...");
  pinMode(R1, INPUT);
  pinMode(R2, INPUT);
  radarTimer.setOverflow(100); //1ms
  radarTimer.setPrescaleFactor(320); //1ms
  radarTimer.attachInterrupt(ISR_Timer);
  attachInterrupt(digitalPinToInterrupt(R1), ISR_R1_IR, RISING); //rising = react if sensor becomes HIGH / pullup
  attachInterrupt(digitalPinToInterrupt(R2), ISR_R2_IR, RISING);
  I2C_LCD_init();
  Serial.println("Board Ready!");
}

void loop() {
  //do nothing for now
  if (SerialBT.available()){
    message = SerialBT.readString();
    Serial.println(message);
    if (message == "1"){
      lock = 1;
      Serial.println("MODULE ON");
      radarTimer.pause();
      ctr = 0;
      timePassed = 0;
    }
    else {
      lock = 0;
      Serial.println("MODULE OFF");
      radarTimer.pause();
      ctr = 0;
      timePassed = 0;
    }
  }
  delay(500);
  if(timePassed == 3000){
    delay(3000); //if second sensor wont activate in time, RESET!
    Serial.println("reset");
    I2C_LCD(cM);
    radarTimer.pause();
    timePassed = 0;
    ctr = 0;   
    attachInterrupt(digitalPinToInterrupt(R1), ISR_R1_IR, RISING); 
    attachInterrupt(digitalPinToInterrupt(R2), ISR_R2_IR, RISING);
  }
}
