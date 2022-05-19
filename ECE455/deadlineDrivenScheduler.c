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
#define DD_SCHEDULER_PRIO configMAX_PRIORITIES-1
#define GENERATOR_PRIO configMAX_PRIORITIES-2
#define HIGH_PRIO configMAX_PRIORITIES-3
#define LOW_PRIO 2
#define Aux_STACK_SIZE ((unsigned short ) 30)
#define Mul_Divider 00111
#define schQUEUE_LENGTH 3
#define genQUEUE_LENGTH 3
#define tcQUEUE_LENGTH 3

/*-----------------------------------------------------------*/
enum task_type {
	PERIODIC,
	APERIODIC
}task_type;

enum Request_Types{
	create,
	delete,
	return_active_list,
	return_overdue_list
}Request_Types;

typedef struct dd_task{
	TaskHandle_t t_handle;
	enum task_type t_type;
	uint32_t task_id;
	uint32_t release_time;
	uint32_t absolute_deadline;
	uint32_t completion_time;
	uint32_t execution_cycle;
}dd_task;

typedef struct node{
	struct dd_task data;
	enum task_type type;
	struct node *next;
}node;

enum Priorities{
	HIGH = 1,
	LOW = tskIDLE_PRIORITY
};

//LIGHTS
#define RED GPIO_Pin_0
#define YELLOW GPIO_Pin_1
#define GREEN GPIO_Pin_2
#define POT GPIO_Pin_3

//FUNCTIONS
static TaskHandle_t dd_tcreate(dd_task task);
static void dd_tdelete(dd_task  task);
static node* sort_list(node *head, dd_task task);
static void Delay_Init(void );
void prvSetupHardware( void );
void GPIO_init(void);
node* remove_node(node* head, dd_task task);

//CALLBACKS
void task1TimerCallback(TimerHandle_t xTimer);
void task2TimerCallback(TimerHandle_t xTimer);
void task3TimerCallback(TimerHandle_t xTimer);


//TASKS
static void DD_scheduler_Task( void *pvParameters );
static void User_1_Task (void *pvParameters);
static void User_2_Task (void *pvParameters);
static void User_3_Task (void *pvParameters);
static void Task_Generator( void *pvParameters);
static void Monitor_Task( void *pvParameters );

uint32_t EXECUTION = 0;
uint32_t multiplier =0;
volatile uint32_t utilization=0;
TickType_t CURRENT_SLEEP=0;

//QUEUE HANDLERS
xQueueHandle task_queue = 0;
xQueueHandle task_generation_queue = 0;
xQueueHandle completed_task_queue = 0;
xQueueHandle current_task = 0;
xQueueHandle overdue_task_queue = 0;

//TIMER HANDLERS
xTimerHandle task1_timer;
xTimerHandle task2_timer;
xTimerHandle task3_timer;

//TASK HANDLERS
TaskHandle_t task1_Handle;
TaskHandle_t task2_Handle;
TaskHandle_t task3_Handle;
TaskHandle_t taskGenerator_Handle;
TaskHandle_t taskScheduler_Handle;
TaskHandle_t taskMonitor_Handle;

/*-----------------------------------------------------------*/

int main(void)
{


	prvSetupHardware();

	/*initialize the multiplier that is used to convert delay into cycle.*/
	Delay_Init();

	//create queues
	task_queue = xQueueCreate(100, sizeof(node*));
	completed_task_queue = xQueueCreate(100, sizeof(node*));
	//overdue_task_queue = xQueueCreate(100, sizeof(node*));
	current_task = xQueueCreate(100, sizeof(dd_task*));
	task_generation_queue = xQueueCreate(100, sizeof(int*));

	//create timers (for tasks 1 2 and 3) => note values for pdMS to ticks are hard coded rn but can be adjusted for different trials
	task1_timer = xTimerCreate("timer1", pdMS_TO_TICKS(500), pdTRUE, (void *) 0, task1TimerCallback);
	task2_timer = xTimerCreate("timer2", pdMS_TO_TICKS(800), pdTRUE, (void *) 0, task2TimerCallback);
	task3_timer = xTimerCreate("timer3", pdMS_TO_TICKS(750), pdTRUE, (void *) 0, task3TimerCallback);


	//create tasks
	xTaskCreate(Task_Generator, "taskGenerator", configMINIMAL_STACK_SIZE, NULL, 3 , &taskGenerator_Handle);
	xTaskCreate(DD_scheduler_Task, "ddScheduler", configMINIMAL_STACK_SIZE, NULL, 4, &taskScheduler_Handle);
	//xTaskCreate(Monitor_Task, "monitorTask", configMINIMAL_STACK_SIZE, NULL, 5, &taskMonitor_Handle);
	xTaskCreate(User_1_Task, "task1", configMINIMAL_STACK_SIZE, NULL, LOW , &task1_Handle);
	xTaskCreate(User_2_Task, "task2", configMINIMAL_STACK_SIZE, NULL, LOW , &task2_Handle);
	xTaskCreate(User_3_Task, "task3", configMINIMAL_STACK_SIZE, NULL, LOW , &task3_Handle);


	/* Add to the registry, for the benefit of kernel aware debugging. */
	vQueueAddToRegistry(task_queue, "taskQueue");
	vQueueAddToRegistry(task_generation_queue, "taskGeneratorQueue");
	vQueueAddToRegistry(completed_task_queue, "completedTaskQueue");
	vQueueAddToRegistry(current_task, "currentTask");
	//vQueueAddToRegistry(overdue_task_queue, "overdueTaskQueue");

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	for( ;; ); // we should never get here!

	return 0;
}


