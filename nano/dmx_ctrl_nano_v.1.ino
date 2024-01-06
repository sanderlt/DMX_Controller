// get the libary at:  https://github.com/mathertel/DMXSerial  by: mathertel
#include <DMXSerial.h>       
#define number_of_74hc595s 6
#define numOfRegisterPins number_of_74hc595s * 8
#define numRGBLeds 16

// DMX Settings
int startAddress = 0;  
int dmxUV = 0;
int dmxDelay = 100;

// Shift Register Pins
int enablePin = 1;
int dataPin = 2;
int clockPin = 3;
int latchPin = 4;

// DMX Address dip switches
int Input1 = 5;  
int Input2 = 6;  
int Input3 = 7;  
int Input4 = 8;  
int Input5 = 9;  
int Input6 = 10; 
int Input7 = 11;   
int Input8 = 12; 
int Input9 = 13; 
int Input10 = 14; // reserved for option

// Dip switch address state
int Dip1 = 0;
int Dip2 = 0;
int Dip3 = 0;
int Dip4 = 0;
int Dip5 = 0;
int Dip6 = 0;
int Dip7 = 0;
int Dip8 = 0;
int Dip9 = 0;
int Dip10 = 0;  // reserved for option

// alligning register to colour
int bluePin[]  = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45};
int greenPin[] = {1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34, 37, 40, 43, 46};
int redPin []  = {2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35, 38, 41, 44, 47};

boolean registers[numOfRegisterPins];

void setup() {

  DMXSerial.init(DMXReceiver);
  
  pinMode(dataPin,  OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  digitalWrite(enablePin, LOW);

  pinMode(Input1, INPUT_PULLUP);
  pinMode(Input2, INPUT_PULLUP);
  pinMode(Input3, INPUT_PULLUP);
  pinMode(Input4, INPUT_PULLUP);
  pinMode(Input5, INPUT_PULLUP);
  pinMode(Input6, INPUT_PULLUP);
  pinMode(Input7, INPUT_PULLUP);
  pinMode(Input8, INPUT_PULLUP);
  pinMode(Input9, INPUT_PULLUP);
  pinMode(Input10, INPUT_PULLUP);

  // translate the dip switches inputs into a number
  if (digitalRead(Input1) == HIGH) {Dip1 = 0;}
  if (digitalRead(Input1) == LOW)  {Dip1 = 1;}

  if (digitalRead(Input2) == HIGH) {Dip2 = 0;}
  if (digitalRead(Input2) == LOW)  {Dip2 = 2;}

  if (digitalRead(Input3) == HIGH) {Dip3 = 0;}
  if (digitalRead(Input3) == LOW)  {Dip3 = 4;}

  if (digitalRead(Input4) == HIGH) {Dip4 = 0;}
  if (digitalRead(Input4) == LOW)  {Dip4 = 8;}

  if (digitalRead(Input5) == HIGH) {Dip5 = 0;}
  if (digitalRead(Input5) == LOW)  {Dip5 = 16;}

  if (digitalRead(Input6) == HIGH) {Dip6 = 0;}
  if (digitalRead(Input6) == LOW)  {Dip6 = 32;}

  if (digitalRead(Input7) == HIGH) {Dip7 = 0;}
  if (digitalRead(Input6) == LOW)  {Dip7 = 64;}

  if (digitalRead(Input8) == HIGH) {Dip8 = 0;}
  if (digitalRead(Input8) == LOW)  {Dip8 = 128;}

  if (digitalRead(Input9) == HIGH) {Dip9 = 0;}
  if (digitalRead(Input9) == LOW)  {Dip9 = 256;}

  if (digitalRead(Input10) == HIGH) {Dip10 = 1;}
  if (digitalRead(Input10) == LOW)  {Dip10 = 0;}  // reserved for option

// set the startAddress 
 startAddress = Dip1 + Dip2 + Dip3 + Dip4 + Dip5 + Dip6 + Dip7 + Dip8 + Dip9; 

  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    registers[i] = LOW;   
  }
  ledOff(0); 
}

