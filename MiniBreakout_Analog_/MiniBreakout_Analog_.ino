#include <Keyboard.h>

//enum BUTTONS { A, B, X, Y, UP, DOWN, LEFT, RIGHT, START, SELECT, JOYSTICK, NUM_BUTTONS };

// Digital buttons assigned to pins on the breakout board
const int buttonpinA = 2;
const int buttonpinB = 3;
const int buttonpinX = 4;
const int buttonpinY = 5;
const int buttonpinUP = 6;
const int buttonpinDOWN = 7;
const int buttonpinLEFT = 8;
const int buttonpinRIGHT = 9;
const int buttonpinSTART = 10;
const int buttonpinSELECT= 11;
const int joyStickButton = 13;
int analogJoystickX = A0;
int analogJoystickY = A1;

// ButtonState to assign to each digital button
//int buttonState[NUM_BUTTONS] = { HIGH };
//int lastButtonState[NUM_BUTTONS] = { HIGH };

int buttonStateA;
int buttonStateB;
int buttonStateX;
int buttonStateY;
int buttonStateUP;
int buttonStateDOWN;
int buttonStateLEFT;
int buttonStateRIGHT;
int buttonStateSTART;
int buttonStateSELECT;
int buttonStateJOYSTICK;

int lastButtonStateA;
int lastButtonStateB;
int lastButtonStateX;
int lastButtonStateY;
int lastButtonStateUP;
int lastButtonStateDOWN;
int lastButtonStateLEFT;
int lastButtonStateRIGHT;
int lastButtonStateSTART;
int lastButtonStateSELECT;
int lastButtonStateJOYSTICK;

// Boolean used to stop the button press from writing multiple keys
boolean buttonPressA = false;
boolean buttonPressB = false;
boolean buttonPressX = false;
boolean buttonPressY = false;
boolean buttonPressUP = false;
boolean buttonPressDOWN = false;
boolean buttonPressLEFT = false;
boolean buttonPressRIGHT = false;
boolean buttonPressSTART = false;
boolean buttonPressSELECT = false;
boolean buttonPressJOYSTICK = false;

// Debounce variables for button presses
long lastDebounceTimeA = 0;
long lastPressTimeA = 0;

long lastDebounceTimeB = 0;
long lastPressTimeB = 0;

long lastDebounceTimeX = 0;
long lastPressTimeX = 0;

long lastDebounceTimeY = 0;
long lastPressTimeY = 0;

long lastDebounceTimeUP = 0;
long lastPressTimeUP = 0;

long lastDebounceTimeDOWN = 0;
long lastPressTimeDOWN = 0;

long lastDebounceTimeLEFT = 0;
long lastPressTimeLEFT = 0;

long lastDebounceTimeRIGHT = 0;
long lastPressTimeRIGHT = 0;

long lastDebounceTimeSTART = 0;
long lastPressTimeSTART = 0;

long lastDebounceTimeSELECT = 0;
long lastPressTimeSELECT = 0;

long lastDebounceTimeJOYSTICK = 0;
long lastPressTimeJOYSTICK= 0;

long debounceDelay = 25;
long holdTime = 10;
long holdJump = 7;
long runTime = 0.05;
long startSelectTime = 250;

void setup() {
  // Digital Buttons
  pinMode(buttonpinA, INPUT_PULLUP);
  pinMode(buttonpinB, INPUT_PULLUP);
  pinMode(buttonpinX, INPUT_PULLUP);
  pinMode(buttonpinY, INPUT_PULLUP);
  pinMode(buttonpinUP, INPUT_PULLUP);
  pinMode(buttonpinDOWN, INPUT_PULLUP);
  pinMode(buttonpinLEFT, INPUT_PULLUP);
  pinMode(buttonpinRIGHT, INPUT_PULLUP);
  pinMode(buttonpinSTART, INPUT_PULLUP);
  pinMode(buttonpinSELECT, INPUT_PULLUP);

  // Analog JoyStick
  pinMode(joyStickButton, INPUT_PULLUP);
  
  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  // Analog joystick
  int xValue = analogRead(analogJoystickX);
  int yValue = analogRead(analogJoystickY);

  Serial.print(xValue);
  Serial.print("\t");
  Serial.println(yValue);

//if ((millis() - lastDebounceTime) > debounceDelay) {
  // To The Corner
  if ((xValue >= 500 && yValue >= 1000) && (xValue >= 1000 && yValue >= 500)) {
    Keyboard.press(68); //d
    //lastDebounceTime = millis();
  }
  // Move Down -Y
  else if (xValue >= 500 && yValue >= 1000) {
    Keyboard.press(83); //s
    //lastDebounceTime = millis();
  }
  // Move UpB +Y
  else if (xValue >= 0 && yValue <= 10) {
    Keyboard.press(87); //w
    //lastDebounceTime = millis();
  }
  // Move Left -X
  else if (xValue <= 10 && yValue >= 500) {
    Keyboard.press(65); //a
    //lastDebounceTime = millis();
  }
  // Move Right +X
  else if (xValue >= 1000 && yValue >= 500) {
    Keyboard.press(68); //d
    //lastDebounceTime = millis();
  //}
  }
  else {
    Keyboard.releaseAll();
  }

// Digital buttons:
  int readingA = digitalRead(buttonpinA);
  int readingB = digitalRead(buttonpinB);
  int readingX = digitalRead(buttonpinX);
  int readingY = digitalRead(buttonpinY);
  int readingUP = digitalRead(buttonpinUP);
  int readingDOWN = digitalRead(buttonpinDOWN);
  int readingLEFT = digitalRead(buttonpinLEFT);
  int readingRIGHT = digitalRead(buttonpinRIGHT);
  int readingSTART = digitalRead(buttonpinSTART);
  int readingSELECT = digitalRead(buttonpinSELECT);
  int readingJOYSTICK = digitalRead(joyStickButton);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (buttonStateA != lastButtonStateA) {
    // reset the debouncing timer
    lastDebounceTimeA = millis();
  } else if ((buttonStateA == LOW) && (millis() - lastPressTimeA) > holdTime ) {
     Keyboard.press(90); //Z     
     lastPressTimeA = millis();
     delay(0.05);    
  }
  else {
    Keyboard.release(90);
  }

  if ((millis() - lastDebounceTimeA) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingA != buttonStateA) {
      buttonStateA = readingA;

      if (buttonStateA == LOW) {
         Keyboard.press(90); //Z
         
         lastPressTimeA = millis();
         delay(0.05);
      }
      else {
        Keyboard.release(90);
        }
     }
  }
  lastButtonStateA = buttonStateA;


