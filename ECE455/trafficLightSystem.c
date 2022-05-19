/*
 
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
 
    All rights reserved
 
 
 
    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
 
 
 
    This file is part of the FreeRTOS distribution.
 
 
 
    FreeRTOS is free software; you can redistribute it and/or modify it under
 
    the terms of the GNU General Public License (version 2) as published by the
 
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.
 
 
 
    ***************************************************************************
 
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
 
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
 
    >>!   obliged to provide the source code for proprietary components     !<<
 
    >>!   outside of the FreeRTOS kernel.                                   !<<
 
    ***************************************************************************
 
 
 
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
 
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
 
    link: http://www.freertos.org/a00114.html
 
 
 
    ***************************************************************************
 
     *                                                                       *
 
     *    FreeRTOS provides completely free yet professionally developed,    *
 
     *    robust, strictly quality controlled, supported, and cross          *
 
     *    platform software that is more than just the market leader, it     *
 
     *    is the industry's de facto standard.                               *
 
     *                                                                       *
 
     *    Help yourself get started quickly while simultaneously helping     *
 
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
 
     *    tutorial book, reference manual, or both:                          *
 
     *    http://www.FreeRTOS.org/Documentation                              *
 
     *                                                                       *
 
    ***************************************************************************
 
 
 
    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
 
    the FAQ page "My application does not run, what could be wwrong?".  Have you
 
    defined configASSERT()?
 
 
 
    http://www.FreeRTOS.org/support - In return for receiving this top quality
 
    embedded software for free we request you assist our global community by
 
    participating in the support forum.
 
 
 
    http://www.FreeRTOS.org/training - Investing in training allows your team to
 
    be as productive as possible as early as possible.  Now you can receive
 
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
 
    Ltd, and the world's leading authority on the world's leading RTOS.
 
 
 
    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
 
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
 
    compatible FAT file system, and our tiny thread aware UDP/IP stack.
 
 
 
    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
 
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.
 
 
 
    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
 
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
 
    licenses offer ticketed support, indemnification and commercial middleware.
 
 
 
    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
 
    engineered and independently SIL3 certified version for use in safety and
 
    mission critical applications that require provable dependability.
 
 
 
    1 tab == 4 spaces!
 
*/
 
 
 
/*
 
FreeRTOS is a market leading RTOS from Real Time Engineers Ltd. that supports
 
31 architectures and receives 77500 downloads a year. It is professionally
 
developed, strictly quality controlled, robust, supported, and free to use in
 
commercial products without any requirement to expose your proprietary source
 
code.
 
 
 
This simple FreeRTOS demo does not make use of any IO ports, so will execute on
 
any Cortex-M3 of Cortex-M4 hardware.  Look for TODO markers in the code for
 
locations that may require tailoring to, for example, include a manufacturer
 
specific header file.
 
 
 
This is a starter project, so only a subset of the RTOS features are
 
demonstrated.  Ample source comments are provided, along with web links to
 
relevant pages on the http://www.FreeRTOS.org site.
 
 
 
Here is a description of the project's functionality:
 
 
 
The main() Function:
 
main() creates the tasks and software timers described in this section, before
 
starting the scheduler.
 
 
 
The Queue Send Task:
 
The queue send task is implemented by the prvQueueSendTask() function.
 
The task uses the FreeRTOS vTaskDelayUntil() and xQueueSend() API functions to
 
periodically send the number 100 on a queue.  The period is set to 200ms.  See
 
the comments in the function for more details.
 
http://www.freertos.org/vtaskdelayuntil.html
 
http://www.freertos.org/a00117.html
 
 
 
The Queue Receive Task:
 
The queue receive task is implemented by the prvQueueReceiveTask() function.
 
The task uses the FreeRTOS xQueueReceive() API function to receive values from
 
a queue.  The values received are those sent by the queue send task.  The queue
 
receive task increments the ulCountOfItemsReceivedOnQueue variable each time it
 
receives the value 100.  Therefore, as values are sent to the queue every 200ms,
 
the value of ulCountOfItemsReceivedOnQueue will increase by 5 every second.
 
http://www.freertos.org/a00118.html
 
 
 
An example software timer:
 
A software timer is created with an auto reloading period of 1000ms.  The
 
timer's callback function increments the ulCountOfTimerCallbackExecutions
 
variable each time it is called.  Therefore the value of
 
ulCountOfTimerCallbackExecutions will count seconds.
 
http://www.freertos.org/RTOS-software-timer.html
 
 
 
The FreeRTOS RTOS tick hook (or callback) function:
 
The tick hook function executes in the context of the FreeRTOS tick interrupt.
 
The function 'gives' a semaphore every 500th time it executes.  The semaphore
 
is used to synchronise with the event semaphore task, which is described next.
 
 
 
The event semaphore task:
 
The event semaphore task uses the FreeRTOS xSemaphoreTake() API function to
 
wait for the semaphore that is given by the RTOS tick hook function.  The task
 
increments the ulCountOfReceivedSemaphores variable each time the semaphore is
 
received.  As the semaphore is given every 500ms (assuming a tick frequency of
 
1KHz), the value of ulCountOfReceivedSemaphores will increase by 2 each second.
 
 
 
The idle hook (or callback) function:
 
The idle hook function queries the amount of free FreeRTOS heap space available.
 
See vApplicationIdleHook().
 
 
 
The malloc failed and stack overflow hook (or callback) functions:
 
These two hook functions are provided as examples, but do not contain any
 
functionality.
 
*/
 
 
 