void loop() {

// Calculate how long no data backet was received
  unsigned long lastPacket = DMXSerial.noDataSince();

   dmxUV =  DMXSerial.read(startAddress);          // first fixture channel <---- this is where you read the incomming DMX values 
   dmxDelay = DMXSerial.read(startAddress + 1);   // second fixture channel; for future use; maybe I implement a strobe function or add a extra colour 
   //if (dmxDelay > 45) dmxDelay = 45;
  
     if (lastPacket < 5000) {                  // it is less than 5 seconds after we received a DMX value 
    dmxUV = DMXSerial.read(startAddress);          
    digitalWrite(LED_BUILTIN, HIGH);       // display a normal operation and we receive a DMX value

     //  int dmxChanged = dmxUV;

switch (dmxUV) {
  case 1 ... 10:
        effect_1(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
  case 11 ... 20:
        effect_2(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
  case 21 ... 30:
        effect_3(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
  case 31 ... 40:
        effect_4(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
  case 41 ... 50:
        effect_5(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
  case 51 ... 60:
        effect_6(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
  case 61 ... 70:
        effect_7(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
  case 71 ... 80:
        effect_8(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
  case 81 ... 90:
        effect_9(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
   case 91 ... 100:
        effect_10(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
   case 101 ... 110:
        effect_11(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
    case 111 ... 120:
        effect_12(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
    case 121 ... 130:
        effect_13(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
    case 131 ... 140:
        effect_14(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
    case 141 ... 150:
        effect_15(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
    case 151 ... 160:
        effect_16(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
    case 161 ... 170:
        effect_17(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
    case 171 ... 180:
        effect_18(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
    case 181 ... 190:
        effect_19(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
    case 191 ... 200:
        effect_20(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
    case 201 ... 210:
        effect_1(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
    case 211 ... 255:
        effect_1(1);//effect_X(how many time you want to repeat the effect.)
        ledOff(0);
    break;
  default:
        //freq = 150.0;
        ////Serial.println(result);
        //Serial.println(result);
    // block of code default: do something when var is not equal to any of above label
    break;
}
 }
//   


else {
//  dmxDelay = 45; 
//  
//  effect_1(1);//effect_X(how many time you want to repeat the effect.)
//  ledOff(0);  //ledOff(leds off time )
//  effect_2(1);
//  ledOff(0);
//  effect_3(1);
//  ledOff(0);
//  effect_4(4);
//  ledOff(0);
//  effect_5(2);
//  ledOff(0);
//  effect_6(1);
//  ledOff(0);
//  effect_7(3);
//  ledOff(0);
//  effect_8(1);
//  ledOff(0);
//  effect_9(1);
//  ledOff(0);
//  effect_10(1);
//  ledOff(0);
//  effect_11(1);
//  ledOff(0);
//  effect_12(2);
//  ledOff(0);
//  effect_13(1);
//  ledOff(0);
//  effect_14(1);
//  ledOff(0);
//  effect_15(3);
//  ledOff(0);
//  effect_16(1);
//  ledOff(0);
//  effect_17(1);
//  ledOff(0);
//  effect_18(1);
//  ledOff(0);
//  effect_19(2);
//  ledOff(0);
//  effect_20(5);
//  ledOff(0);
//  delay(1000);
}
}
//////////////////////////////////////////////////////EFFECT 1
void effect_1(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    Red(0, 14, 0);
    brigtness();
    //ledOff(0);

    Yellow(0, 14, 0);
    brigtness();
    //ledOff(0);

    Green(0, 14, 0);
    brigtness();
    //ledOff(0);

    White(0, 14, 0);
    brigtness();
    //ledOff(0);

    Cyan(0, 14, 0);
    brigtness();
    //ledOff(0);

    Blue(0, 14, 0);
    brigtness();
    //ledOff(0);

    Pink(0, 14, 0);
    brigtness();
    //ledOff(0);

    
  }
}
//////////////////////////////////////////////////////effect_2
void effect_2(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i <= 14; i++ ) {
      Red(0, i, 0);
      delay(dmxDelay);
      ledOff(0);

      Yellow(0, i, 0);
      delay(dmxDelay);
      ledOff(0);

      Green(0, i, 0);
      delay(dmxDelay);
      ledOff(0);

      White(0, i, 0);
      delay(dmxDelay);
      ledOff(0);

      Cyan(0, i, 0);
      delay(dmxDelay);
      ledOff(0);

      Blue(0, i, 0);
      delay(dmxDelay);
      ledOff(0);

      Pink(0, i, 0);
      delay(dmxDelay);
      ledOff(0);
    }
  }
}
//////////////////////////////////////////////////////effect_3
void effect_3(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i <= 14; i++) {
      registersWrite(redPin[i], HIGH);
      delay(dmxDelay);
    } ledOff(30);
    for (int i = 14; i >= 0; i--) {
      registersWrite(redPin[i], HIGH);
      registersWrite(bluePin[i], HIGH);
      delay(dmxDelay);
    } ledOffR(30);

    for (int i = 0; i <= 14; i++) {
      registersWrite(greenPin[i], HIGH);
      delay(dmxDelay);
    } ledOff(30);

    for (int i = 14; i >= 0; i--) {
      registersWrite(redPin[i], HIGH);
      registersWrite(greenPin[i], HIGH);
      delay(dmxDelay);
    } ledOffR(30);

    for (int i = 0; i <= 14; i++) {
      registersWrite(bluePin[i], HIGH);
      delay(dmxDelay);
    } ledOff(30);

    for (int i = 14; i >= 0; i--) {
      registersWrite(bluePin[i], HIGH);
      registersWrite(greenPin[i], HIGH);
      delay(dmxDelay);
    } ledOffR(30);

    for (int i = 0; i <= 14; i++) {
      registersWrite(bluePin[i], HIGH);
      registersWrite(redPin[i], HIGH);
      registersWrite(greenPin[i], HIGH);
      delay(dmxDelay);
    } ledOff(30);
  }
}
//////////////////////////////////////////////////////effect_4
void effect_4(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    byte led = 0b10101010;
    byte led1 = 0b10101010;
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, led);
    shiftOut(dataPin, clockPin, LSBFIRST, led1);
    digitalWrite(latchPin, HIGH);
    delay(dmxDelay);
    brigtnessNodelay();
    byte led2 = 0b01010101;
    byte led3 = 0b01010101;
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, led2);
    shiftOut(dataPin, clockPin, LSBFIRST, led3);
    digitalWrite(latchPin, HIGH);
    delay(dmxDelay);
  }
}
//////////////////////////////////////////////////////effect_5
void effect_5(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    Red(0, 1, 0);
    Yellow(2, 3, 0);
    Green(4, 5, 0);
    White(6, 7, 0);
    Cyan(8, 9, 0);
    Blue(10, 11, 0);
    Pink(12, 13, 0);
    Red(14, 14, 0);

    brigtness();
    for (int i = 1; i <= 5; i++) {
      turnOutputsOn();
      delay(dmxDelay);
      turnOutputsOff();
      delay(dmxDelay);
    }
  }
}
//////////////////////////////////////////////////////effect_6
void effect_6(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    int count = 15;
    for (int i = 0; i < 15; i++) {
      ledOff(5);
      registersWrite(redPin[i], HIGH);  // chaser 1
      registersWrite(bluePin[count], HIGH); // chaser 2
      delay(dmxDelay);
      count--;
    }
    count = 15;
    for (int i = 0; i < 15; i++) {
      ledOff(5);
      registersWrite(redPin[i], HIGH);  // chaser 1
      registersWrite(greenPin[i], HIGH);
      registersWrite(bluePin[count], HIGH); // chaser 2
      delay(dmxDelay);
      count--;
    }
    count = 15;
    for (int i = 0; i < 15; i++) {
      ledOff(5);
      registersWrite(redPin[i], HIGH);  // chaser 1
      registersWrite(bluePin[i], HIGH);
      registersWrite(greenPin[count], HIGH); // chaser 2
      delay(dmxDelay);
      count--;
    }
  }
}
//////////////////////////////////////////////////////effect_7
void effect_7(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    int count = 14;
    for (int i = 0; i <= 14; i++) {
      ledOff(0);
      registersWrite(redPin[i], HIGH);  // chaser 1
      registersWrite(redPin[i - 1], HIGH);
      brigtnessNodelay();
      registersWrite(bluePin[count], HIGH); // chaser 2
      registersWrite(bluePin[count - 1], HIGH); // chaser 2
      count--;
      delay(dmxDelay);
    }
  }
}
//////////////////////////////////////////////////////effect_8
void effect_8(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    int count = 14;
    for (int i = 0; i <= 14; i++) {
      Cyan(0, i, 0);
      Cyan(0, i - count, 0);
      brigtnessNodelay();
      Pink(0, count, 0);
      Pink(0, count - i, 0);
      count--;
      delay(dmxDelay);
    }
    brigtnessNodelay();
    count = 14;
    for (int i = 0; i <= 14; i++) {
      Red(0, i, 0);
      Red(0, i - count, 0);
      brigtnessNodelay();
      Yellow(0, count, 0);
      Yellow(0, count - i, 0);
      count--;
      delay(dmxDelay);
    }
    brigtnessNodelay();
    count = 14;
    for (int i = 0; i <= 14; i++) {
      Blue(0, i, 0);
      Blue(0, i - count, 0);
      brigtnessNodelay();
      Green(0, count, 0);
      Green(0, count - i, 0);
      count--;
      delay(dmxDelay);
    }
  }
}
//////////////////////////////////////////////////////effect_9
void effect_9(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i < 15; i++) {
      for (int k = i; k < 15; k++) {
        registersWrite(greenPin[k], HIGH);
        delay(dmxDelay);
        registersWrite(greenPin[k], LOW);
        delay(30);
      }
      //registersWrite(redPin[i], HIGH);
      if (i < 2) {
        Red(0, i, 0);
      }
      if (i < 4) {
        Yellow(2, i, 0);
      }
      if (i < 6) {
        Green(4, i, 0);
      }
      if (i < 7) {
        White(6, i, 0);
      }
      if (i < 8) {
        Cyan(7, i, 0);
      }
      if (i < 10) {
        Blue(8, i, 0);
      }
      if (i < 15) {
        Pink(10, i, 0);
        delay(20);
      }
    }
  }
}
/////////////////////////////////////////////////////Effect_10
void effect_10(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 14; i >= 0; i--) {
      for (int k = 0; k < i; k++) {
        registersWrite(redPin[k], HIGH);
        registersWrite(greenPin[k], HIGH);
        delay(dmxDelay);
        registersWrite(redPin[k], LOW);
        registersWrite(greenPin[k], LOW);
        delay(30);
      }

      registersWrite(bluePin[i], HIGH);
      delay(20);
    }
  }
}
/////////////////////////////////////////////////////Effect 11
void effect_11(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i <= 14; i++) {
      registersWrite(redPin[i], HIGH);
      delay(30);
      registersWrite(redPin[i - 4], LOW);
      delay(dmxDelay);
    } ledOff(0);
    for (int i = 14; i >= 0; i--) {
      registersWrite(bluePin[i], HIGH);
      delay(30);
      registersWrite(bluePin[i + 4], LOW);
      delay(dmxDelay);
    } ledOff(0);
    for (int i = 0; i <= 14; i++) {
      registersWrite(greenPin[i], HIGH);
      delay(30);
      registersWrite(greenPin[i - 4], LOW);
      delay(dmxDelay);
    } ledOff(0);
    for (int i = 14; i >= 0; i--) {
      registersWrite(bluePin[i], HIGH);
      registersWrite(greenPin[i], HIGH);
      registersWrite(redPin[i], HIGH);
      delay(30);
      registersWrite(bluePin[i + 4], LOW);
      registersWrite(greenPin[i + 4], LOW);
      registersWrite(redPin[i + 4], LOW);
      delay(dmxDelay);
    }
  }
}

/////////////////////////////////////////////////////effect_12
void effect_12(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    int count = 14;
    for (int i = 0; i <= 14; i++) {
      registersWrite(bluePin[i], HIGH);  // chaser 1
      registersWrite(bluePin[i - 1], HIGH);
      registersWrite(bluePin[count], HIGH); // chaser 2
      registersWrite(bluePin[count - 1], HIGH); // chaser 2
      count--;
      delay(dmxDelay);
    }
    ledOff(0);
    count = 6;
    for (int i = 6; i >= 0; i--) {
      registersWrite(redPin[i], HIGH);  // chaser 1
      registersWrite(redPin[i - 1], HIGH);
      registersWrite(redPin[count], HIGH); // chaser 2
      registersWrite(redPin[count - 1], HIGH); // chaser 2
      count++;
      delay(dmxDelay);
    }
    ledOff(0);
    count = 14;
    for (int i = 0; i <= 14; i++) {
      registersWrite(greenPin[i], HIGH);  // chaser 1
      registersWrite(greenPin[i - 1], HIGH);
      registersWrite(greenPin[count], HIGH); // chaser 2
      registersWrite(greenPin[count - 1], HIGH); // chaser 2
      count--;
      delay(dmxDelay);
    }
    ledOff(0);
    count = 6;
    for (int i = 6; i >= 0; i--) {
      registersWrite(redPin[i], HIGH);
      registersWrite(bluePin[i], HIGH);
      registersWrite(greenPin[i], HIGH);
      brigtnessNodelay();
      registersWrite(redPin[i - 1], HIGH);
      registersWrite(bluePin[i - 1], HIGH);
      registersWrite(greenPin[i - 1], HIGH);
      brigtnessNodelay();
      registersWrite(redPin[count], HIGH);
      registersWrite(bluePin[count], HIGH);
      registersWrite(greenPin[count], HIGH);
      brigtnessNodelay();
      registersWrite(redPin[count - 1], HIGH);
      registersWrite(bluePin[count - 1], HIGH);
      registersWrite(greenPin[count - 1], HIGH);
      brigtnessNodelay();
      count++;
      delay(dmxDelay);
    }
    ledOff(0);
  }
}
/////////////////////////////////////////////////////effect_13
void effect_13(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i <= 14; i++) {
      for (int k = i; k <= 5; k++)
      {
        registersWrite(redPin[k], HIGH);
        registersWrite(bluePin[14 - k], HIGH);
        delay(dmxDelay);
        registersWrite(redPin[k], LOW);
        registersWrite(bluePin[14 - k], LOW);
        delay(dmxDelay);
      }
      registersWrite(greenPin[i], HIGH);
      registersWrite(bluePin[14 - i], HIGH);
      registersWrite(greenPin[14 - i], HIGH);
    }
  }
}

