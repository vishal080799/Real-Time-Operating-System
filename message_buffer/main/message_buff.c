#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include"freertos/message_buffer.h"

const TickType_t xDelay1 =10000 / portTICK_PERIOD_MS;
const TickType_t xDelay =3000 / portTICK_PERIOD_MS;
static int taskcore = 1;



TaskHandle_t first_task_handle;
TaskHandle_t second_task_handle;



MessageBufferHandle_t message_buff_handle,message_buff_handle1;



void first_task(void *data)
{
    unsigned char receive1_buff[200];
    printf("Starting of first TAsk\n");
    printf("First message sent\n");
    xMessageBufferSend(message_buff_handle,"Hi This is Task1 as First task\n",40,xDelay1);
    vTaskDelay(xDelay);
    
    
    printf("Second message sent\n");
    
    xMessageBufferSend(message_buff_handle,"Hi This is Vishal from First task\n",50,xDelay1);
    vTaskDelay(xDelay);
   
     
    printf("Third message sent\n");
    
    xMessageBufferSend(message_buff_handle,"Hi This is Jayesh talking from First task\n",50,xDelay1);
    vTaskDelay(xDelay);
    
    for(int i =0;i<3;i++)
    {
        xMessageBufferReceive(message_buff_handle1,&receive1_buff,200,xDelay1);
        printf("Confirmation: \t%s\n",receive1_buff);
    }

    vTaskDelete(first_task_handle);

}

void second_task(void *data)
{
    unsigned char receive_buff[200];
   printf("Starting of secend TAsk\n");
    for(int i=0;i<3;i++)
    {   
        printf("Trying to receive message\n");
        vTaskDelay(xDelay);
        xMessageBufferReceive(message_buff_handle,&receive_buff,200,xDelay1);
        printf("Messge Received from Task1 in Task2 ......\n........And the Message is \n%s\n",receive_buff);
        
    }
     xMessageBufferSend(message_buff_handle1,"Message1 Received at Task2\n",30,xDelay1);
     vTaskDelay(xDelay);
     xMessageBufferSend(message_buff_handle1,"Message2 Received at Task2\n",30,xDelay1);
     vTaskDelay(xDelay);
     xMessageBufferSend(message_buff_handle1,"Message3 Received at Task2\n",30,xDelay1);
    vTaskDelay(xDelay);
    vTaskDelete(second_task_handle);
        

}
void app_main()
{
    // BaseType_t first_task_ret,second_task_ret;
    printf("DESD RTOS\n");

    message_buff_handle=xMessageBufferCreate(200);
    message_buff_handle1=xMessageBufferCreate(200);

    // xTaskCreate(first_task,"firsttask",2048,NULL,7,&first_task_handle);
    // xTaskCreate(second_task,"secondtask",2048,NULL,9,&second_task_handle);
    xTaskCreatePinnedToCore(first_task,"firsttask",2048,NULL,7,&first_task_handle,taskcore);
    xTaskCreatePinnedToCore(second_task,"secondtask",2048,NULL,9,&second_task_handle,taskcore);

}
   



