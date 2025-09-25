#define LED1_PIN 2
#define LED2_PIN 3

unsigned long blinkInterval[2] = {500, 1000};

int LED1State = LOW;
int LED2State = LOW;

unsigned long previousTime1 = millis();
unsigned long previousTime2 = millis();

int askingLED = 1;
int askingDuration = 0;


int LEDToChange = 0;
unsigned long changeBlinkInterval = 0;

int LED2Time = millis();

void blinkLED1();
void blinkLED2();
void setDuration();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  Serial.println("What LED?");
  Serial.flush();
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()){
    setDuration();
  }

  if(millis() - previousTime1 > blinkInterval[0]){
    blinkLED1();
    previousTime1 = millis();
  }
  if(millis() - previousTime2 > blinkInterval[1]){
    blinkLED2();
    previousTime2 = millis();
  }

}


void blinkLED1(){
  if(LED1State == LOW){
    LED1State = HIGH;
  }
  else{
    LED1State = LOW;
  }
  digitalWrite(LED1_PIN, LED1State);
}

void blinkLED2(){
  if(LED2State == LOW){
    LED2State = HIGH;
  }
  else{
    LED2State = LOW;
  }
  digitalWrite(LED2_PIN, LED2State);
}

void setDuration(){
  if(askingLED != 0){
    int whatLED = Serial.parseInt();
    if(whatLED == 1 || whatLED == 2){
      LEDToChange = whatLED;
      Serial.println("What interval (in msec)");
      askingLED = 0;
      askingDuration = 1;
    }
  }
  else if(askingDuration != 0){
    int interval = Serial.parseInt();
    if(interval > 0){
      blinkInterval[LEDToChange - 1] = interval;
      Serial.println("What LED?");
      askingDuration = 0;
      askingLED = 1;
    }
  }
}
