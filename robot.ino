#include <pitches.h>  //library for music
#include <MeMCore.h>

int melody[] = {
  REST, REST, REST, NOTE_DS4, 
  NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
  NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_B4,   
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, 
  NOTE_E4, REST, REST, NOTE_DS4,
  
  NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
  NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_B4, NOTE_E5,
  NOTE_DS5,   
  NOTE_D5, REST, REST, NOTE_DS4, 
  NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
  NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_B4,   
  
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, 
  NOTE_E4, REST,
  REST, NOTE_E5, NOTE_D5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_E4,
  NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4,   
  NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4
};

int durations[] = {
  2, 4, 8, 8, 
  4, 8, 8, 4, 8, 8,
  8, 8,  8, 8, 8, 8, 8, 8,   
  2, 16, 16, 16, 16, 
  2, 4, 8, 4,
  
  4, 8, 8, 4, 8, 8,
  8, 8,  8, 8, 8, 8, 8, 8,
  1,   
  2, 4, 8, 8, 
  4, 8, 8, 4, 8, 8,
  8, 8,  8, 8, 8, 8, 8, 8,   
  
  2, 16, 16, 16, 16, 
  4, 4,
  4, 8, 8, 8, 8, 8, 8,
  16, 8, 16, 8, 16, 8, 16, 8,   
  16, 16, 16, 16, 16, 2
};


MeBuzzer buzzer;
MeDCMotor leftmotor(M1); // assigning leftMotor to port M1
MeDCMotor rightmotor(M2); // assigning RightMotor to port M2
MePort coloursensor = MePort(1);
MeLineFollower lineFinder(PORT_2);
MeUltrasonicSensor ultraSensor(PORT_3);
MePort sharedsensor = MePort(4);
int leftmotorspeed = -109;
int rightmotorspeed = 127;
// int leftmotorspeed = 0;
// int rightmotorspeed = 0;

void startmusic(){
  buzzer.tone(NOTE_D4, 350);
  delay(250);
  buzzer.tone(NOTE_D4, 350);
  delay(250);
  buzzer.tone(NOTE_D4, 350);
  delay(250);
  buzzer.tone(NOTE_D5, 700);
  delay(250);
}

void celebrate() {
    int size = sizeof(durations) / sizeof(int);
  for (int note = 0; note < size; note++) {
    int duration = 1000 / durations[note];
    buzzer.tone(melody[note], duration);
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
  }
}// Code for playing celebratory tune}

void stopMotor() {
  rightmotor.stop();
  leftmotor.stop();
  }// Code for stopping motor}

void moveForward() {
  rightmotor.run(rightmotorspeed);
  leftmotor.run(leftmotorspeed);
  delay(2300);
  rightmotor.stop();
  leftmotor.stop();
}// Code for moving forward for some short interval}

void turnRight() {
  rightmotor.run(-rightmotorspeed);
  leftmotor.run(leftmotorspeed);
  delay(950);
  rightmotor.stop();
  leftmotor.stop();
}// Code for turning right 90 deg

void turnLeft(){
  rightmotor.run(rightmotorspeed);
  leftmotor.run(-leftmotorspeed);
  delay(950);
  rightmotor.stop();
  leftmotor.stop();
}// Code for turning left 90 deg}

// void uTurn() {}// Code for u-turn}
// void doubleLeftTurn() {}// Code for double left turn}
// void doubleRightTurn() {}// Code for double right turn}


void nudgeLeft() {
  rightmotor.run(rightmotorspeed);
  leftmotor.run(-leftmotorspeed);
  delay(250);
  rightmotor.stop();
  leftmotor.stop();
}// Code for nudging slightly to the left for some short interval}

void nudgeRight() {
  rightmotor.run(-rightmotorspeed);
  leftmotor.run(leftmotorspeed);
  delay(150);
  rightmotor.stop();
  leftmotor.stop();
}// Code for nudging slightly to the right for some short interval}

