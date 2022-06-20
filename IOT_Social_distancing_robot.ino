//--------------------<Servo>----------------------

#include <Servo.h>

Servo myservo;
int pos = 0;

//--------------------<Ultrasonic Sensors>----------------------

#include <NewPing.h>

#define TRIGGER_PIN1  A0  
#define ECHO_PIN1     A1  
#define MAX_DISTANCE1 100 

NewPing sonar(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE1); 

//--------------------<L298N motor controller>----------------------

int motor1pin1 = 9;
int motor1pin2 = 8;

int motor2pin1 = 7;
int motor2pin2 = 6;

//------------------------<Buzzer>------------------------------------------------

const int buzzer=12;

//------------------------<Function line Left or Right>---------------------------

bool LR_direction = true;

//------------------------<Size of line by units>---------------------------------

int MeterToUnits = 80 ; // 1 Unit = 5 cm that mean 200 = 10 meters
int unitsOfTotalmove = 0;
int unitsCheckDis = 0;

//------------------------<checker condition and Delay timer>-----------------------------------------

bool isTargetActive = false;
bool waitDelay = false;

void setup() {
  //pins that output to L298N DC motor controller
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT);
  //pin that output to servo
  myservo.attach(11);
  //pin output to buzzer
  pinMode(buzzer, OUTPUT);
  
}

void loop() {
  //check if someone in line frist then start check distance
  setLorR();
  checkDistance();
}

void checkDistance(){
  while(isTargetActive){
    //this if to force rebot to take frist step if units is zero
    if(isTargetActive&&unitsCheckDis==0){
      forward5CM();
      unitsCheckDis++;
      unitsOfTotalmove++;
    }
    int dis = sonar.ping_cm();
    //if Ultrasonic sensor out of range read will be zero 
    //for that we set it to maximum point in range
    if(dis==0){
      dis = 100;
    }
    //if it under 50cm that mean rebot found some one
    if(dis<50){
      //if units in his point more than 20(that mean 1 meter)
      if(unitsCheckDis>=20){
        //reset units counter
        unitsCheckDis = 0;
      }else{
        //if not start alarm
        for(int i = 0 ; i <3 ;i++){
          Alarm();
        }
      }
    }else{
      forward5CM();
      unitsCheckDis++;
    }
    //if robot in end point stop all and go to start point 
    if(unitsOfTotalmove==MeterToUnits){
      delay(1000);
      while(unitsOfTotalmove!=0){
        unitsOfTotalmove--;
        backward5CM(); 
      }
      //reset loop
      isTargetActive = false ;     
    }else{
      unitsOfTotalmove++;
    }
         
  }     
}
  

void setLorR(){
  delay(100);
  // define left and right
  float R = 0.0;
  float L = 0.0;
  for (pos = 0; pos <= 180; pos += 1) { 
    if(pos==2){
      delay(5000);
      R = sonar.ping_cm();
      }else if(pos== 178){
        delay(5000);
        L = sonar.ping_cm();
      }
    myservo.write(pos);              
    delay(15);
    }
    //part that take decision if line must by left or right 
    
    if(R<L&&R<50.0){ 
      LR_direction = false;
      pos = map(LR_direction, false, true, 0, 180);
      myservo.write(pos);
      
      isTargetActive = true ;
      }else if(L<R&&L<50.0){
        LR_direction = true;
        pos = map(LR_direction, false, true, 0, 180);
        myservo.write(pos);
        
        isTargetActive = true ;
        }else{
          delay(7000);
          
        }
     
}
void Alarm(){
  
    for(int Auint=0;Auint<=2;Auint++){
      
        if(Auint==2){
          digitalWrite(buzzer,HIGH);
          delay(1000);
          digitalWrite(buzzer,LOW);
          delay(1000);
         }else{
           digitalWrite(buzzer,HIGH);
           delay(500);
           digitalWrite(buzzer,LOW);
           delay(500); 
         }   
    }
}
void forward5CM(){


  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  //delay here is that way to controll size of movement by unit
  delay(47);

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  delay(0);
  
} 
void backward5CM(){


  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  delay(47);
 
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  delay(0);
  
}