/////////////////////////////////////////////////////effect_14
void effect_14(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i <= 14; i++) {
      i = i + 1;
      if (i >= 1) {
        registersWrite(redPin[i], HIGH);
      }
      if (i >= 3) {
        registersWrite(redPin[i], HIGH);
        registersWrite(greenPin[i], HIGH);
        registersWrite(bluePin[i], LOW);
      }
      if (i >= 5) {
        registersWrite(greenPin[i], HIGH);
        registersWrite(bluePin[i], LOW);
        registersWrite(redPin[i], LOW);
      }
      if (i >= 7) {
        registersWrite(greenPin[i], HIGH);
        registersWrite(bluePin[i], HIGH);
        registersWrite(redPin[i], LOW);
      }
      if (i >= 9) {
        registersWrite(bluePin[i], HIGH);
        registersWrite(redPin[i], LOW);
        registersWrite(greenPin[i], LOW);
      }
      if (i >= 14) {
        registersWrite(bluePin[i], HIGH);
        registersWrite(redPin[i], HIGH);
        registersWrite(greenPin[i], LOW);
      }
      delay(dmxDelay);
    }
    ledOff(50);
    for (int i = 5; i >= 0; i--) {
      int  j = i * 2;
      if (j == 10) {
        registersWrite(redPin[j], HIGH);
      }
      if (j == 8) {
        registersWrite(redPin[j], HIGH);
        registersWrite(greenPin[j], HIGH);
        registersWrite(bluePin[j], LOW);
      }
      if (j == 6) {
        registersWrite(greenPin[j], HIGH);
        registersWrite(bluePin[j], LOW);
        registersWrite(redPin[j], LOW);
      }
      if (j == 4) {
        registersWrite(greenPin[j], HIGH);
        registersWrite(bluePin[j], HIGH);
        registersWrite(redPin[j], LOW);
      }
      if (j == 2) {
        registersWrite(bluePin[j], HIGH);
        registersWrite(redPin[j], LOW);
        registersWrite(greenPin[j], LOW);
      }
      if (j == 0) {
        registersWrite(bluePin[j], HIGH);
        registersWrite(redPin[j], HIGH);
        registersWrite(greenPin[j], LOW);
      }
      delay(dmxDelay);
    }
    ledOffR(50);
  }
}
/////////////////////////////////////////////////////effect_15
void effect_15(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 14; i >= 0; i--) {
      if (i <= 14) {
        registersWrite(redPin[i], HIGH);
      }
      if (i <= 9) {
        registersWrite(redPin[i], HIGH);
        registersWrite(greenPin[i], HIGH);
        registersWrite(bluePin[i], LOW);
      }
      if (i <= 7) {
        registersWrite(greenPin[i], HIGH);
        registersWrite(bluePin[i], LOW);
        registersWrite(redPin[i], LOW);
      }
      if (i <= 5) {
        registersWrite(greenPin[i], HIGH);
        registersWrite(bluePin[i], HIGH);
        registersWrite(redPin[i], LOW);
      }
      if (i <= 3) {
        registersWrite(bluePin[i], HIGH);
        registersWrite(redPin[i], LOW);
        registersWrite(greenPin[i], LOW);
      }
      if (i <= 0) {
        registersWrite(bluePin[i], HIGH);
        registersWrite(redPin[i], HIGH);
        registersWrite(greenPin[i], LOW);
      }
      delay(dmxDelay);
    }
    ledOffR(10);
    for (int i = 0; i <= 14; i++) {
      if (i >= 0) {
        registersWrite(redPin[i], HIGH);
      }
      if (i >= 2) {
        registersWrite(redPin[i], HIGH);
        registersWrite(greenPin[i], HIGH);
        registersWrite(bluePin[i], LOW);
      }
      if (i >= 4) {
        registersWrite(greenPin[i], HIGH);
        registersWrite(bluePin[i], LOW);
        registersWrite(redPin[i], LOW);
      }
      if (i >= 6) {
        registersWrite(greenPin[i], HIGH);
        registersWrite(bluePin[i], HIGH);
        registersWrite(redPin[i], LOW);
      }
      if (i >= 8) {
        registersWrite(bluePin[i], HIGH);
        registersWrite(redPin[i], LOW);
        registersWrite(greenPin[i], LOW);
      }
      if (i >= 14) {
        registersWrite(bluePin[i], HIGH);
        registersWrite(redPin[i], HIGH);
        registersWrite(greenPin[i], LOW);
      }
      delay(dmxDelay);
    }
    ledOff(10);
  }
}
/////////////////////////////////////////////////////effect_16
void effect_16(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int k = 0; k <= 14; k++) {
      for (int i = 0; i <= k; i++) {
        Red(0, i, 0);
        brigtnessNodelay();
      }
      for (int i = 0; i <= k; i++) {
        Yellow(0, i, 0);
        brigtnessNodelay();
      }
      for (int i = 0; i <= k; i++) {
        Green(0, i, 0);
        brigtnessNodelay();
      }
      for (int i = 0; i <= k; i++) {
        White(0, i, 0);
        brigtnessNodelay();
      }
      for (int i = 0; i <= k; i++) {
        Cyan(0, i, 0);
        brigtnessNodelay();
      }
      for (int i = 0; i <= k; i++) {
        Blue(0, i, 0);
        brigtnessNodelay();
      }
      for (int i = 0; i <= k; i++) {
        Pink(0, i, 0);
        brigtnessNodelay();
      }
    }
  }
}
/////////////////////////////////////////////////////effect_17
void effect_17(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i <= 14; i++) {
      registersWrite(redPin[i], HIGH);
      brigtnessNodelay();
      if (1 <= i) {
        registersWrite(redPin[i - 1], HIGH);
        registersWrite(greenPin[i - 1], HIGH);
        registersWrite(bluePin[i - 1], LOW);
        brigtnessNodelay();
      }
      if (2 <= i) {
        registersWrite(greenPin[i - 2], HIGH);
        brigtnessNodelay();
      }
      if (3 <= i) {
        registersWrite(redPin[i - 3], HIGH);
        registersWrite(greenPin[i - 3], HIGH);
        registersWrite(bluePin[i - 3], HIGH);
        brigtnessNodelay();
      }
      if (4 <= i) {
        registersWrite(greenPin[i - 4], HIGH);
        registersWrite(bluePin[i - 4], HIGH);
        brigtnessNodelay();
      }
      if (5 <= i) {
        registersWrite(bluePin[i - 5], HIGH);
        brigtnessNodelay();
      }
      if (6 <= i) {
        registersWrite(redPin[i - 6], HIGH);
        registersWrite(bluePin[i - 6], HIGH);
        brigtnessNodelay();
      }
      registersWrite(redPin[i], LOW);

      registersWrite(greenPin[i - 1], LOW);
      registersWrite(redPin[i - 1], LOW);

      registersWrite(greenPin[i - 2], LOW);

      registersWrite(redPin[i - 3], LOW);
      registersWrite(greenPin[i - 3], LOW);
      registersWrite(bluePin[i - 3], LOW);

      registersWrite(greenPin[i - 4], LOW);
      registersWrite(bluePin[i - 4], LOW);

      registersWrite(bluePin[i - 5], LOW);

      registersWrite(redPin[i - 6], LOW);
      registersWrite(bluePin[i - 6], LOW);
    }

    for (int i = 14; i >= 0; i--) {
      registersWrite(redPin[i], HIGH);
      brigtnessNodelay();
      if (10 >= i) {
        registersWrite(redPin[i + 1], HIGH);
        registersWrite(greenPin[i + 1], HIGH);
        registersWrite(bluePin[i + 1], LOW);
        brigtnessNodelay();
      }
      if (9 >= i) {
        registersWrite(greenPin[i + 2], HIGH);
        brigtnessNodelay();
      }
      if (8 >= i) {
        registersWrite(redPin[i + 3], HIGH);
        registersWrite(greenPin[i + 3], HIGH);
        registersWrite(bluePin[i + 3], HIGH);
        brigtnessNodelay();
      }
      if (7 >= i) {
        registersWrite(greenPin[i + 4], HIGH);
        registersWrite(bluePin[i + 4], HIGH);
        brigtnessNodelay();
      }
      if (6 >= i) {
        registersWrite(bluePin[i + 5], HIGH);
        brigtnessNodelay();
      }
      if (5 >= i) {
        registersWrite(redPin[i + 6], HIGH);
        registersWrite(bluePin[i + 6], HIGH);
        brigtnessNodelay();
      }
      registersWrite(redPin[i], LOW);

      registersWrite(greenPin[i + 1], LOW);
      registersWrite(redPin[i + 1], LOW);

      registersWrite(greenPin[i + 2], LOW);

      registersWrite(redPin[i + 3], LOW);
      registersWrite(greenPin[i + 3], LOW);
      registersWrite(bluePin[i + 3], LOW);

      registersWrite(greenPin[i + 4], LOW);
      registersWrite(bluePin[i + 4], LOW);

      registersWrite(bluePin[i + 5], LOW);

      registersWrite(redPin[i + 6], LOW);
      registersWrite(bluePin[i + 6], LOW);
    }
  }
}
//////////////////////////////////////////////////////effect_18
void effect_18(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i <= 14; i++) {
      registersWrite(redPin[i], HIGH);
      i++;
      registersWrite(greenPin[i], HIGH);
      delay(dmxDelay);
      registersWrite(redPin[i - 4], LOW);
      delay(dmxDelay);
    } ledOff(0);
    for (int i = 14; i >= 0; i--) {
      registersWrite(bluePin[i], HIGH);
      i--;
      registersWrite(redPin[i], HIGH);
      delay(dmxDelay);
      registersWrite(bluePin[i + 4], LOW);
      delay(dmxDelay);
    }
  }
}
/////////////////////////////////////////////////////effect_19
void effect_19(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    Red(0, 1, 0);
    Yellow(2, 3, 0);
    Green(4, 5, 0);
    White(6, 6, 0);
    Cyan(7, 7, 0);
    Blue(8, 9, 0);
    Pink(10, 11, 0);
    //brigtness();
  }
}
/////////////////////////////////////////////////////effect_20
void effect_20(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    for (int i = 0; i <= 14; i++) {
      registersWrite(redPin[i], HIGH);
      brigtnessNodelay();
      if (1 <= i) {
        registersWrite(redPin[i - 1], HIGH);
        registersWrite(greenPin[i - 1], HIGH);
        registersWrite(bluePin[i - 1], LOW);
        brigtnessNodelay();
      }
      if (2 <= i) {
        registersWrite(greenPin[i - 2], HIGH);
        brigtnessNodelay();
      }
      if (3 <= i) {
        registersWrite(redPin[i - 3], HIGH);
        registersWrite(greenPin[i - 3], HIGH);
        registersWrite(bluePin[i - 3], HIGH);
        brigtnessNodelay();
      }
      if (4 <= i) {
        registersWrite(greenPin[i - 4], HIGH);
        registersWrite(bluePin[i - 4], HIGH);
        brigtnessNodelay();
      }
      if (5 <= i) {
        registersWrite(bluePin[i - 5], HIGH);
        brigtnessNodelay();
      }
      if (6 <= i) {
        registersWrite(redPin[i - 6], HIGH);
        registersWrite(bluePin[i - 6], HIGH);
        brigtnessNodelay();
      }
      registersWrite(redPin[i], LOW);

      registersWrite(greenPin[i - 1], LOW);
      registersWrite(redPin[i - 1], LOW);

      registersWrite(greenPin[i - 2], LOW);

      registersWrite(redPin[i - 3], LOW);
      registersWrite(greenPin[i - 3], LOW);
      registersWrite(bluePin[i - 3], LOW);

      registersWrite(greenPin[i - 4], LOW);
      registersWrite(bluePin[i - 4], LOW);

      registersWrite(bluePin[i - 5], LOW);

      registersWrite(redPin[i - 6], LOW);
      registersWrite(bluePin[i - 6], LOW);
    }
  }
}

