#include <Adafruit_NeoPixel.h>
#include <IRremote.h>
 
#define NUMPIXELS 3
#define TOTALPROGRAMS 11

#define SLEEPINTERVAL 5
#define SLEEPTIME 3000

#define OFFINTERVAL 1000
#define OFFTIME 300000  

#define POWER 16621663
#define BACK 16615543
#define FORWARD 16625743

Adafruit_NeoPixel pixels(NUMPIXELS, A0, NEO_GRB + NEO_KHZ800);
typedef void (*VoidFunctionWithNoParams) ();
typedef void (*VoidFunctionWithOneParam) (int);

int IRpin = A3;
IRrecv irrecv(IRpin);
decode_results results;

int currentProgram = 0;
int colorIndex = 0;
int frames = 0;
int offFrames = 0;
bool colorCycleSet = false;

int AIN2 = 5;
int AIN1 = 4;

int BIN2 = 7;
int BIN1 = 6;

int CIN2 = 10;
int CIN1 = 11;

int DIN2 = 9;
int DIN1 = 8;

int EIN2 = 3;
int EIN1 = 2;

int FIN2 = 12;
int FIN1 = 13;

void pushE(){
  digitalWrite(EIN1, HIGH);
  digitalWrite(EIN2, LOW);
}

void pullE() {
  digitalWrite(EIN1, LOW);
  digitalWrite(EIN2, HIGH);
}

void pullF() {
  digitalWrite(FIN1, HIGH);
  digitalWrite(FIN2, LOW);
}

void pushF() {
  digitalWrite(FIN1, LOW);
  digitalWrite(FIN2, HIGH);
}
void pushD() {
  digitalWrite(DIN1, HIGH);
  digitalWrite(DIN2, LOW); 
}
void pullD() {
  digitalWrite(DIN1, LOW);
  digitalWrite(DIN2, HIGH);
}
void pushA() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
}

void pushB() {
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void pullB() {
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}


void pullA() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
}

void turnOnC() {
  digitalWrite(CIN1, HIGH);
  digitalWrite(CIN2, LOW);
}

void invertC() {
  digitalWrite(CIN1, LOW);
  digitalWrite(CIN2, HIGH);
}

void pushC() {
  digitalWrite(CIN1, HIGH);
  digitalWrite(CIN2, LOW);
}

void pullC() {
  digitalWrite(CIN1, LOW);
  digitalWrite(CIN2, HIGH);
}



//VoidFunctionWithNoParams funcs[] = {pushE, pullE, pushC, pullC, pushB, pullB, pushA, pullA};
VoidFunctionWithNoParams funcs[] = {pullA, pullE, pullF, pullC};
VoidFunctionWithNoParams funcs2[] = {pushA, pushE, pushF, pushC};

void allOff() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  digitalWrite(CIN1, LOW);
  digitalWrite(CIN2, LOW);
  digitalWrite(DIN1, LOW);
  digitalWrite(DIN2, LOW);
  digitalWrite(EIN1, LOW);
  digitalWrite(EIN2, LOW);
  digitalWrite(FIN1, LOW);
  digitalWrite(FIN2, LOW);
}


void updateColorIndex() {
  if (colorCycleSet == true) {
    if (colorIndex == 15)  {
      colorIndex = 0;
    }
    else {
      colorIndex += 1;      
    }
    return;
  }

  colorIndex = random(0,16);
  colorCycleSet = true;
}

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  
  // put your setup code here, to run once:
  pinMode(A0, OUTPUT);
  colorIndex = 9;
}

boolean checkRemoteAndSleep(int sleep=300) {
  random(0,16);
  for (int i=0;i<20;i++) {
     if (i*100 >= sleep) return false;
 
     if (irrecv.decode(&results)) {
      Serial.println(results.value, DEC);
      if (results.value == POWER) {
        frames = 0;
        offFrames = 0;
        colorCycleSet = false;
        Serial.println("Power button pressed.");
        updateColorIndex();
        if (currentProgram == -1) currentProgram = 0;
        else currentProgram = -1;
        irrecv.resume();
        return true;
      } else if (results.value == BACK) {
        updateColorIndex();
        frames = 0;
        offFrames = 0;
        currentProgram -= 1;
        if (currentProgram == -1) currentProgram = TOTALPROGRAMS-1;
        irrecv.resume();
        return true;
      } else if (results.value == FORWARD) {
        frames = 0;
        offFrames = 0;
        currentProgram += 1;
        updateColorIndex();
        if (currentProgram >= TOTALPROGRAMS) currentProgram = 0;
        irrecv.resume();
        return true;
      }
      irrecv.resume();
    }
    delay(100);
  }
  return false;
}


