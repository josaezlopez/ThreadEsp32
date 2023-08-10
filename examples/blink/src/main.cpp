#include <threadesp32.h>

class Blink : public TaskParent{

  public:

    Blink(const char* _taskName, uint8_t _pin, bool _activeHigh=true): TaskParent(_taskName,1000,TaskParent::th_MEDIUM_PRIORITY,1){
      pin = _pin;
      activeHigh = _activeHigh;
      
      pinMode(pin,OUTPUT);
      digitalWrite(pin,!activeHigh);
    }


    void on(float frequency,float workCycle){
      uint32_t period = 1000 / frequency;
      tOn = period * workCycle;
      tOff = period - tOn;
      resume();
    }


    void stop(){
      digitalWrite(pin,!activeHigh);
      suspend();
    }


  void loop(){
    stop();
    while(true){
        digitalWrite(pin, activeHigh);
        delay(tOn);
        digitalWrite(pin, !activeHigh);
        delay(tOff);
      }
    

  }


  private:

    uint32_t tOn = 500;   
    uint32_t tOff = 500;
    bool activeHigh;
    uint8_t pin;



};

Blink led("TaskLed",LED_BUILTIN);

void setup() {
  Serial.begin(115200);
  // Flash led 5Hz,WC = 50%
  led.on(5.0,0.5);
  // wait 10 seconds
  delay(10000);
  // Flash led 1Hz,WC = 10%
  led.on(1.0,0.1);
 
}



void loop() {
  // put your main code here, to run repeatedly:

  
}

