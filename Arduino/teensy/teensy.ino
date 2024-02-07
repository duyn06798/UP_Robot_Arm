//This is just an example, not guanretee to work

#include <Arduino.h>
#include <ODriveTeensyCAN.h>

ODriveTeensyCAN odriveCAN;


// Joystick pins
const int joystickXPin = 14;  // Joystick X-axis
const int joystickYPin = 15;  // Joystick Y-axis
const int buttonPin = 1;
const int clearPin = 1;
const int calibratePin = 2;

//Global variables
float destPos = 0;
float posGainX = 0;
float posGainY = 0;

float posGain = .1;

boolean stopRobot  = false; 

void setup() {

  Serial.begin(115200);  // Start Serial monitor
  Serial.println("test");

  // Initialize joystick pins
  //pinMode(joystickXPin, INPUT);
  //pinMode(joystickYPin, INPUT);
  pinMode(buttonPin, INPUT);
  //pinMode(clearPin, INPUT_PULLUP);
  //pinMode(calibratePin, INPUT_PULLUP);
  
  odriveCAN = ODriveTeensyCAN();
  Serial.println(digitalRead(buttonPin));
  while (!(digitalRead(buttonPin) == 1));
  Serial.println("Robot online");
  Serial.println("Running calibration");

  int currentState = odriveCAN.GetCurrentState(2);
  Serial.println("Current State: " + currentState);
  Serial.println("Set to Full Calibration");
  odriveCAN.RunState(2, 3);
  while(odriveCAN.GetCurrentState(2) != currentState)
  {
    Serial.println("Currently calibrating");
  }
  Serial.println("Set to Closed Loop Control");
  odriveCAN.RunState(2, 8);

  while(1);
}

void loop() {
  Serial.println("New Loop");
  /*Serial.print("BP: " + (String)digitalRead(buttonPin));
  Serial.print(" CLP: " + (String)digitalRead(clearPin));
  Serial.println(" CAP: " + (String)digitalRead(calibratePin));
  */
  /*if(digitalRead(buttonPin) == 1)
  {
    //odriveCAN.Estop(1);
    Serial.println("ESTOP");
  }
  
  if(digitalRead(clearPin) == 0)
  {
    Serial.println("Clear error!");
    odriveCAN.ClearErrors(1);
  }
  */
  if(digitalRead(calibratePin) == 0)
  {
    int currentState = odriveCAN.GetCurrentState(1);
    Serial.println("Current State: " + currentState);
    Serial.println("Set to Full Calibration");
    odriveCAN.RunState(1, 3);
    while(odriveCAN.GetCurrentState(1) != currentState)
    {
      Serial.println("Currently calibrating");
    }
    Serial.println("Set to Closed Loop Control");
    odriveCAN.RunState(1, 8);
  }
  
  int joystickX = analogRead(joystickXPin);  // Read joystick X value
  int joystickY = analogRead(joystickYPin);


  //set the deadband and gain for the joystick
  if (!(300 < joystickY && joystickY < 600))
  { if (joystickY >= 300)
    { posGainY = (-1 * posGain * (joystickY - 300) / 300);
    }
    else if (joystickY <= 600)
    { posGainY = (posGain * (600 - joystickY) / 300);
    }
  }
  else
  { posGainY = 0;
  }

  if (!(300 < joystickX && joystickX < 600))
  { if (joystickX <= 300)
    { posGainX = (-1 * posGain * (300 - joystickX) / 300);
    }
    else if (joystickX >= 600)
    { posGainX = (posGain * (joystickX - 600) / 300);
    }
  }
  else
  { posGainX = 0;
  }



  float odrv0_pos = odriveCAN.GetPosition(1);
  int odrv0_current_state = odriveCAN.GetCurrentState(1);


  destPos = odrv0_pos + posGainX;

  
  if (abs(destPos - odrv0_pos) > 0.05)
  {
    odriveCAN.SetPosition(1, destPos);
  }

  Serial.println("X: " + (String)joystickX + " Y: " + (String)joystickY);
  Serial.println("Xpos: " + (String)posGainX + " Ypos: " + (String)posGainY);


  Serial.println("Current State: " + (String)odrv0_current_state);
  Serial.println("ODRV0 Position: " + (String)odrv0_pos);
  Serial.println("Destination Position: " + (String)destPos);
//  Serial.println("Stop Robot: " + (String)stopRobot);

  //posOld = odrv0_pos;
  delay(200);

}
