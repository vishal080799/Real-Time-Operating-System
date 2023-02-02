#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include"freertos/semphr.h"

const TickType_t xDelay1 =1000 / portTICK_PERIOD_MS;
static int taskcore = 1;



TaskHandle_t first_task_handle;
TaskHandle_t second_task_handle;
TaskHandle_t third_task_handle;
TaskHandle_t fourth_task_handle;



SemaphoreHandle_t counting_sema_handle;



void first_task(void *data)
{
   printf("task 1: starting \n");
   printf("task 1:requesting for serial port\n");
   xSemaphoreTake(counting_sema_handle,pdMS_TO_TICKS(20000));
   printf("task 1:got the serial port\n");
   vTaskDelay(xDelay1);
   xSemaphoreGive(counting_sema_handle);
   printf("Task1: Released the serial port\n");
    vTaskDelete(first_task_handle);

}

void second_task(void *data)
{
     printf("task 2: starting \n");
   printf("task 2:requesting for serial port\n");
   xSemaphoreTake(counting_sema_handle,pdMS_TO_TICKS(20000));
   printf("task 2:got the serial port\n");
   vTaskDelay(2000 / portTICK_PERIOD_MS);
   xSemaphoreGive(counting_sema_handle);
   printf("Task2: Released the serial port\n");
    vTaskDelete(second_task_handle);
}

void third_task(void *data)
{
     printf("task 3: starting \n");
   printf("task 3:requesting for serial port\n");
   xSemaphoreTake(counting_sema_handle,pdMS_TO_TICKS(20000));
   printf("task 3:got the serial port\n");
   vTaskDelay(3000 / portTICK_PERIOD_MS);
   xSemaphoreGive(counting_sema_handle);
   printf("Task3: Released the serial port\n");
    vTaskDelete(third_task_handle);
}

void fourth_task(void *data)
{
     printf("task 4: starting \n");
   printf("task 4:requesting for serial port\n");
   xSemaphoreTake(counting_sema_handle,pdMS_TO_TICKS(20000));
   printf("task 4:got the serial port\n");
   vTaskDelay(5000 / portTICK_PERIOD_MS);
   xSemaphoreGive(counting_sema_handle);
   printf("Task4: Released the serial port\n");
    vTaskDelete(fourth_task_handle);
}


void app_main()
{
    // BaseType_t first_task_ret,second_task_ret;
    printf("DESD RTOS\n");

    counting_sema_handle=xSemaphoreCreateCounting(2,2);

    // xTaskCreate(first_task,"firsttask",2048,NULL,7,&first_task_handle);
    // xTaskCreate(second_task,"secondtask",2048,NULL,9,&second_task_handle);
    xTaskCreatePinnedToCore(first_task,"firsttask",2048,NULL,7,&first_task_handle,taskcore);
    xTaskCreatePinnedToCore(second_task,"secondtask",2048,NULL,7,&second_task_handle,taskcore);
    xTaskCreatePinnedToCore(third_task,"thirdtask",2048,NULL,7,&third_task_handle,taskcore);
    xTaskCreatePinnedToCore(fourth_task,"fourthtask",2048,NULL,7,&fourth_task_handle,taskcore);
}
   