void setColor() {
  switch (colorIndex) {
    case 0:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(50, 20, 100));
      pixels.setPixelColor(1, pixels.Color(50, 50, 100));
      pixels.setPixelColor(2, pixels.Color(50, 20, 100));
      pixels.show();
      break;
    case 1:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(100, 20, 100));
      pixels.setPixelColor(1, pixels.Color(100, 50, 100));
      pixels.setPixelColor(2, pixels.Color(100, 20, 100));
      pixels.show();
      break;
    case 2:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(100, 0, 0));
      pixels.setPixelColor(1, pixels.Color(100, 0, 0));
      pixels.setPixelColor(2, pixels.Color(100, 0, 0));
      pixels.show();
      break;
    case 3:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(0, 100, 0));
      pixels.setPixelColor(1, pixels.Color(0, 100, 0));
      pixels.setPixelColor(2, pixels.Color(0, 100, 0));
      pixels.show();
      break;
    case 4:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(0, 0, 100));
      pixels.setPixelColor(1, pixels.Color(0, 0, 100));
      pixels.setPixelColor(2, pixels.Color(0, 0, 100));
      pixels.show();
      break;
    case 5:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(50, 50, 50));
      pixels.setPixelColor(1, pixels.Color(50, 50, 50));
      pixels.setPixelColor(2, pixels.Color(50, 50, 50));
      pixels.show();
      break;
    case 6:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(144, 238, 144));
      pixels.setPixelColor(1, pixels.Color(144, 238, 144));
      pixels.setPixelColor(2, pixels.Color(144, 238, 144));
      pixels.show();
      break;
    case 7:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(255, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 255, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 255));
      pixels.show();
      break;
    case 8:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(255, 69, 0));
      pixels.setPixelColor(1, pixels.Color(255, 69, 0));
      pixels.setPixelColor(2, pixels.Color(255, 69, 0));
      pixels.show();
      break;
    case 9:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(255, 255, 255));
      pixels.setPixelColor(1, pixels.Color(255, 255, 255));
      pixels.setPixelColor(2, pixels.Color(255, 255, 255));
      pixels.show();
      break;
    case 10:
      pixels.begin();
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(119, 69, 19));
      pixels.setPixelColor(1, pixels.Color(119, 69, 19));
      pixels.setPixelColor(2, pixels.Color(119, 69, 19));
      pixels.show();
    case 11:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(8, 136, 8));
      pixels.setPixelColor(1, pixels.Color(8, 70, 70));
      pixels.setPixelColor(2, pixels.Color(8, 8, 136));
      pixels.show();
      break;
    case 12:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(50, 130, 10));
      pixels.setPixelColor(1, pixels.Color(50, 130, 10));
      pixels.setPixelColor(2, pixels.Color(50, 130, 10));
      pixels.show();
      break;
    case 13:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(139, 69, 19));
      pixels.setPixelColor(1, pixels.Color(139, 69, 19));
      pixels.setPixelColor(2, pixels.Color(139, 69, 19));
      pixels.show();
      break;
    case 14:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(175, 0, 42));
      pixels.setPixelColor(1, pixels.Color(175, 0, 42));
      pixels.setPixelColor(2, pixels.Color(175, 0, 42));
      pixels.show();
      break;
    case 15:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(255, 255, 0));
      pixels.setPixelColor(1, pixels.Color(255, 255, 0));
      pixels.setPixelColor(2, pixels.Color(255, 255, 0));
      pixels.show();
      break;
    default:
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(255, 255, 255));
      pixels.setPixelColor(1, pixels.Color(255, 255, 255));
      pixels.setPixelColor(2, pixels.Color(255, 255, 255));
      pixels.show();
      break;
  }

}
void program1(int speed=300) {
  int k = 0;
  for (int i=0;i<20;i++) {
    pushD();
    if ((i % 2) == 0) {
      funcs2[k]();
    } else {
      allOff();
      funcs[k]();
    }
    if (checkRemoteAndSleep(speed/2)) return;
    allOff();
    pullD();
    if (checkRemoteAndSleep(speed/2)) return;
    if ( ( (i+1) % 5) == 0) {
      k += 1;
      allOff();
      checkRemoteAndSleep(500);
    }
  }
  allOff();
  checkRemoteAndSleep(5000);
}

void program2(int speed=300) {
  int k = 0;
  for (int i=0;i<10;i++) {
    pushD();
    if (checkRemoteAndSleep(speed/2)) return;
    allOff();
    if (checkRemoteAndSleep(speed/2)) return;
    pullD();
    if (checkRemoteAndSleep(speed/2)) return;
  }
  allOff();
  checkRemoteAndSleep(1000);
}

