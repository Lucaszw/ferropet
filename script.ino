#include <IRremote.h>

int IRpin = A3;
IRrecv irrecv(IRpin);
decode_results results;


typedef void (*VoidFunctionWithNoParams) ();
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

int val = 0;

void reset() {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
}

void red() {
  reset();
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
}

void green() {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
}

void blue() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
}

void purple() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
}

void acqua() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
}


void pushE(){
  digitalWrite(EIN1, HIGH);
  digitalWrite(EIN2, LOW);
}

void pullE() {
  digitalWrite(EIN1, LOW);
  digitalWrite(EIN2, HIGH);
}

void pullF() {
  digitalWrite(FIN1, LOW);
  digitalWrite(FIN2, HIGH);
}

void pushF() {
  digitalWrite(FIN1, HIGH);
  digitalWrite(FIN2, LOW);
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
VoidFunctionWithNoParams funcs[] = {pullA, pullE, pullB, pullC};
VoidFunctionWithNoParams funcs2[] = {pushA, pushE, pushB, pushC};

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
}

void turnOff() {
  allOff();
  reset();
}

void moveUpFromCenter(int t=300, bool split=true) {
  pushC();
  pullA();
  pullB();
  if (split) {
      delay(t);
      pushA(); 
  }
}

void moveDownFromCenter(int t=300, bool split=true) {
  pushC();
  pullE();
  pullD();
  if (split) {
    delay(t);
    pushE();
  }
}

void moveUpFromBottom(int t=300, bool split=true) {
  pushD();
  pullE();
  pullC();
  if (split) {
    delay(t);
    pushE(); 
  }
}

void moveDownFromTop(int t=300, bool split=true) {
  pushB();
  pullA();
  pullC();
  if (split) {
    delay(t);
    pushA(); 
  }
}

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  allOff();
}

void anim1() {
  int t = 200;
  moveUpFromCenter(t);
  delay(t);
  allOff();
  moveDownFromTop(t);
  delay(t);
  allOff();
  delay(t);
  moveDownFromCenter(t);
  delay(t);
  allOff();
  moveUpFromBottom(t);
  delay(t);
  allOff();
  delay(t);
}

void anim2() {
  int t = 800;
  moveUpFromCenter(t, false);
  moveDownFromCenter(t, false);
  delay(t);
  allOff();
  delay(t);
}


void down2(int t) {
  pushC();
  pushE();
  pullC();
  pullE();
  pushE();
  pullC();
  pushE();
  delay(t);
//  allOff();
  
}

void up2(int t) {
  pullC();
  pullA();
  delay(t);
  pushC();
  pullA();
  delay(t);
  allOff();
}

int index = 0;

void pwm(VoidFunctionWithNoParams funcs[], int num) {
  for (int j=0;j<1;j++) {
    for (int i=0;i<num;i++) {
//      allOff();
//      delay(1);
      funcs[i]();
//      delay(1);
    }
//    delay(3*num);
//    allOff();
//    delay(3*num);
  }
}

void dancing() {
  int t = 350;
  for (int i=2;i<4;i++) {
    pullD();
    delay(t);
    VoidFunctionWithNoParams a[] = {allOff, pushD, funcs[i], funcs[i-2]};
    pwm(a, 4);
//    allOff();
//    pushD();
//    funcs[i]();
//    funcs[i-2]();
    delay(t);
    VoidFunctionWithNoParams b[] = {funcs2[i], funcs2[i-2], pullD};
    pwm(b, 3);
//    funcs2[i]();
//    funcs2[i-2]();
//    pullD();
    delay(t);
    pushD();
//    delay(t);
//    allOff();
  }
//  delay(t);
//  allOff();

//  int t = 200;
////  int index = random(4);
//  allOff();
//  pullD();
//  delay(t*0.75);
////  for (int i=0;i<4;i+=2) funcs2[i]();
////  for (int i=0;i<4;i++) {
////    if (i != index) funcs2[i]();  
////  }
////  delay(100);
////  delay(10);
//  allOff();
//  funcs[index]();
//  delay(t);
//  pushD();
//  if (index < 2) funcs[index+2]();
//  else funcs[index-2]();
////  delay(t/3);
////  allOff();
////  pushD();
//  delay(t);
////  funcs2[index]();
//  pullD();
//  delay(t*3);
//  index ++;
//  if (index >= 4) index = 0;
}