//callback function for task 1 timer
void task1TimerCallback(TimerHandle_t xTimer){
	int task_id = 1;
	xQueueSend(task_generation_queue, (void *) &task_id, (TickType_t ) 0);
	vTaskResume(taskGenerator_Handle);
}


//callback function for task 2 timer
void task2TimerCallback(TimerHandle_t xTimer){
	int task_id = 2;
	xQueueSend(task_generation_queue, (void *) &task_id, (TickType_t ) 0);
	vTaskResume(taskGenerator_Handle);
}

//callback function for task 3 timer
void task3TimerCallback(TimerHandle_t xTimer){
	int task_id = 3;
	xQueueSend(task_generation_queue, (void *) &task_id, (TickType_t ) 0);
	vTaskResume(taskGenerator_Handle);
}


static void Delay_Init(void)
{
	 RCC_ClocksTypeDef RCC_Clocks;
	 /* Get system clocks */
	 RCC_GetClocksFreq(&RCC_Clocks);
	 /* While loop takes 4 cycles */
	 /* For 1 ms delay, we need to divide with 4K */
	 printf("Freq: %d \n", RCC_Clocks.HCLK_Frequency);
	 multiplier = RCC_Clocks.HCLK_Frequency / Mul_Divider; // to calculate 1 msec

}


/*-----------------Real Tasks--------------------------------*/


/*
 * This task manages scheduling the dd tasks by adjusting their priority as an F task
 */
static void DD_scheduler_Task( void *pvParameters )
{
	//for the purpose of resume task
	vTaskSuspend(task1_Handle);
	vTaskSuspend(task2_Handle);
	vTaskSuspend(task3_Handle);
	vTaskSuspend(taskMonitor_Handle);


	// This is for initialization and to give the generator task to have a chance to run at the start of the program.
	CURRENT_SLEEP = 100;
	while(1)
	{

		node* active_list = NULL;

		//check first last in the active task list and make a high priority
		if(xQueueReceive(task_queue, &active_list, CURRENT_SLEEP)){

			if(active_list->data.t_handle == task1_Handle){
				//Make U Task 1 highest priority
				vTaskPrioritySet(task1_Handle, HIGH);
				vTaskPrioritySet(task2_Handle, LOW);
				vTaskPrioritySet(task3_Handle, LOW);

			}else if(active_list->data.t_handle == task2_Handle){
				vTaskPrioritySet(task1_Handle, LOW);
				vTaskPrioritySet(task2_Handle, HIGH);
				vTaskPrioritySet(task3_Handle, LOW);

			}else if(active_list->data.t_handle == task3_Handle){
				vTaskPrioritySet(task1_Handle, LOW);
				vTaskPrioritySet(task2_Handle, LOW);
				vTaskPrioritySet(task3_Handle, HIGH);
			}
		}

		vTaskSuspend(NULL);
	}
}
/*
 * The task generator function creates 3 dd_tasks (1 2 and 3).
 */
