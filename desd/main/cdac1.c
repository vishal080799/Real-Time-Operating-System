#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
TaskHandle_t serial_task_handle;
TaskHandle_t eth_task_handle;
const TickType_t xDelay =500 / portTICK_PERIOD_MS;

void serial_task(void *data)
{ 
    int count =0;
    while (1)
    {
        count +=1;
        if(count==5)
        {
            vTaskResume(eth_task_handle);
            count=0;
        }
        printf("serial tak:started\n");
        vTaskDelay(xDelay);
     // vTaskDelete(serial_task_handle);
    }
}
void eth_task(void *data)
{
    while(1){
        vTaskSuspend(eth_task_handle);
    printf("eth task:started\n");
     vTaskDelay(xDelay);
    vTaskDelete(eth_task_handle);
    }
}


void app_main()
{
    // BaseType_t res;
    printf("DESD RTOS\n");
    xTaskCreate(serial_task, "serialtask", 2048, NULL,7, &serial_task_handle);
    xTaskCreate(eth_task,"ethtask", 2048, NULL,6, &eth_task_handle);
    //     if(res=pdPASS)
    //     {
    //         printf("task succewssfully created");
    //     }
}
