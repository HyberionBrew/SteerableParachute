const uint8_t RotEnc1A = 2;
const uint8_t RotEnc1B = 3;

const uint8_t RotEnc2A = 20;
const uint8_t RotEnc2B = 21;

const uint8_t LATCHSTATE = 3;
const uint8_t LATCHSTATE2 = 3;
int8_t oldState = 3;
int8_t oldState2 = 3;

const int8_t KNOBDIR[] = {
  0, -1,  1,  0,
  1,  0,  0, -1,
 -1,  0,  0,  1,
  0,  1, -1,  0};

  const int8_t KNOBDIR2[] = {
  0, -1,  1,  0,
  1,  0,  0, -1,
 -1,  0,  0,  1,
  0,  1, -1,  0};
  
int positionInternal = 0;
int oldPositionExternal = 0;

int positionInternal2 = 0;
int oldPositionExternal2 = 0;

void setupEncoders(){
  //init Rotary Encoder
  //Pull-up resistors
  digitalWrite(RotEnc1A, HIGH);
  digitalWrite(RotEnc1B, HIGH);

  pinMode(RotEnc1A, INPUT);
  pinMode(RotEnc1B, INPUT);
  attachInterrupt(digitalPinToInterrupt(RotEnc1A),listenEncoder1 , CHANGE);
  attachInterrupt(digitalPinToInterrupt(RotEnc1B), listenEncoder1, CHANGE);

  //turn on Pull-up resistors
  digitalWrite(RotEnc2A, HIGH);
  digitalWrite(RotEnc2B, HIGH);
  
  pinMode(RotEnc2A, INPUT);
  pinMode(RotEnc2B, INPUT);

  attachInterrupt(digitalPinToInterrupt(RotEnc2A), listenEncoder2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RotEnc2B), listenEncoder2, CHANGE);
  }
  
void listenEncoder1() {
  // see https://forum.arduino.cc/index.php?topic=389243.0 
  // post on Mar 31, 2016, 5:50 pm
  
  int sigA = digitalRead(RotEnc1A);
  int sigB = digitalRead(RotEnc1B);
  int8_t thisState = sigA | (sigB << 1);

  if (oldState != thisState) {
    positionInternal += KNOBDIR[thisState | (oldState<<2)];
    if (thisState == LATCHSTATE)
      positionEnc1 = positionInternal >> 2;   
    oldState = thisState;
  }
}
void listenEncoder2() {
  // see listenEncoder1
  //debouncer
  int sigA2 = digitalRead(RotEnc2A);
  int sigB2 = digitalRead(RotEnc2B);
  int8_t thisState2 = sigA2 | (sigB2 << 1);

  if (oldState2 != thisState2) {
    positionInternal2 += KNOBDIR2[thisState2 | (oldState2<<2)];
    if (thisState2 == LATCHSTATE2)
      positionEnc2 = positionInternal2 >> 2;   
    oldState2 = thisState2;
  }
  }
