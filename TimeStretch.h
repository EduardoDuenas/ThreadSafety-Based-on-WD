#ifndef TS_H
#define TS_H


#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include <conio.h>

#ifdef __cplusplus
extern "C" {
#endif

    UBaseType_t uxAskForTicks(
        UBaseType_t uxTickNumb,                 //numero de ticks pedidos
        TaskHandle_t pxTask,                    //guia da tarefa a receber ticks
        SemaphoreHandle_t xFailSafeSemaphore/*, //guia do semaforo de failsafe
        TaskHandle_t pxTaskFailSafe*/);  

    void vFinishTicksTask(void);

    void vDecTickCount(void);

#ifdef __cplusplus
}
#endif
#endif  //end TS_H
#pragma once
