/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "usart.h"
#include "fireWork.h"
#include "bmp.h"
#include <oled_driver.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void CH446ResetAllSwitch();
void CH446QTurnOffSwitch(uint32_t switchADDR);
void CH446QTurnOnSwitch(uint32_t switchADDR);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for myTask03 */
osThreadId_t myTask03Handle;
const osThreadAttr_t myTask03_attributes = {
  .name = "myTask03",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask04 */
osThreadId_t myTask04Handle;
const osThreadAttr_t myTask04_attributes = {
  .name = "myTask04",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myBinarySem01 */
osSemaphoreId_t myBinarySem01Handle;
const osSemaphoreAttr_t myBinarySem01_attributes = {
  .name = "myBinarySem01"
};
/* Definitions for myBinarySem02 */
osSemaphoreId_t myBinarySem02Handle;
const osSemaphoreAttr_t myBinarySem02_attributes = {
  .name = "myBinarySem02"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void StartTask04(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myBinarySem01 */
  myBinarySem01Handle = osSemaphoreNew(1, 1, &myBinarySem01_attributes);

  /* creation of myBinarySem02 */
  myBinarySem02Handle = osSemaphoreNew(1, 1, &myBinarySem02_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* creation of myTask03 */
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

  /* creation of myTask04 */
  myTask04Handle = osThreadNew(StartTask04, NULL, &myTask04_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	LL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
	osDelay(500);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */

	//uint32_t i=0;
	OLED_Init();
	osDelay(500);
	OLED_Clear();
	OLED_DrawBMP(0,0,128,8,(unsigned char *)Bnana_BMP0);//
	osDelay(3000);
	OLED_Clear();
  /* Infinite loop */
  for(;;)
  {


	  	OLED_DrawBMP(0,0,128,8,(unsigned char *)FireWork1);//
	  	osDelay(50);
	  	OLED_DrawBMP(0,0,128,8,(unsigned char *)FireWork2);//??BMP????
	  	osDelay(50);
	  	OLED_DrawBMP(0,0,128,8,(unsigned char *)FireWork3);//??BMP????
	  	osDelay(50);
	  	OLED_DrawBMP(0,0,128,8,(unsigned char *)FireWork4);//??BMP????
	  	osDelay(50);
	  	OLED_DrawBMP(0,0,128,8,(unsigned char *)FireWork5);//??BMP????
	  	osDelay(50);
	  	OLED_DrawBMP(0,0,128,8,(unsigned char *)FireWork6);//??BMP????
	  	osDelay(50);
	  	OLED_DrawBMP(0,0,128,8,(unsigned char *)FireWork7);//??BMP????
	  	osDelay(50);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
	StartReception();
  /* Infinite loop */
	for(;;)
	{
		osSemaphoreAcquire(myBinarySem01Handle,osWaitForever);
		switch(pycommand)
		{
		case 1:
			printString("one\n");
			CH446QTurnOnSwitch(0x00000000);  // Y0X0
			CH446QTurnOnSwitch(0x00000011);  // Y1X1
			break;
		case 2:
			printString("two\n");
			CH446QTurnOffSwitch(0x00000000);  // Y0X0
			CH446QTurnOffSwitch(0x00000011);  // Y1X1
			break;
		case 3:
			printString("three\n");
			break;
		default:
			printString("None of the command\n");
		}
		osDelay(1);
	}
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void *argument)
{
  /* USER CODE BEGIN StartTask04 */
	CH446ResetAllSwitch();
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask04 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void CH446QTurnOnSwitch(uint32_t switchADDR)
{

	uint32_t portCPinMask;
	//set CH446Q_DAT_Pin
	LL_GPIO_SetOutputPin(CH446Q_DAT_GPIO_Port, CH446Q_DAT_Pin);
	//protect pins in port C other than C0->C6
	portCPinMask = LL_GPIO_ReadOutputPort(GPIOC);
	switchADDR+=portCPinMask&0xFFFFFF80;
	//write address in parallel mode
	LL_GPIO_WriteOutputPort(GPIOC, switchADDR);
	//generate a pulse to activate this setting
	LL_GPIO_ResetOutputPin(CH446Q_STB_GPIO_Port, CH446Q_STB_Pin);
	osDelay(1);
	LL_GPIO_SetOutputPin(CH446Q_STB_GPIO_Port, CH446Q_STB_Pin);
	osDelay(1);
	LL_GPIO_ResetOutputPin(CH446Q_STB_GPIO_Port, CH446Q_STB_Pin);

}

void CH446QTurnOffSwitch(uint32_t switchADDR)
{

	uint32_t portCPinMask;
	//set CH446Q_DAT_Pin
	LL_GPIO_ResetOutputPin(CH446Q_DAT_GPIO_Port, CH446Q_DAT_Pin);
	//protect pins in port C other than C0->C6
	portCPinMask = LL_GPIO_ReadOutputPort(GPIOC);
	switchADDR+=portCPinMask&0xFFFFFF80;
	//write address in parallel mode
	LL_GPIO_WriteOutputPort(GPIOC, switchADDR);
	//generate a pulse to activate this setting
	LL_GPIO_ResetOutputPin(CH446Q_STB_GPIO_Port, CH446Q_STB_Pin);
	osDelay(1);
	LL_GPIO_SetOutputPin(CH446Q_STB_GPIO_Port, CH446Q_STB_Pin);
	osDelay(1);
	LL_GPIO_ResetOutputPin(CH446Q_STB_GPIO_Port, CH446Q_STB_Pin);

}
void CH446ResetAllSwitch()
{
	LL_GPIO_SetOutputPin(CH446Q_RST_GPIO_Port, CH446Q_RST_Pin);

	LL_GPIO_SetOutputPin(CH446Q_CLK_GPIO_Port, CH446Q_CLK_Pin);


	LL_GPIO_ResetOutputPin(CH446Q_RST_GPIO_Port, CH446Q_RST_Pin);
}

/* USER CODE END Application */