void calm(int s = 500) {
  purple();
  allOff();
  pullA();
  pullE();
  delay(s);
  allOff();
  pullE();
  pullB();
  delay(s);
  allOff();
  pullE();
  pullD();
  delay(s);

  // invert
  allOff();
  pushD();
  pushE();
  delay(s);
  allOff();
  pushB();
  pushE();
  delay(s);
  allOff();
  pushE();
  pushB();
  delay(s);
}
void theSplit(int s = 500) {
  blue();
  allOff();
  pullF();
  pushD();
  pullE();
  delay(s);
  pullD();
  pushE();
  delay(s);
  allOff();
  pushF();
  delay(s);

  // invert
  allOff();
  pullF();
  delay(s);
  pullE();
  pushD();
  delay(s);
  allOff();
  pushE();
  pullD();
  pushF();
  delay(s);
}

void pulseCenter(int s = 500) {
  green();
  delay(s);
  pushE();
  delay(s);
  pullE();
  delay(s);
}

void pulseFlow(int s = 500) {
  green();
  allOff();
  pullD();
  pullB();
  delay(s);
  pushD();
  pushB();
  delay(s);
  pushD();
  pushE();
  delay(s);

  // invert
  pullD();
  pullE();
  delay(s);
  pullD();
  pullB();
  delay(s);
  allOff();
  pushB();
  pushD();
  delay(s);
}

void theSeasons(int s=500) {
  turnOff();
  red();
  pushC();
  delay(s);
  allOff();
  pullB();
  delay(s);
  allOff();
  pushC();
  pullE();
  delay(s);
  allOff();
  pullC();
  delay(s);
}
void offWait() {
  allOff();
  delay(50);
}

int loopId = 10 ;
int danceSpeed = 500;

void AA(int s = 500) {
    pullA();
    delay(danceSpeed);
    pushA();
    delay(danceSpeed);
}
void BB(int s = 500) {
  pullB();
  delay(s);
  pushB();
  delay(s);
}

void CC(int s = 500) {
  pullC();
  delay(s);
  pushC();
  delay(s);
}
void DD(int s = 500) {
  pullD();
  delay(s);
  pushD();
  delay(s);
}

void line(int s= 500) {
  acqua();
  pushD();
  pushC();
  pullA();
  delay(s);
  pullD();
  pushC();
  pushA();
  delay(s);
}

void checkRemote() {
    if (irrecv.decode(&results)) 
    {
      Serial.println(results.value, DEC); // Print the Serial 'results.value'
      irrecv.resume();   // Receive the next value

      if (results.value == 16187647) danceSpeed += 50;
      if (results.value == 16220287) danceSpeed -= 50;
      if (results.value == 16203967) loopId = -1;
      if (results.value == 16236607) loopId = 10;
      if (results.value == 16195807) loopId = 1;
      if (results.value == 16228447) loopId = 2;
      if (results.value == 16212127) loopId = 3;
      if (results.value == 16199887) loopId = 4;
      if (results.value == 16232527) loopId = 5;
      if (results.value == 16216207) loopId = 6;
      if (results.value == 16189687) loopId = 7;
      if (results.value == 16191727) loopId = 8;
      if (results.value == 16224367) loopId = 9;
      if (danceSpeed > 1000) danceSpeed = 1000;
      if (danceSpeed < 50) danceSpeed = 50;
      Serial.println(danceSpeed);
    }
}
void loop() {
    checkRemote();
    turnOff();
    if (loopId == -1) turnOff();
    if (loopId == 1 || loopId == 10) theSeasons(danceSpeed); turnOff(); checkRemote();
    if (loopId == 2 || loopId == 10) pulseFlow(danceSpeed); turnOff(); checkRemote();
    if (loopId == 3 || loopId == 10) theSplit(danceSpeed); turnOff(); checkRemote();
    if (loopId != -1) purple();
    if (loopId == 4) AA(danceSpeed);
    if (loopId == 5) BB(danceSpeed);
    if (loopId == 6) CC(danceSpeed);
    if (loopId == 7) DD(danceSpeed);
    reset();
    if (loopId == 8 || loopId == 10) line(danceSpeed); turnOff(); checkRemote();
    if (loopId == 9 || loopId == 10) calm(danceSpeed); turnOff(); checkRemote();

//    pushC();
//    delay(200);
//    pullC();
//    pushE();
//    delay(500);
//    pushC();
//    pullE();
//    delay(500);
//      blue();
//      pullE();
//      delay(500);
//      pushE();
//      delay(500);
//
}