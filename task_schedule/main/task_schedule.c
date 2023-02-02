#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
TaskHandle_t serial_task_handle;
TaskHandle_t eth_task_handle;
TaskHandle_t wifi_task_handle;


const TickType_t xDelay =500 / portTICK_PERIOD_MS;

void serial_task(void *data)
{ 
    while (1)
    {
        // count +=1;
        // if(count==5)
        // {
        //     vTaskResume(eth_task_handle);
            
        // }
        // if(count==10){
        //     vTaskResume(wifi_task_handle);
        //     count =0;
        // }
        printf("serial task:started\n");
        vTaskDelay(xDelay);
    }
}
void eth_task(void *data)
{
    while(1){
    // vTaskSuspend(eth_task_handle);
    printf("eth task:started\n");
     vTaskDelay(xDelay);
    }
}

void wifi_task(void *data)
{
    while(1){

        // vTaskSuspend(wifi_task_handle);
        printf("wifi_task : Started\n");
        vTaskDelay(xDelay);
    }
}


void app_main()
{
    
    xTaskCreate(serial_task, "serialtask", 2048, NULL,11, &serial_task_handle);
    xTaskCreate(eth_task,"ethtask", 2048, NULL,19, &eth_task_handle);
    
    
    xTaskCreate(wifi_task,"wifitask", 2048, NULL,28, &wifi_task_handle);
    
 }
