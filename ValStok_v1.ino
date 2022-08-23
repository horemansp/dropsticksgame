int sequence = 0;
//ESP32 DEVKIT v1
int stickList[] = {12,13,14,15,16,17,18,19};
int stick[] = {12,13,14,15,16,17,18,19};


int stickLeft = 8;
int randomNumber;
int randomTime;
int stickTemp[8];
int stickSeq;
int progSeq = 0;
int button = 32;
int progStartLed = 23;
int progPrepareLed = 22;
int buzPin = 21;


void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Starting program");
  for(int x=0;x<8;x++){
      pinMode(stick[x], OUTPUT);
    }
  pinMode(button, INPUT_PULLUP);
  pinMode(progStartLed, OUTPUT);
  pinMode(buzPin, OUTPUT);
  digitalWrite(progStartLed, HIGH);
  pinMode(progPrepareLed, OUTPUT);
  digitalWrite(progPrepareLed, HIGH);
  digitalWrite(buzPin, LOW);
  delay(1000);
}

void printSticksLeft(int sticksLeft){
  for(int i=0;i<sticksLeft;i++){
  Serial.print(stick[i]);Serial.print(",");
  }
  Serial.println(" ");
  Serial.println("----------------------");
}

void loop() {
  if( !digitalRead(button) && progSeq != 3){
    Serial.println("Button pressed, advancing sequence");
    progSeq++;
    delay(1000);
    }

  if(progSeq == 1){
    digitalWrite(progPrepareLed, LOW);
    for(int x=0;x<8;x++){
        digitalWrite(stickList[x], HIGH);
        stick[x]=stickList[x];
      }
      stickLeft=8;
      Serial.println("Hang sticks and press button when finished");
      progSeq++;
      delay(1000);
    }



  if(progSeq == 3){
    if(stickLeft>0){
      if(stickLeft == 8){
        digitalWrite(progPrepareLed, HIGH);
        digitalWrite(progStartLed, LOW);
        Serial.println("Starting stick drops");
        for(int j=0; j<4;j++){
            digitalWrite(buzPin, HIGH);
            delay(300);
            digitalWrite(buzPin, LOW);
            delay(500);
          }
        digitalWrite(buzPin, HIGH);
        delay(2000);
        digitalWrite(buzPin, LOW);
        
      }
      printSticksLeft(stickLeft);
      randomTime = random(3000,10000);
      delay(randomTime); 
      randomNumber=random(stickLeft);
      Serial.print("Stick to drop=");Serial.println(stick[randomNumber]);
      digitalWrite(stick[randomNumber], LOW);
      stickSeq=0;
      for(int x=0;x<stickLeft+1;x++){
        if(x!=randomNumber){
          stick[stickSeq]=stick[x];
          stickSeq++;
        }
      }
      stickLeft--;
      if(stickLeft ==0){
          progSeq=0;
          digitalWrite(progStartLed, HIGH);
          Serial.println("Program finished, press button to start over");
          delay(1000);
        }
      
    }
  }
}
