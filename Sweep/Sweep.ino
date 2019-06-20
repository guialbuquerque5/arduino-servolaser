// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// Modified for Energia/Stellaris Launchpad by Kevin Balke <fughilli@gmail.com>
// This example code is in the public domain.

#include <Servo.h> 
#define LASER 7
int t = 25;
String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete

Servo myservo;  // create servo object to control a servo 
int pos = 180;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(PB_5);  // attaches the servo on Port F, pin 1 (Red LED pin) to the servo object
  Serial.begin(38400);
  pinMode(LASER, OUTPUT);
    inputString.reserve(200);
     Serial.println(pos);
    setPos(0);              // tell servo to go to position in variable 'pos' 
    pos = 0;
    laserOn();
} 
void laserOn(){
   digitalWrite(LASER, HIGH);
}
void laserOff(){
   digitalWrite(LASER, LOW);

}

void increase(int num = 1){ 
    myservo.write(pos = ++pos>180?180:pos);              // tell servo to go to position in variable 'pos' 
    String s = "servo position: " + String(pos);
    Serial.println(s);

}
void decrease(){
    myservo.write(pos = --pos<0?0:pos);  
    String s = "servo position: " + String(pos);
     Serial.println(s);
}

void setPos(int p){
   Serial.println(p);
    int it = pos - p;
    for(int i = 0; i < (it>0?it:-it); i++){
          it>0?decrease():increase();
    }
}

void loop() 
{ 
  readSerial();
}

int getNumberFromString(String s){
  int numOut = 0; 
  int numDigits = s.length() -1;
  for(int i = 0; i < numDigits; i++){
      numOut+= (s[i]-48) * pow(10,numDigits-i-1);
  }
  return numOut;
}

void comand(String c){
  if(c.substring(0,3) == "inc"){
    int num = getNumberFromString(c.substring(4,c.length()));
    if(c.length() > 5){
      for(int i = 0; i < num; i++){
      increase();
      delay(t);
      }
    }
  }
  else if(c.substring(0,3) == "dec"){
    int num = getNumberFromString(c.substring(4,c.length()));
    if(c.length() > 5){
      for(int i = 0; i < num; i++){
      decrease();
      delay(t);
      }
    }
  }
  else if(c.substring(0,7) == "laserOn"){
    
    laserOn();
  }
  else if(c.substring(0,8) == "laserOff"){
    laserOff();
  }
  else if(c.substring(0,3)== "pos"){
    int num = getNumberFromString(c.substring(4,c.length()));   
    int it = pos - num;
    for(int i = 0; i < (it>0?it:-it); i++){
          it>0?decrease():increase();
    }
    Serial.print(pos);
  }
  else{
    Serial.println("Comando desconhecido");
  }
}

void readSerial(){
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
    stringComplete = true;
    } 
  }
  if (stringComplete) {
      Serial.print("command received: ");
      Serial.println(inputString);
      comand(inputString); 
      // clear the string:
      inputString = "";
      stringComplete = false;
    }
}

 