/* Standard includes. */
 
#include <stdint.h>
 
#include <stdio.h>
 
#include "stm32f4_discovery.h"
 
/* Kernel includes. */
 
#include "stm32f4xx.h"
 
#include "../FreeRTOS_Source/include/FreeRTOS.h"
 
#include "../FreeRTOS_Source/include/queue.h"
 
#include "../FreeRTOS_Source/include/semphr.h"
 
#include "../FreeRTOS_Source/include/task.h"
 
#include "../FreeRTOS_Source/include/timers.h"
 
 
 
 
 
 
 
/*-----------------------------------------------------------*/
 
#define mainQUEUE_LENGTH 100
 
 
 
#define amber  0
 
#define green  1
 
#define red  2
 
#define blue  3
 
 
 
#define amber_led LED3
#define green_led LED4
#define red_led LED5
#define blue_led LED6
 
#define RED GPIO_Pin_0
#define YELLOW GPIO_Pin_1
#define GREEN GPIO_Pin_2
#define POT GPIO_Pin_3
 
 
#define SCALE_FACTOR 1000
 
//VARIABLES
int speed = 1;
int red_flag = 0;
int randomTraffic = 1;
 
//QUEUES
xQueueHandle speed_Queue = 0;
xQueueHandle car_Queue = 0;
xQueueHandle state_Queue = 0;
xQueueHandle xQueue_handle = 0;
 
//FUNCTION DECLARATIONS
uint16_t readADC(void);
static void sendToShift(int);
 
//CALLBACKS
void Yellow_Light_Callback();
void Green_Light_Callback();
void Red_Light_Callback();
 
//TAST DECLARATIONS
static void prvSetupHardware( void );
static void createTrafficTask(void *pvParams);
static void trafficLightTask(void *pvParameters);
static void displayTrafficTask(void *pvParams);
static void trafficFlowTask(void *pvParams);
 
//TIMERS
xTimerHandle xRedLightTimer;
xTimerHandle xYellowLightTimer;
xTimerHandle xGreenLightTimer;
 
 
 
 
 
/*-----------------------------------------------------------*/
 
 
 
int main(void)
 
