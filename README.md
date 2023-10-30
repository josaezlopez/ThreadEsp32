# threadesp32
Parent class to derive FreeRTOS tasks in C++ from it.

# How to use it:

Create a class derived from TaskParent.  
TaskParent is an abstract class and you will need to define the loop() function in the derived class, which will be the entry function to the task.

        #include <threadesp32.h>  
                
        class Blink: public TaskParent {  
                public:  
                        Blink(const char*TaskName, uint8_tpinLed):TaskParent(TaskName,2048,TaskParent::th_MEDIUM_PRIORITY,1){
                                _pinLed = pinLed;  
                        }  
                        void loop(){  
                                pinMode(_pinLed,OUTPUT);  
                                while (true){  
                                        digitalWrite(_pinLed, HIGH);  
                                        delay(500);  
                                        digitalWrite(_pinLed, LOW);  
                                        delay(500);
                                }  
                        }  
                protected:  
                        uint8_t _pinLed;  
        };  
        
        Blink LED("LED1",LED_BUILTIN);  
        
        void setup(){  
        }  
        void loop() {  
        }  


In the constructor they pass the necessary parameters, in the example above, the name of the task and the pin to which the LED that will flash is connected. The constructor also starts the parent class.
The parameters passed to TaskParent are:

const char* _name → task name  
uint32_t _stackDepth → Stack size.  
UBaseType_t _uxPriority → The priority of the task  
BaseType_t _xCoreID) → the core it will run on  

It will cause the LED to flash at a frequency of one hertz.  
The class has the following methods.  

        void suspend();
Stop the task.

        void resume();
Resume the task.

        bool issuspended();
True if the task was suspended with suspend(), False if the task was resumed with resume();

        void setPriority(UBaseType_t newPriority);
Change the priority of the task.

        const char* getName();
Returns the name of the task

        UBaseType_t getPriority();
Returns the priority of the task

        UBaseType_t getWaterMark();
Returns the watermark of the task.
The watermark is the minimum amount of free memory the stack had. The number returned are words, on a 32-bit machine a value of 100 would indicate that (100x4 bytes per word) 400 bytes were not used. A return value of zero indicates that the stack has overflowed.  A value close to zero indicates that the stack has been close to overflowing.

        TaskHandle_t getTaskHandle();
Returns the task handler.

        uint32_t getStackDepth();
Returns the initial size of the stack.