static void Task_Generator( void *pvParameters )
{

	//start timers for tasks 1 2 and 3
	xTimerStart(task1_timer, 0);
	xTimerStart(task2_timer, 0);
	xTimerStart(task3_timer, 0);

	int task_id = 0;
	int id = 0;

	while(1)
	{

		//only create task when a timer has finished
		if(xQueueReceive(task_generation_queue, &id, portMAX_DELAY) == pdPASS){

			if(id == 1){
				//create task 1
				dd_task dd_task1;
				dd_task1.t_handle = task1_Handle;
				dd_task1.task_id = task_id;
				dd_task1.t_type = PERIODIC;
				dd_task1.release_time = 0;
				dd_task1.absolute_deadline = 2000;
				dd_task1.completion_time = 2000;
				dd_task1.execution_cycle = 5000;

				if(dd_tcreate(dd_task1) == NULL){
						printf("dd_tcreate 1 Failed!\n");
				}

				//update current task
				xQueueSend(current_task, (void *) &dd_task1, (TickType_t ) 0);
				vTaskResume(task1_Handle);

			}else if (id == 2){

				//create task 2
				dd_task dd_task2;
				dd_task2.t_handle = task2_Handle;
				dd_task2.t_type = PERIODIC;
				dd_task2.task_id = task_id;
				dd_task2.release_time = 1000;
				dd_task2.absolute_deadline = 4000;
				dd_task2.completion_time = 2000;
				dd_task2.execution_cycle = 5000;

				if(dd_tcreate(dd_task2) == NULL){
					printf("dd_tcreate 2 Failed!\n");
				}

				//update current task
				xQueueSend(current_task, (void *) &dd_task2, (TickType_t ) 0);
				vTaskResume(task2_Handle);

			}else if (id == 3){

				//create task 3
				dd_task dd_task3;
				dd_task3.t_handle = task3_Handle;
				dd_task3.t_type = PERIODIC;
				dd_task3.release_time = 3000;
				dd_task3.task_id = task_id;
				dd_task3.absolute_deadline = 5000;
				dd_task3.completion_time = 2000;
				dd_task3.execution_cycle = 5000;

				if(dd_tcreate(dd_task3) == NULL){
					printf("dd_tcreate 3 Failed!\n");
				}

				//update current task
				xQueueSend(current_task, (void *) &dd_task3, (TickType_t ) 0);
				vTaskResume(task3_Handle);

			}
			//task was generated so now wake up scheduler
			task_id++;
			vTaskResume(taskScheduler_Handle);
			vTaskSuspend(NULL);
		}
	}
}

/*
 * This task is used for monitoring/debuging purposes. This function prints the task list (tasks to be scheduled) and the completed task list
 */