//////////////////////Functions/////////////////////
void brigtnessNodelay() {
  for (int i = 255; i >= 0; i--) {
    analogWrite(enablePin, i);
  }
}
void brigtness() {
  for (int i = 255; i >= 0; i--) {
    analogWrite(enablePin, i);
    delay(5);
  }
}

void ledOff(int clearSpeed) {
  for (int i = 0; i <= 44; i++) {
    registersWrite(i, LOW);
    delay(clearSpeed);
  }
}
void ledOffR(int clearSpeed) {
  for (int i = 44; i >= 0; i--) {
    registersWrite(i, LOW);
    delay(clearSpeed);
  }
}

void turnOutputsOn() {
  digitalWrite(enablePin, LOW);
}
void turnOutputsOff() {
  digitalWrite(enablePin, HIGH);
}

void registersWrite(int index, int value) {
  digitalWrite(enablePin, LOW);
  digitalWrite(latchPin, LOW);
  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    digitalWrite(clockPin, LOW);
    int val = registers[i];
    digitalWrite(dataPin, val);
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH);
  registers[index] = value;
}

void Red(int startPin, int endPin, int ledBT) {
  for (byte count = startPin; count <= endPin; count++) {
    registersWrite(redPin[count], HIGH);
    registersWrite(bluePin[count], LOW);
    registersWrite(greenPin[count], LOW);
  }
}

