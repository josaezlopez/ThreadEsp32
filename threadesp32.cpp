#include <threadesp32.h>


#if defined(ESP8266)
    #pragma "only esp32!!!"
#elif defined(ESP32)


TaskParent::TaskParent(const char* _name, uint32_t _stackDepth, UBaseType_t _uxPriority, BaseType_t _xCoreID = 0){
    stackDepth = _stackDepth;
    if(_uxPriority >  configMAX_PRIORITIES){
        return;
        }
    name[0] = 0x0;

    if(xTaskCreatePinnedToCore(taskFunction, _name, _stackDepth, this, _uxPriority, &taskHandle ,_xCoreID) == pdPASS){
        strncpy(name,_name,configMAX_TASK_NAME_LEN);
        }
    }


TaskParent::~TaskParent(){
    if(taskHandle != nullptr)
        vTaskDelete(taskHandle);
}


void TaskParent::taskFunction(void* _param){
    TaskParent* p =   static_cast<TaskParent*>(_param);
    p->loop();
    }

uint32_t TaskParent::getStackDepth(){
    return stackDepth;
    }

void TaskParent::suspend(){ 
    _isSuspended = true;
    vTaskSuspend(taskHandle); 
    }

void TaskParent::resume(){  
    _isSuspended = false;
    vTaskResume(taskHandle); 
    }

bool TaskParent::isSuspended(){
    return _isSuspended;
    }

const char* TaskParent::getName(){ 
    return name; 
    }

void TaskParent::taskDelay(uint32_t t){
    vTaskDelay(t / portTICK_PERIOD_MS);
}

UBaseType_t TaskParent::getPriority(){
    return uxTaskPriorityGet(taskHandle);
}

void TaskParent::setPriority(UBaseType_t newPriority){
    vTaskPrioritySet(taskHandle,newPriority);
}

UBaseType_t TaskParent::getWaterMark(){
    return uxTaskGetStackHighWaterMark( taskHandle );
}

TaskHandle_t TaskParent::getTaskHandle(){
    return taskHandle;
}

#endif