static void Monitor_Task( void *pvParameters )
{

	while(1){

		struct node* list = NULL;
		xQueuePeek(task_queue, &list, 0);

		printf("<<<<<<<<<<<<<<<<<<<= ACTIVE TASK LIST =>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n ");
		if(list != NULL){
			while(list->next != NULL){
				printf("Task id = %d , absolute deadline = %d \n", list->data.task_id, list->data.absolute_deadline );
				list = list->next;
			}
			printf("Task id = %d , absolute deadline = %d \n", list->data.task_id, list->data.absolute_deadline );
		}

		xQueuePeek(completed_task_queue, &list, 0);

		printf("<<<<<<<<<<<<<<<<<<<= COMPLETED TASK LIST =>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n ");

		if(list != NULL){
			while(list->next != NULL){
				printf("Task id = %d , absolute deadline = %d \n", list->data.task_id, list->data.absolute_deadline );
				list = list->next;
			}
			printf("Task id = %d , absolute deadline = %d \n", list->data.task_id, list->data.absolute_deadline );
		}


xQueuePeek(overdue_task_queue, &list, 0);

printf(“OVERDUE TASK LIST =>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n ");

		if(list != NULL){
			while(list->next != NULL){
				printf("Task id = %d , absolute deadline = %d \n", list->data.task_id, list->data.absolute_deadline );
				list = list->next;
			}
			printf("Task id = %d , absolute deadline = %d \n", list->data.task_id, list->data.absolute_deadline );
		}


		vTaskDelay(1500);
	}

}


/*-----------------Functions--------------------------------*/


/*
 * dd_tcreate accepts a task and will add that task to the active task list. It will also update the task queue with the new task
 */
static TaskHandle_t dd_tcreate(dd_task  task)
{

	//grab active task list from the queue
	struct node* active_list = NULL;
	xQueueReceive(task_queue, &active_list, 0);
	active_list = sort_list(active_list, task);

	//send updated list to the scheduler (through the task queue)
	xQueueSend(task_queue, (void *) &active_list, (TickType_t ) 0);
	
	return task.t_handle;

}

/*
 * This function accepts a dd task. It will add remove this task from the active list and add it to the completed list
 */
static void dd_tdelete(dd_task  task)
{

	//remove task from active list
	struct node* active_list = NULL;
	xQueueReceive(task_queue, &active_list, 0);
	active_list = sort_list(active_list, task);
	remove_node(active_list, task);

	//add to completed list (send to queue!)
	struct node* completed_list = NULL;
	xQueueReceive(completed_task_queue, &completed_list, 0);

	xQueueSend(completed_task_queue, (void *) &completed_list, (TickType_t ) 0);
}

static void User_1_Task (void *pvParameters)
{
	dd_task *AuxTaskParam = (dd_task *) pvParameters;
	uint32_t *cycles = &(AuxTaskParam->execution_cycle);
	//printf("AST %d\n", xTaskGetTickCount());
	while (1)
	{

		//turn on green led
		GPIO_ResetBits(GPIOC, RED);
		GPIO_ResetBits(GPIOC, YELLOW);
		GPIO_SetBits(GPIOC, GREEN);

		while ((*cycles)--);
		GPIO_ResetBits(GPIOC, GREEN);
		printf("User 1 Task: AET %d\n", xTaskGetTickCount());

		//grab current task and send to be deleted
		dd_task curr_task;
		xQueueReceive(current_task, &curr_task, 0);
		dd_tdelete(curr_task);
		vTaskSuspend(NULL);
	}
}

static void User_2_Task (void *pvParameters)
{
	dd_task *AuxTaskParam = (dd_task *) pvParameters;
	uint32_t *cycles = &(AuxTaskParam->execution_cycle);
	//printf("AST %d\n", xTaskGetTickCount());
	while (1)
	{
		//turn on yellow led
		GPIO_ResetBits(GPIOC, RED);
		GPIO_ResetBits(GPIOC, GREEN);
		GPIO_SetBits(GPIOC, YELLOW);

		while ((*cycles)--);
		GPIO_ResetBits(GPIOC, YELLOW);
		// delete the task!
		printf("User 2 Task: AET %d\n", xTaskGetTickCount());

		//grab current task and send to be deleted
		dd_task curr_task;
		xQueueReceive(current_task, &curr_task, 0);
		dd_tdelete(curr_task);
		vTaskSuspend(NULL);
	}
}

static void User_3_Task (void *pvParameters)
{
	dd_task *AuxTaskParam = (dd_task *) pvParameters;
	uint32_t *cycles = &(AuxTaskParam->execution_cycle);
	//printf("AST %d\n", xTaskGetTickCount());
	while (1)
	{
		//turn on red led
		GPIO_ResetBits(GPIOC, YELLOW);
		GPIO_ResetBits(GPIOC, GREEN);
		GPIO_SetBits(GPIOC, RED);

		while ((*cycles)--);
		GPIO_ResetBits(GPIOC, RED);
		// delete the task!
		printf("User 3 Task: AET %d\n", xTaskGetTickCount());

		//grab current task and send to be deleted
		dd_task curr_task;
		xQueueReceive(current_task, &curr_task, 0);
		dd_tdelete(curr_task);
		vTaskSuspend(NULL);
	}
}



/*
 * This function accepts a reference to the head of a list and a dd_task and adds that task to the sorted list
 */
node* sort_list(node* head, dd_task task){

	//create node
	node* new_node = (node*)malloc(sizeof(node));
	new_node->data = task;
	new_node->next = NULL;


	if(head == NULL){
		head = new_node;
	}else{

		node* curr = head;
		uint32_t deadline = task.absolute_deadline;

		while(curr->next != NULL && curr->next->data.absolute_deadline < deadline){
			curr = curr->next;
		}
		new_node->next = curr->next;
		curr->next = new_node;
	}
	return head;
}


/*
 * This function accepts a reference to the head of a list and the id for the task to be removed and removes that task from the sorted list
 */
node* remove_node(node* head, dd_task task){

	node* temp = head;
	node* prev = NULL;

	int task_id = task.task_id;

	//if element is first node remove and return next element as new head
	if(temp != NULL && temp->data.task_id == task_id){
		return temp->next;

	}else{
		while(temp != NULL && temp->data.task_id != task_id){
			prev = temp;
			temp = temp->next;
		}
	}

	//id was not found
	if(temp == NULL){
		return NULL;
	}

	prev->next = temp->next;

	//free the node
	free(temp);

	return head;
}

/*----------------------------------------------------------*/
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

void prvSetupHardware( void )
{
	/* Ensure all priority bits are assigned as preemption priority bits.
	http://www.freertos.org/RTOS-Cortex-M3-M4.html */
	NVIC_SetPriorityGrouping( 0 );
	GPIO_init();
	utilization++;

	/* TODO: Setup the clocks, etc. here, if they were not configured before
	main() was called. */
}

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

}




void vApplicationIdleHook( void )
{
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

/*-----------------------------------------------------------*/