void Pink(int startPin, int endPin, int ledBT) {
  for (byte count = startPin; count <= endPin; count++) {
    registersWrite(redPin[count], HIGH);
    registersWrite(bluePin[count], HIGH);
    registersWrite(greenPin[count], LOW);
    delay(ledBT);
  }
}

void Green(int startPin, int endPin, int ledBT) {
  for (byte count = startPin; count <= endPin; count++) {
    registersWrite(greenPin[count], HIGH);
    registersWrite(redPin[count], LOW);
    registersWrite(bluePin[count], LOW);
    delay(ledBT);
  }
}

void Yellow(int startPin, int endPin, int ledBT) {
  for (byte count = startPin; count <= endPin; count++) {
    registersWrite(redPin[count], HIGH);
    registersWrite(greenPin[count], HIGH);
    registersWrite(bluePin[count], LOW);
    delay(ledBT);
  }
}

void Blue(int startPin, int endPin, int ledBT) {
  for (byte count = startPin; count <= endPin; count++) {
    registersWrite(bluePin[count], HIGH);
    registersWrite(redPin[count], LOW);
    registersWrite(greenPin[count], LOW);
    delay(ledBT);
  }
}
void Cyan(int startPin, int endPin, int ledBT) {
  for (byte count = startPin; count <= endPin; count++) {
    registersWrite(greenPin[count], HIGH);
    registersWrite(bluePin[count], HIGH);
    registersWrite(redPin[count], LOW);
    delay(ledBT);
  }
}

void White(int startPin, int endPin, int ledBT) {
  for (byte count = startPin; count <= endPin; count++) {
    registersWrite(redPin[count], HIGH);
    registersWrite(greenPin[count], HIGH);
    registersWrite(bluePin[count], HIGH);
    delay(ledBT);
  }
}
