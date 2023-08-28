#include <Servo.h>

// Define the number of values to receive and digits per value
#define numOfValsRec 5
#define digitsPerValRec 1

// Declare Servo objects for each finger
Servo servoThumb; 
Servo servoIndex; 
Servo servoMiddle; 
Servo servoRing; 
Servo servoPinky; 

// Arrays and variables for receiving and processing data
int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1; //$00000
int counter=0;
bool counterStart = false;
String receviedString;


void setup (){
  Serial.begin(9600);
  // Attach Servo objects to their corresponding pins
  servoThumb.attach(3);
  servoIndex.attach(7);
  servoMiddle.attach(5); 
  servoRing.attach(9); 
  servoPinky.attach(11); 

}

// Function to receive and process data
void receiveData() {
  // Loop while there are available characters in the serial buffer
  while (Serial.available()) {
    char c = Serial.read(); // Read a character from serial buffer

    // Check if the received character is the start marker '$'
    if (c == '$') {
      counterStart = true; // Start receiving data
    }

    // Continue receiving data if the start marker has been found
    if (counterStart) {
      // Check if the counter is within the expected range of characters
      if (counter < stringLength) {
        receviedString += c; // Add the received character to the string
        counter++; 
      }

      // Process the received string once it's complete
      if (counter >= stringLength) {
        // Loop through the values received for each finger
        for (int i = 0; i < numOfValsRec; i++) {
          // Calculate the index positions for each value within the string
          int num = (i * digitsPerValRec) + 1;
          // Extract and convert the substring to an integer value
          valsRec[i] = receviedString.substring(num, num + digitsPerValRec).toInt();
        }

        // Reset variables for the next iteration
        receviedString = "";
        counter = 0;
        counterStart = false; // Stop receiving data until the next start marker
      }
    }
  }
}

void loop(){
  receiveData();
  // Set servo positions based on received data
  if (valsRec[0] == 1){servoThumb.write(0);} else{servoThumb.write(180);}
  if (valsRec[1] == 1){servoIndex.write(0);} else{servoIndex.write(180);}
  if (valsRec[2] == 1){servoMiddle.write(0);} else{servoMiddle.write(180);}
  if (valsRec[3] == 1){servoRing.write(0);} else{servoRing.write(180);}
  if (valsRec[4] == 1){servoPinky.write(0);} else{servoPinky.write(180);}
}


