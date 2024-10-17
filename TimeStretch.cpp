#include "TimeStretch.h"

#ifdef __cplusplus
extern "C" {
#endif

    static UBaseType_t uxIsRunning = pdFALSE;

    static UBaseType_t uxTickCoun = 0;

    static TaskHandle_t pxCurrentTask = NULL;

    static UBaseType_t uxPriorPriority = 0;

    static SemaphoreHandle_t pxSemaphore = NULL;

    //static TaskHandle_t pxCurrentTaskFailSafe = NULL;

    static SemaphoreHandle_t xCurrentFailSafeSemaphore = NULL;

    void vInitTask(void) {
        pxSemaphore = xSemaphoreCreateMutex();
    }

    UBaseType_t uxAskForTicks(UBaseType_t uxTickNumb, TaskHandle_t pxTask, SemaphoreHandle_t xFailSafeSemaphore/*, TaskHandle_t pxTaskFailSafe*/) {

        if (pxSemaphore == NULL)vInitTask();
        if (xSemaphoreTake(pxSemaphore, portMAX_DELAY) == pdFAIL) return pdFAIL;

        if (pxTask == NULL) pxCurrentTask = xTaskGetCurrentTaskHandle();
        else pxCurrentTask = pxTask;
        if (pxCurrentTask == NULL) {
            vFinishTicksTask();
            return pdFAIL;
        }

        //pxCurrentTaskFailSafe = pxTaskFailSafe;
        xCurrentFailSafeSemaphore = xFailSafeSemaphore;
        uxPriorPriority = uxTaskPriorityGet(pxCurrentTask);
        vTaskPrioritySet(pxCurrentTask, (configMAX_PRIORITIES - 1));
        uxTickCoun = uxTickNumb;
        uxIsRunning = pdTRUE;
        return pdPASS;
    }

    void vFinishTicksTask(void) {
        uxIsRunning = pdFALSE;
        uxTickCoun = 0;
        vTaskPrioritySet(pxCurrentTask, uxPriorPriority);
        pxCurrentTask = NULL;
        uxPriorPriority = 0;
        //pxCurrentTaskFailSafe = NULL;
        xCurrentFailSafeSemaphore = NULL;
        xSemaphoreGive(pxSemaphore);
        return;
    }

    void vDecTickCount(void) {
        if (uxIsRunning == pdTRUE) {
            printf("vDecTickCount\n");
            uxTickCoun--;
            if (uxTickCoun == 0) {
                //vTaskSuspend(NULL);
                /*if (pxCurrentTaskFailSafe != NULL) {
                    //colocar uma mensagem direta para o failsafe rodar de volta
                    xTaskResumeFromISR(pxCurrentTaskFailSafe);
                    //vTaskNotifyGiveFromISR(pxCurrentTaskFailSafe, NULL);
                }*/
                if (xCurrentFailSafeSemaphore != NULL) {
                    xSemaphoreGiveFromISR(xCurrentFailSafeSemaphore, NULL);
                }
                vFinishTicksTask();

            }
        }
    }

#ifdef __cplusplus
}
#endif