// check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (buttonStateB != lastButtonStateB) {
    // reset the debouncing timer
    lastDebounceTimeB = millis();
  } else if ((buttonStateB == LOW) && (millis() - lastPressTimeB) > holdJump ) {
     Keyboard.press(88); //X     
     lastPressTimeB = millis();
     delay(15);    
  }
  else {
    Keyboard.release(88);
  }

  if ((millis() - lastDebounceTimeB) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingB != buttonStateB) {
      buttonStateB = readingB;

      if (buttonStateB == LOW) {
         Keyboard.press(88); //X
         
         lastPressTimeB = millis();
         delay(15);
      }
      else {
        Keyboard.release(88);
        }
    }
  }
  lastButtonStateB = buttonStateB;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (buttonStateX != lastButtonStateX) {
    // reset the debouncing timer
    lastDebounceTimeX = millis();
  } else if ((buttonStateX == LOW) && (millis() - lastPressTimeX) > holdTime ) {
     Keyboard.press(67); //C     
     lastPressTimeX = millis();    
  }
  else {
    Keyboard.release(67);
  }

  if ((millis() - lastDebounceTimeX) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingX != buttonStateX) {
      buttonStateX = readingX;

      if (buttonStateX == LOW) {
         Keyboard.press(67); //C
         
         lastPressTimeX = millis();
      }
      else {
        Keyboard.release(67);
        }
    }
  }
  lastButtonStateX = buttonStateX;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (buttonStateY != lastButtonStateY) {
    // reset the debouncing timer
    lastDebounceTimeY = millis();
  } else if ((buttonStateY == LOW) && (millis() - lastPressTimeY) > holdTime ) {
     Keyboard.press(86); //V     
     lastPressTimeY = millis();    
  }
  else {
    Keyboard.release(86);
  }

  if ((millis() - lastDebounceTimeA) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingY != buttonStateY) {
      buttonStateY = readingY;

      if (buttonStateY == LOW) {
         Keyboard.press(86); //V
         
         lastPressTimeY = millis();
      }
      else {
        Keyboard.release(86);
        }
    }
  }
  lastButtonStateY = buttonStateY;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (buttonStateUP != lastButtonStateUP) {
    // reset the debouncing timer
    lastDebounceTimeUP = millis();
  } else if ((buttonStateUP == LOW) && (millis() - lastPressTimeUP) > runTime ) {
    for (int i = 0; i < 200; i++) {
      Keyboard.press(48); //0     
      lastPressTimeUP = millis(); 
    }
        
  }
  else {
    Keyboard.release(48);
  }

  if ((millis() - lastDebounceTimeUP) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingUP != buttonStateUP) {
      buttonStateUP = readingUP;

      if (buttonStateUP == LOW) {
         for (int i = 0; i < 200; i++) {
          Keyboard.press(48); //0     
          lastPressTimeUP = millis(); 
          }
         
         lastPressTimeUP = millis();
      }
      else {
        Keyboard.release(48);
        }
    }
  }
  lastButtonStateUP = buttonStateUP;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (buttonStateDOWN != lastButtonStateDOWN) {
    // reset the debouncing timer
    lastDebounceTimeDOWN = millis();
  } else if ((buttonStateDOWN == LOW) && (millis() - lastPressTimeDOWN) > runTime ) {
    for (int i = 0; i < 200; i++) {
      Keyboard.press(57); //9     
      lastPressTimeDOWN = millis();
    }
         
  }
  else {
    Keyboard.release(57);
  }

  if ((millis() - lastDebounceTimeDOWN) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingDOWN != buttonStateDOWN) {
      buttonStateDOWN = readingDOWN;

      if (buttonStateDOWN == LOW) {
         for (int i = 0; i < 200; i++) {
          Keyboard.press(57); //9     
          lastPressTimeDOWN = millis();
        }
      }
      else {
        Keyboard.release(57);
        }
    }
  }
  lastButtonStateDOWN = buttonStateDOWN;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (buttonStateLEFT != lastButtonStateLEFT) {
    // reset the debouncing timer
    lastDebounceTimeLEFT = millis();
  } else if ((buttonStateLEFT == LOW) && (millis() - lastPressTimeLEFT) > runTime ) {
    for (int i = 0; i < 200; i++) {
      Keyboard.press(56); //8     
      lastPressTimeLEFT = millis();
    }
         
  }
  else {
    Keyboard.release(56);
  }

  if ((millis() - lastDebounceTimeLEFT) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingLEFT != buttonStateLEFT) {
      buttonStateLEFT = readingLEFT;

      if (buttonStateLEFT == LOW) {
         for (int i = 0; i < 200; i++) {
          Keyboard.press(56); //8     
          lastPressTimeLEFT = millis();
        }
      }
      else {
        Keyboard.release(56);
        }
    }
  }
  lastButtonStateLEFT = buttonStateLEFT;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (buttonStateRIGHT != lastButtonStateRIGHT) {
    // reset the debouncing timer
    lastDebounceTimeRIGHT = millis();
  } else if ((buttonStateRIGHT == LOW) && (millis() - lastPressTimeRIGHT) > runTime ) {
    for (int i = 0; i < 200; i++) {
      Keyboard.press(55); //7     
      lastPressTimeRIGHT = millis(); 
    }
       
  }
  else {
    Keyboard.release(55);
  }

  if ((millis() - lastDebounceTimeRIGHT) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingRIGHT != buttonStateRIGHT) {
      buttonStateRIGHT = readingRIGHT;

      if (buttonStateRIGHT == LOW) {
        for (int i = 0; i < 200; i++) {
          Keyboard.press(55); //7     
          lastPressTimeRIGHT = millis(); 
        }
         
      }
      else {
        Keyboard.release(55);
        }
    }
  }
  lastButtonStateRIGHT = buttonStateRIGHT;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (buttonStateSTART != lastButtonStateSTART) {
    // reset the debouncing timer
    lastDebounceTimeSTART = millis();
  } else if ((buttonStateSTART == LOW) && (millis() - lastPressTimeSTART) > startSelectTime ) {
     Keyboard.press(49); //1     
     lastPressTimeSTART = millis();    
  }
  else {
    Keyboard.release(49);
  }

  if ((millis() - lastDebounceTimeSTART) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingSTART != buttonStateSTART) {
      buttonStateSTART = readingSTART;

      if (buttonStateSTART == LOW) {
         Keyboard.press(49); //1
         
         lastPressTimeSTART = millis();
      }
      else {
        Keyboard.release(49);
        }
    }
  }
  lastButtonStateSTART = buttonStateSTART;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (buttonStateSELECT != lastButtonStateSELECT) {
    // reset the debouncing timer
    lastDebounceTimeSELECT = millis();
  } else if ((buttonStateSELECT == LOW) && (millis() - lastPressTimeSELECT) > startSelectTime ) {
     Keyboard.press(177); //ESC     
     lastPressTimeSELECT = millis();    
  }
  else {
    Keyboard.release(177);
  }

  if ((millis() - lastDebounceTimeSELECT) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingSELECT != buttonStateSELECT) {
      buttonStateSELECT = readingSELECT;

      if (buttonStateSELECT == LOW) {
         Keyboard.press(177); //ESC
         
         lastPressTimeSELECT = millis();
      }
      else {
        Keyboard.release(177);
        }
    }
  }
  lastButtonStateSELECT = buttonStateSELECT;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (buttonStateJOYSTICK != lastButtonStateJOYSTICK) {
    // reset the debouncing timer
    lastDebounceTimeJOYSTICK = millis();
  } else if ((buttonStateJOYSTICK == LOW) && (millis() - lastPressTimeJOYSTICK) > holdTime ) {
     Keyboard.press(51); //3     
     lastPressTimeJOYSTICK = millis();    
  }
  else {
    Keyboard.release(51);
  }

  if ((millis() - lastDebounceTimeJOYSTICK) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingJOYSTICK != buttonStateJOYSTICK) {
      buttonStateJOYSTICK = readingJOYSTICK;

      if (buttonStateJOYSTICK == LOW) {
         Keyboard.press(51); //3
         
         lastPressTimeJOYSTICK = millis();
      }
      else {
        Keyboard.release(51);
        }
    }
  }
  lastButtonStateJOYSTICK = buttonStateJOYSTICK;
}
