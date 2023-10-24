#pragma once

#include <Arduino.h>
#include <freertos/FreeRTOS.h>

 


class TaskParent{
    public:
        TaskParent(const char* _name, uint32_t _stackDepth, UBaseType_t _uxPriority, BaseType_t _xCoreID);
        ~TaskParent();

        void suspend();
        void resume();
        bool isSuspended();
        void setPriority(UBaseType_t newPriority);

        const char* getName();
        UBaseType_t getPriority();
        UBaseType_t getWaterMark();
        TaskHandle_t getTaskHandle();
        uint32_t getStackDepth();


    protected:
        virtual void loop() = 0;
        static void taskFunction(void* _param);

        bool _isSuspended = false;
        void taskDelay(uint32_t t);
        char name[ configMAX_TASK_NAME_LEN + 1 ];
        
        TaskHandle_t taskHandle = nullptr;
        uint32_t stackDepth;

        static const uint8_t th_LOWEST_PRIORITY = 1;         
        static const uint8_t th_MEDIUM_PRIORITY = ((configMAX_PRIORITIES + 1) / 4);        
        static const uint8_t th_HIGH_PRIORITY   = (((configMAX_PRIORITIES + 1 )/ 4) * 2);
        static const uint8_t th_VERY_HIGH_PRIORITY = (((configMAX_PRIORITIES + 1 )/ 4) * 3);     
        static const uint8_t th_HIGHEST_PRIORITY   = configMAX_PRIORITIES;   
    

};



