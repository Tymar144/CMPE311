#define LED1_PIN 2
#define LED2_PIN 3
#define NUM_TASKS 3
#define EXECUTIVE_CYCLE_TIME 50

unsigned long blinkInterval[2] = {500, 1000};

int LED1State = LOW;
int LED2State = LOW;


unsigned long currentTime = millis();
unsigned long previousTime1 = millis();
unsigned long previousTime2 = millis();
unsigned long previousCycleTime = 0;

int askingLED = 1;
int askingDuration = 0;


int LEDToChange = 0;
unsigned long changeBlinkInterval = 0;

int LED2Time = millis();

typedef void(*CyclicTasks)();

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

CyclicTasks tasks [NUM_TASKS] = {setDuration, blinkLED1, blinkLED2};


void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();

  if(currentTime - previousCycleTime > EXECUTIVE_CYCLE_TIME){
    for(int i = 0; i < NUM_TASKS; i++){
      (*tasks[i])();
    }
    previousCycleTime = currentTime;
  }

}


void blinkLED1(){
  if(millis() - previousTime1 > blinkInterval[0]){
    if(LED1State == LOW){
      LED1State = HIGH;
    }
    else{
      LED1State = LOW;
    }
    digitalWrite(LED1_PIN, LED1State);
    previousTime1 = millis();
  }

}

void blinkLED2(){
  if(millis() - previousTime2 > blinkInterval[1]){

    if(LED2State == LOW){
      LED2State = HIGH;
    }
    else{
      LED2State = LOW;
    }
    digitalWrite(LED2_PIN, LED2State);
    previousTime2 = millis();
  }
}

void setDuration(){
  if(!Serial.available()){
    return;
  }

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
