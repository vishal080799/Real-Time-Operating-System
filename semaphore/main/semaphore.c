#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include"freertos/semphr.h"

const TickType_t xDelay1 =1000 / portTICK_PERIOD_MS;
static int taskcore = 1;



TaskHandle_t first_task_handle;
TaskHandle_t second_task_handle;



SemaphoreHandle_t binary_sema_handle;



void first_task(void *data)
{
   BaseType_t sem_ret;
    printf("Starting of first TAsk\n");

    vTaskDelay(xDelay1);
    sem_ret = xSemaphoreGive(binary_sema_handle);
    if(sem_ret == pdFAIL)
    {
        printf("SemaphoreGive Error\n");
    }
    else
        printf("SemaphoreGive Successfull\n");

    printf("First task Entered\n");
    vTaskDelete(first_task_handle);

}

void second_task(void *data)
{
    BaseType_t sem_ret;
   printf("Starting of secend TAsk\n");
    sem_ret = xSemaphoreTake(binary_sema_handle,xDelay1);
    if(sem_ret != pdFAIL)
    {
        printf("SemaphoreTake Error\n");
    }
    else
        printf("SemaphoreTake Successfull\n");

    printf("Second  task Entered\n");
    vTaskDelete(second_task_handle);
        

}
void app_main()
{
    // BaseType_t first_task_ret,second_task_ret;
    printf("DESD RTOS\n");

    binary_sema_handle=xSemaphoreCreateBinary();

    // xTaskCreate(first_task,"firsttask",2048,NULL,7,&first_task_handle);
    // xTaskCreate(second_task,"secondtask",2048,NULL,9,&second_task_handle);
    xTaskCreatePinnedToCore(first_task,"firsttask",2048,NULL,7,&first_task_handle,taskcore);
    xTaskCreatePinnedToCore(second_task,"secondtask",2048,NULL,9,&second_task_handle,taskcore);

}
   



