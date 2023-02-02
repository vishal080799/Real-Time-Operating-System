#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include"freertos/stream_buffer.h"

const TickType_t xDelay1 =10000 / portTICK_PERIOD_MS;
const TickType_t xDelay =3000 / portTICK_PERIOD_MS;
static int taskcore = 1;



TaskHandle_t first_task_handle;
TaskHandle_t second_task_handle;



StreamBufferHandle_t stream_buff_handle;
// stream_buff_handle1;

unsigned char receive_buff[300];

void first_task(void *data)
{

    printf("Starting of first TAsk\n");
    // printf("First message sent\n");
    xStreamBufferSend(stream_buff_handle,"Hi This\n",10,xDelay1);
    xStreamBufferSend(stream_buff_handle,"Vishal\n",10,xDelay1);
    xStreamBufferSend(stream_buff_handle,"Jayesh\n",10,xDelay1);
    //printf("Third message sent\n");
    vTaskDelete(first_task_handle);

}

void second_task(void *data)
{
    
   //printf("Starting of secend TAsk\n");
  ssize_t size = xStreamBufferReceive(stream_buff_handle,&receive_buff,300,xDelay1);
   printf("size of data received is %d : : And the Message is %s\n",size,receive_buff);

    vTaskDelete(second_task_handle);
        

}
void app_main()
{
    printf("DESD RTOS\n");

    stream_buff_handle=xStreamBufferCreate(300,10);
    xTaskCreatePinnedToCore(first_task,"firsttask",2048,NULL,7,&first_task_handle,taskcore);
    xTaskCreatePinnedToCore(second_task,"secondtask",2048,NULL,9,&second_task_handle,taskcore);

}
   