void program3(int sleep=300) {
  pullF();
  pushD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
  pushF();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
  pushD();
  pullC();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
  pushC();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
}

void program4(int sleep=300) {
  pullA();
  pushD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushA();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushD();
  pushC();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pullC();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
}

void program5(int sleep=300) {

  pullF();
  pushD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushF();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushD();
  pullE();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushE();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
}

void program6(int sleep=300) {
  pullA();
  pushD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushA();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushD();
  pullE();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();  
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushE();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
}

void program7(int sleep=300) {
  pullC();
  pushD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushC();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushD();
  pullF();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();    
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushF();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
}

void program8(int sleep=300) {
  pullA();
  pushD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushA();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushD();
  pullF();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushF();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
}

void program9(int sleep=300) {
  pullC();
  pushD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushC();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushD();
  pullE();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  pushE();
  pullD();
  if (checkRemoteAndSleep(sleep)) return;
  allOff();
  if (checkRemoteAndSleep(sleep)) return;
}

void program10(int sleep=300) {
  allOff();
  pullA();
  if (checkRemoteAndSleep(sleep/2)) return;
  allOff();
  pullC();
  if (checkRemoteAndSleep(sleep/2)) return;
  allOff();
  pullF();
  if (checkRemoteAndSleep(sleep/2)) return;
  allOff();
  pullE();
  if (checkRemoteAndSleep(sleep/2)) return;
  allOff();
  pushA();
  if (checkRemoteAndSleep(sleep/2)) return;
  allOff();
  pushC();
  if (checkRemoteAndSleep(sleep/2)) return;
  allOff();
  pushF();
  if (checkRemoteAndSleep(sleep/2)) return;
  allOff();
  pushE();
  if (checkRemoteAndSleep(sleep/2)) return;
  allOff();
  if (checkRemoteAndSleep(sleep/2)) return;
}


void program11(int sleep=300) {
  for (int j = 0;j<3;j++) {
    for (int i = 0; i < 2; i++) {
      if (checkRemoteAndSleep(sleep/6)) return;
      allOff();
      pullA();
      if (checkRemoteAndSleep(sleep/6)) return;
      allOff();
      pullC();
    }
    //
    for (int i = 0; i < 2; i++) {
      if (checkRemoteAndSleep(sleep/6)) return;
      allOff();
      pullF();
      if (checkRemoteAndSleep(sleep/6)) return;
      allOff();
      pullE();
    }
    //
    for (int i = 0; i < 2; i++) {
      if (checkRemoteAndSleep(sleep/6)) return;
      allOff();
      pushA();
      if (checkRemoteAndSleep(sleep/6)) return;
      allOff();
      pushC();
    }
    //
    for (int i = 0; i < 2; i++) {
      if (checkRemoteAndSleep(sleep/6)) return;
      allOff();
      pushF();
      if (checkRemoteAndSleep(sleep/6)) return;
      allOff();
      pushE();
    }
    //
    if (checkRemoteAndSleep(sleep/6)) return;
    allOff();
  }
  
  if (checkRemoteAndSleep(sleep)) return;
}


VoidFunctionWithOneParam programs[] = {program10, program1, program2, program3, program4, program5, program6, program7, program8, program9, program11};

void loop() {
  if (currentProgram == -1) {
      allOff();
      pixels.begin();
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.setPixelColor(1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(2, pixels.Color(0, 0, 0));
      pixels.show();
      checkRemoteAndSleep(100);
      return;
  }

  if (frames >= SLEEPINTERVAL) {
    allOff();
    for (int i=0;i<SLEEPTIME/500;i++) {
          if (checkRemoteAndSleep(500)) break;
    }
    frames = 0;
    currentProgram += 1;
    if (currentProgram >= TOTALPROGRAMS) currentProgram = 0;
    updateColorIndex();
    setColor();
  } 
  else if (offFrames >= OFFINTERVAL) {
    allOff();
    for (int i=0;i<OFFTIME/500;i++) {
          if (checkRemoteAndSleep(500)) break;
    }
    offFrames = 0;
  }
  
  allOff();
  setColor();
  programs[currentProgram](500);
  frames += 1;
  offFrames += 1;
}

//void loop() {
//  int sleep = 300;
//  pullE();
//  //pushD();
//  if (checkRemoteAndSleep(sleep)) return;
//  pushE();
//  //pullD();
//  if (checkRemoteAndSleep(sleep)) return;
//}