int detectColour()
{
  Serial.begin(9600);
  coloursensor.dWrite1(LOW);
  coloursensor.dWrite2(LOW);
  buzzer.tone(NOTE_AS5, 1000);
// Shine Red, read LDR after some delay

  coloursensor.dWrite1(HIGH);
  coloursensor.dWrite2(HIGH);
  delay(1500);
  int redlightlevel = sharedsensor.aRead1();
  delay(1500);
  Serial.print("RED"); //remove
  Serial.println(redlightlevel); //remove
  buzzer.tone(NOTE_A5, 1000);
  

// Shine blu, read LDR after some delay
  coloursensor.dWrite1(HIGH);
  coloursensor.dWrite2(LOW);
  delay(1000);
  int bluelightlevel = sharedsensor.aRead1();
  delay(1000);
  Serial.print("BLUE"); //remove
  Serial.println(bluelightlevel); //remove
  buzzer.tone(NOTE_AS5, 1000);

// Shine green , read LDR after some delay
  coloursensor.dWrite1(LOW);
  coloursensor.dWrite2(HIGH);
  delay(1000);
  int greenlightlevel = sharedsensor.aRead1();
  delay(1000);
  Serial.print("GREEN"); //remove
  Serial.println(greenlightlevel); //remove
  buzzer.tone(NOTE_A5, 1000);
// Run algorithm for colour decoding. requires intense calibration

  
  if ((150 <= redlightlevel) && (redlightlevel<= 300)  && (600 <= bluelightlevel) && (bluelightlevel<= 700) && (600 <= greenlightlevel) && (greenlightlevel<= 700) ){ //white
    celebrate();
  }
  if ((100 <= redlightlevel) && (redlightlevel<= 200)  && (400 <= bluelightlevel) && (bluelightlevel<= 500) && (500 <= greenlightlevel) && (greenlightlevel<= 600) ){ //red
    turnLeft();
  }
  if ((85 <= redlightlevel) && (redlightlevel<= 150)  && (350 <= bluelightlevel) && (bluelightlevel<= 450) && (450 <= greenlightlevel) && (greenlightlevel<= 550) ){//green
    turnRight();
  }
  if ((150 <= redlightlevel) && (redlightlevel<= 250)  && (400 <= bluelightlevel) && (bluelightlevel<= 500) && (600 <= greenlightlevel) && (greenlightlevel<= 700) ){//orange
    turnLeft();
    turnLeft();
  }
  if ((50 <= redlightlevel) && (redlightlevel<= 150)  && (550 <= bluelightlevel) && (bluelightlevel<= 650) && (600 <= greenlightlevel) && (greenlightlevel<= 700) ){ //purple
  turnLeft();
  moveForward();
  turnLeft();
  }
  if ((100 <= redlightlevel) && (redlightlevel<= 200)  && (600 <= bluelightlevel) && (bluelightlevel<= 700) && (500 <= greenlightlevel) && (greenlightlevel<= 700) ){//blue
  turnRight();
  moveForward();
  turnRight();
  }
}



bool detectBlack() {
  int sensorState = lineFinder.readSensors();
  switch(sensorState)
  {
    case S1_IN_S2_IN:
      return true;
    case S1_IN_S2_OUT:
      return false;
      leftmotor.stop();
    case S1_OUT_S2_IN:
      return false;
      rightmotor.stop();      
    case S1_OUT_S2_OUT:
      return false;
  }
}




void ultrasonic(){
  float dist_cm = ultraSensor.distanceCm();
  
  // Serial.println(dist_cm);

  if (dist_cm < 5) {
    nudgeRight();
  }
}

// MePort sharedsensor = MePort(4) [already done earlier]
long shineIR() {
  coloursensor.dWrite1(LOW);
  coloursensor.dWrite2(LOW);
  long ir_level = sharedsensor.aRead2();
  return ir_level;
}

void IR_wall_clearance() {
  long ini_IR_level = sharedsensor.aRead2();
  long ref_IR_level = shineIR();

  long fin_IR_level = ref_IR_level - ini_IR_level;
  if (fin_IR_level > 4) {
    nudgeLeft();
  }
}

void defmovement(){
  rightmotor.run(rightmotorspeed);
  leftmotor.run(leftmotorspeed);
  if (detectBlack() == true){
    rightmotor.stop();
    leftmotor.stop();
    detectColour();
  }
  IR_wall_clearance();
  ultrasonic(); 
} //default movement

void setup()
{
  startmusic();
  //detectColour();
  
// Configure pinMode for A0, A1, A2, A3
}

void loop()
{
  defmovement();



  // leftmotor.run(leftmotorspeed);
  // rightmotor.run(rightmotorspeed);
  // if (detectBlack() == true){
  //   leftmotor.stop();
  //   rightmotor.stop();
  // }
// Read ultrasonic sensing distance (choose an appropriate timeout)
// Read IR sensing distance (turn off IR, read IR detector, turn on IR, read IR detector, estimate distance)
// if within black line, stop motor, detect colour, and take corresponding action
// 	else if too near to left wall, nudge right
// 	else if too near to right wall, nudge left
// 	else move forward


 //move forward
}