{
 
  //function contains init adc and gpio
  prvSetupHardware();


  speed_Queue = xQueueCreate(mainQUEUE_LENGTH, sizeof(uint16_t));
  car_Queue = xQueueCreate(1, sizeof(int));

  //task adjusts flow of traffic
  xTaskCreate(trafficFlowTask , "TrafficFlow", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(createTrafficTask, "createTraffic", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(trafficLightTask, "trafficLight", configMINIMAL_STACK_SIZE,NULL,1, NULL);
  xTaskCreate(displayTrafficTask, "displayTraffic", configMINIMAL_STACK_SIZE, NULL,1, NULL);


  //create red green and amber timers
  xRedLightTimer = xTimerCreate("RedLightTimer",3000,pdFALSE,(void *)0, Red_Light_Callback);
  xGreenLightTimer = xTimerCreate("GreenLightTimer",3000,pdFALSE,(void *)0, Green_Light_Callback);
  xYellowLightTimer = xTimerCreate("YellowLightTimer",1000,pdFALSE,(void *)0, Yellow_Light_Callback);

  //turn on green light first and start timer for green light
  xTimerStart(xGreenLightTimer,0);
  GPIO_SetBits(GPIOC, GREEN);

  vTaskStartScheduler();

  return 0;
 
}
 
/*This function initalizes the adc!*/
void ADC_init(){
 
  //enable clock for adc
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  //struct for adc init
  ADC_InitTypeDef ADC_InitStruct;
  //set adc resolution to 8 bits
  ADC_InitStruct.ADC_Resolution = ADC_Resolution_8b;
  //result will hold in the left most bits
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Left;
  //disable continuous mode
  ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
  //disable external trigger for adc
  ADC_InitStruct.ADC_ExternalTrigConvEdge = DISABLE;

  ADC_Init(ADC1, &ADC_InitStruct);

  //enable adc
  ADC_Cmd(ADC1, ENABLE);

  // sets adc channel's corresponding rank in the sequencer (set to 1 cause only one channel) and its sample time (try 56 cycles?)
  ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 1, ADC_SampleTime_84Cycles);
}
 
/*This function intitalizes the gpio!*/
void GPIO_init(){
 
  NVIC_SetPriorityGrouping(0);
  //enable GPIO clock
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  //struct for initializing the leds
  GPIO_InitTypeDef GPIO_InitStruct;
  //pins 0 1 and 2
  GPIO_InitStruct.GPIO_Pin = RED | YELLOW | GREEN; //Red
  //set mode to output
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

  //send struct to init function
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  //init shift register
  GPIO_InitTypeDef ShiftReg_InitStruct;

  //set bits 6, 7 and 8 for shift register
  ShiftReg_InitStruct.GPIO_Pin = 0b111000000;
  //set mode for shift reg to out
  ShiftReg_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  ShiftReg_InitStruct.GPIO_OType = GPIO_OType_PP;
  ShiftReg_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  //init value to low speed
  ShiftReg_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(GPIOC, &ShiftReg_InitStruct);

  //init potentiometer
  GPIO_InitTypeDef POT_InitStruct;
  //set bit 3 (for potentiometer)
  POT_InitStruct.GPIO_Pin = 0b1000;
  POT_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  POT_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_Init(GPIOC, &POT_InitStruct);
}
 
 
 
 
/*Function called when green timer is done : turn off green light, turn on amber light, start amber timer*/
void Green_Light_Callback(){
  GPIO_ResetBits(GPIOC, GREEN); //turn off green
  GPIO_SetBits(GPIOC, YELLOW);//turn on amber
  xTimerStart(xYellowLightTimer,0);

}
 
/*Function called when yellow timer is done : turn off yellow light, turn on red light, start red timer*/
void Yellow_Light_Callback(){
  GPIO_ResetBits(GPIOC, YELLOW);
  GPIO_SetBits(GPIOC, RED);
  xTimerStart(xRedLightTimer,0);
 
}
 
/*Function called when red timer is done : turn off red light, turn on green light, start green timer*/
void Red_Light_Callback(){
  GPIO_ResetBits(GPIOC, RED);
  GPIO_SetBits(GPIOC, GREEN);
  xTimerStart(xGreenLightTimer,0);
}
 
 
/*This function sends traffic to the shift register */
 
static void sendToShift(int car){
  //send correct bit to shift reg (car  or no car)
  GPIO_SetBits(GPIOC, GPIO_Pin_8);
  if(car){
  GPIO_SetBits(GPIOC, GPIO_Pin_6);
  } else{
  GPIO_ResetBits(GPIOC, GPIO_Pin_6);
  }
  //reset the clock
  GPIO_SetBits(GPIOC, GPIO_Pin_7);
  GPIO_ResetBits(GPIOC, GPIO_Pin_7);
  GPIO_SetBits(GPIOC, GPIO_Pin_7);
}
 
 
/*Function updates traffic light times based on the traffic flow (pot values) */
 
static void trafficLightTask(void *pvParameters){
 
  const TickType_t xTicksToWait = pdMS_TO_TICKS(0);

  int trafficFlow = 3;
  int initTrafficFlow = 3;
  xQueueReceive(speed_Queue, &initTrafficFlow, xTicksToWait);

  while(1){

    xQueueReceive(speed_Queue, &trafficFlow, xTicksToWait);

    //if the traffic flow value has been updated, time to change the lights!!
    if(trafficFlow != initTrafficFlow){
      initTrafficFlow = trafficFlow;

      //reset lights according to new traffic speed
      if(xTimerIsTimerActive(xRedLightTimer)){
        xTimerStop(xRedLightTimer, 0);
        xTimerChangePeriod(xRedLightTimer,-100*trafficFlow + 2000 , 0);
        xTimerChangePeriod(xGreenLightTimer, 100*trafficFlow + 2000, 0);
        xTimerStop(xGreenLightTimer, 0);
      }
      else if(xTimerIsTimerActive(xGreenLightTimer)){
        xTimerChangePeriod(xRedLightTimer,-100*trafficFlow + 2000, 0);
        xTimerStop(xRedLightTimer, 0);
        xTimerStop(xGreenLightTimer, 0);
        xTimerChangePeriod(xGreenLightTimer, 100*trafficFlow + 2000, 0);
      }
      else if(xTimerIsTimerActive(xYellowLightTimer)){
        xTimerChangePeriod(xRedLightTimer, -100*trafficFlow + 2000, 0);
        xTimerStop(xRedLightTimer, 0);
        xTimerChangePeriod(xGreenLightTimer,  100*trafficFlow + 2000, 0);
        xTimerStop(xGreenLightTimer, 0);
      }
    }
  }
 
}
 
/*This task displays traffic depending on the traffic lights!*/
static void displayTrafficTask(void *pvParameters){


  const TickType_t xTicksToWait = pdMS_TO_TICKS(0);

  int traffic[19] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  int newCar = 0;
  while(1){

    vTaskDelay(1000);
    //get new car
    xQueueReceive(car_Queue, &newCar, xTicksToWait);

    //if green timer is on, shift cars down the line
    if(xTimerIsTimerActive(xGreenLightTimer)){

      for(int i = 17; i >= 0; i--){
        traffic[i+1]= traffic[i];
      }

      //place new car on the array
      traffic[0] = newCar;

      //if red or yellow is on, move all cars on the right side of the intersection
      }else if(xTimerIsTimerActive(xRedLightTimer)|| xTimerIsTimerActive(xYellowLightTimer)){

        for(int i = 17; i >= 8; i--){
        traffic[i+1]= traffic[i];
        }
        traffic[8] = 0;

        //only move cars along until the line is full!!!!
        int arrayFullFlag = 0;

        for(int i = 7; i >= 0; i--){
          if(traffic[i] == 0){
          for(int j = i; j > 0; j--){
            traffic[j] = traffic[j-1];
          }
          break;
        }
        if(i ==0){
          arrayFullFlag = 1;
        }

      }
      //if array is not full, add new car
      if(arrayFullFlag != 1){
        traffic[0] = newCar;
      }
    }
    //send traffic to shift register (to display)
    for(int i = 18; i >= 0 ; i--){
      sendToShift(traffic[i]);
    }
  }
}
 
 
/*This function generates the traffic randomly and puts new traffic into the car queue*/
static void createTrafficTask(void *pvParameters){
 
  const TickType_t xTicksToWait = pdMS_TO_TICKS(0);
  int trafficFlow = 0;
  int num = 0;
  while(1){

    vTaskDelay(1000);
    xQueuePeek(speed_Queue, &trafficFlow, xTicksToWait);

    //increase number of random traffic
    randomTraffic++;

    //if traffic flow is less than the random number then add another car to the queue
    if(randomTraffic % 3 == 0 || speed > 3){
      num = 1;
    }

    //send to car queue
    xQueueSendToBack(car_Queue, &num, 0);

  }

}
 

/*This task adjusts the traffic flow based on changes in the potentiometer (based on a 6 speed scale)*/
static void trafficFlowTask(void *pvParameters){
 
  int trafficFlow;
  while(1){

  //max adc value is 4025 ish so 64000/6 = 10667 (cause 6 speeds)
  trafficFlow = readADC() / 10667 ;
  //send new value to the speed queue
  xQueueSendToBack(speed_Queue,&trafficFlow , 0);
  ADC_SoftwareStartConv(ADC1);

  }
 }
 
/*this function reads from the adc and returns the value read */
uint16_t readADC(void){
  //max value: 4025?
  uint16_t adc_val =0;

  ADC_SoftwareStartConv(ADC1);
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
  adc_val = ADC_GetConversionValue(ADC1);

  printf("Current ADC Value: %d\n", adc_val);
  return adc_val;
}
 
 
 
void vApplicationMallocFailedHook( void )
 
{
 
/* The malloc failed hook is enabled by setting
 
configUSE_MALLOC_FAILED_HOOK to 1 in FreeRTOSConfig.h.
 
 
 
Called if a call to pvPortMalloc() fails because there is insufficient
 
free memory available in the FreeRTOS heap.  pvPortMalloc() is called
 
internally by FreeRTOS API functions that create tasks, queues, software 
 
timers, and semaphores.  The size of the FreeRTOS heap is set by the
 
configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
 
for( ;; );
 
}
 
/*-----------------------------------------------------------*/
 
 
 
void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
 
{

  ( void ) pcTaskName;

  ( void ) pxTask;



  /* Run time stack overflow checking is performed if

  configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook

  function is called if a stack overflow is detected.  pxCurrentTCB can be

  inspected in the debugger if the task name passed into this function is

  corrupt. */

  for( ;; );
 
}
 
/*-----------------------------------------------------------*/
 
 
 
void vApplicationIdleHook( void ){

  volatile size_t xFreeStackSpace;



  /* The idle task hook is enabled by setting configUSE_IDLE_HOOK to 1 in

  FreeRTOSConfig.h.



  This function is called on each cycle of the idle task.  In this case it

  does nothing useful, other than report the amount of FreeRTOS heap that

  remains unallocated. */

  xFreeStackSpace = xPortGetFreeHeapSize();



  if( xFreeStackSpace > 100 )

  {

  /* By now, the kernel has allocated everything it is going to, so

  if there is a lot of heap remaining unallocated then

  the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be

  reduced accordingly. */

  }
 
}
 
 
/*This function sets up adc gpio and sets priority bits*/
static void prvSetupHardware( void )
 
{
 
/* Ensure all priority bits are assigned as preemption priority bits.
 
http://www.freertos.org/RTOS-Cortex-M3-M4.html */
 
  NVIC_SetPriorityGrouping( 0 );
  GPIO_init();
  ADC_init();

}
