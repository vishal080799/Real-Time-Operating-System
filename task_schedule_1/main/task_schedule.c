#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
TaskHandle_t serial_task_handle;
TaskHandle_t eth_task_handle;
TaskHandle_t wifi_task_handle;
int count =0;

const TickType_t xDelay =500 / portTICK_PERIOD_MS;
const TickType_t xDelay1 =1000 / portTICK_PERIOD_MS;

void serial_task(void *data)
{ 
    
    while (1)
    {
        
        // count++;
        // printf("%d\t",count);
        // if(count==5)
        // {
        //     vTaskDelay(xDelay);
        //     // vTaskResume(eth_task_handle);
            
        //     // vTaskSuspend(serial_task_handle);
            
        // }
        
        printf("serial tak:started\n");
        vTaskDelay(xDelay1);
        
    }
}
void eth_task(void *data)
{
    while(1){
    
    // count++;
    // printf("%d\t",count);
    // if(count==10)
    // {
    //     vTaskDelay(xDelay);
    // // vTaskResume(wifi_task_handle);
    
    // // vTaskSuspend(eth_task_handle);
    // }
    printf("eth task:started\n");
    vTaskDelay(xDelay1);
    //  
    }
}

void wifi_task(void *data)
{
    while(1){

        
        // count++;
        // printf("%d\t",count);
        // if(count==15)
        // {
        //     vTaskDelay(xDelay);
        //     // vTaskResume(serial_task_handle);
        //     count =0;
            
        //     // vTaskSuspend(wifi_task_handle);
            
        // }
        printf("wifi_task : Started\n");
        vTaskDelay(xDelay1);
        // 
    }
}


void app_main()
{
    BaseType_t serial_task_ret,eth_task_ret,wifi_task_ret;
    printf("DESD RTOS\n");
    serial_task_ret= xTaskCreate(serial_task, "serialtask", 2048, NULL,8, &serial_task_handle);
    if(serial_task_ret==pdPASS)
    {
        printf("serialtask successfully created\n");
    }
    eth_task_ret= xTaskCreate(eth_task,"ethtask", 2048, NULL,6, &eth_task_handle);
    if(eth_task_ret==pdPASS)
    {
        printf("ethtask successfully created\n");
    }
    wifi_task_ret= xTaskCreate(wifi_task,"wifitask", 2048, NULL,8, &wifi_task_handle);
    if(wifi_task_ret==pdPASS)
    {
        printf("wifitask successfully created Priority= \n");
    }
}
