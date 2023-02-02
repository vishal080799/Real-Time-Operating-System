#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include"freertos/queue.h"


const TickType_t xDelay1 =1000/ portTICK_PERIOD_MS;
const TickType_t xDelay =300 / portTICK_PERIOD_MS;
static int taskcore = 1;



TaskHandle_t first_task_handle;
TaskHandle_t second_task_handle;
TaskHandle_t third_task_handle;
TaskHandle_t fourth_task_handle;

QueueHandle_t queue_buff_handle;



void first_task(void *data)
{
   int task1_data=100;
   printf("task1 \n");
   while(1)
   {
    task1_data++;
    xQueueSend(queue_buff_handle,&task1_data,xDelay);
   //  vTaskDelay(xDelay);
   }
   vTaskDelete(NULL);
}

void second_task(void *data)
{
   int task2_data=200;
   printf("task2 \n");
   while(1)
   {
    task2_data++;
    xQueueSend(queue_buff_handle,&task2_data,xDelay);
   vTaskDelay(xDelay);
   }
   vTaskDelete(NULL);
}
void third_task(void *data)
{
int buffer =0;
printf("task3\n");
   while(1)
   {
    
    xQueueReceive(queue_buff_handle,&buffer,xDelay1);
    printf("task3:received data:%d\n",buffer);
   //  vTaskDelay(xDelay);
   }
   vTaskDelete(NULL);
}
void fourth_task(void *data)

{
    int buffer=0;
    int count=0;

   printf("task4 \n");
   while(1)
   {
    //task1_data++;
    xQueueReceive(queue_buff_handle,&buffer,xDelay1);
    printf("task4 :recieved data:%d\n",buffer);
    count++;
    if(count>50)
    {
        count=0;
        
        vTaskDelay(xDelay1);
    }
    }
   vTaskDelete(NULL);
}

void app_main()
{
  
    printf("DESD RTOS\n");
    queue_buff_handle=xQueueCreate(4,64);
    
    xTaskCreatePinnedToCore(first_task,"firsttask",2048,NULL,3,&first_task_handle,taskcore);
    xTaskCreatePinnedToCore(second_task,"secondtask",2048,NULL,6,&second_task_handle,taskcore);
    xTaskCreatePinnedToCore(third_task,"third",2048,NULL,8,&third_task_handle,taskcore); 
    xTaskCreatePinnedToCore(fourth_task,"fourth",2048,NULL,10,&fourth_task_handle,taskcore);

}
   



