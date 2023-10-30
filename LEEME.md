# threadesp32
Clase padre para derivar de ella tareas de FreeRTOS en C++.  

# How to use it:

Crea una clase derivada de TaskParent.  
TaskParent es una clase abstracta, debes de definir en la clase derivada la funcion void loop() function, esta será la funcion de la tarea.  

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


El contructor recibirá los parametros necesarios, en el ejemplo de arriba, el nombre de la tarea y el pin en el que está conectado el LED que destelleará.  
El constructor tambien inicia la clase padre.  
Los parámetros que se pasan a TaskParent son:

const char* _name → Nombre de la tarea  
uint32_t _stackDepth → Tamaño de la pila  
UBaseType_t _uxPriority → La prioridad de la tarea  
BaseType_t _xCoreID) → El nucleo en el que se ejecutará  

El LED parpadeara a la frecuencia de un herzio.  
#TaskParent tiene los siguientes metodos:  

        void suspend();
Detiene la tarea.

        void resume();
Reanuda la tarea.

        bool issuspended();
true si la tarea se paró con suspend(), false si la tarea se reanudó con resume()  

        void setPriority(UBaseType_t newPriority);
Cambia la prioridad de la tarea.

        const char* getName();
Devuelve el nombre de la tarea.

        UBaseType_t getPriority();
Devuelve la prioridad de la tarea.

        UBaseType_t getWaterMark();
Retorna la watermark de la tarea.
La watermark es la minima cantidad de memoria de la pila disponible durante la ejecucion de la tarea.
La funcion retorna numero de palabras (en un procesador de 32 bits la palabra es de 4 bytes).  
Un valor de retorno de cero indica que la pila se ha desbordado. Un valor cercano a cero indica que la pila ha estado a punto de desbordar.  

        TaskHandle_t getTaskHandle();
Devuelve el manejador de la tarea.

        uint32_t getStackDepth();
Devuelve el tamaño inicial de la pila.
