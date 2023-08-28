#include <Servo.h>
#define numOfValsRec 5
#define digitsPerValRec 1

Servo servoThumb; 
Servo servoIndex; 
Servo servoMiddle; 
Servo servoRing; 
Servo servoPinky; 


int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1; //$00000
int counter=0;
bool counterStart = false;
String receviedString;


void setup (){
  Serial.begin(9600);
  servoThumb.attach(3);
  servoIndex.attach(7);
  servoMiddle.attach(5); 
  servoRing.attach(9); 
  servoPinky.attach(11); 

}

void receiveData(){
while (Serial.available()){
char c = Serial.read();

  if (c=='$'){
    counterStart = true;
  }
  if (counterStart){
    if (counter < stringLength){
      receviedString += c;
      // receviedString = String(receviedString);
      counter ++;
    }
    if (counter >= stringLength){
        for (int i = 0; i<numOfValsRec; i++){
            int num = (i * digitsPerValRec) + 1;
            valsRec[i] = receviedString.substring(num,num+digitsPerValRec) .toInt ();
            }
            receviedString = "";
            counter = 0; 
            counterStart = false;
    }
  }
}

}

void loop(){
  receiveData();
  if (valsRec[0] == 1){servoThumb.write(0);} else{servoThumb.write(180);}
  if (valsRec[1] == 1){servoIndex.write(0);} else{servoIndex.write(180);}
  if (valsRec[2] == 1){servoMiddle.write(0);} else{servoMiddle.write(180);}
  if (valsRec[3] == 1){servoRing.write(0);} else{servoRing.write(180);}
  if (valsRec[4] == 1){servoPinky.write(0);} else{servoPinky.write(180);}
}


