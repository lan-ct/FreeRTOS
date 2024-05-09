/**
 ****************************************************************************************************
 * @file        freertos.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS ��ֲʵ��
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽����F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "freertos_demo.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
/*FreeRTOS*********************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"

/******************************************************************************************************/
/*FreeRTOS����*/

/* START_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define START_TASK_PRIO 1                   /* �������ȼ� */
#define START_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            StartTask_Handler;  /* ������ */
void start_task(void *pvParameters);        /* ������ */

/* TASK1 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK1_PRIO      2                   /* �������ȼ� */
#define TASK1_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Task1Task_Handler;  /* ������ */
void task1(void *pvParameters);             /* ������ */

/* TASK2 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK2_PRIO      2                 /* �������ȼ� */
#define TASK2_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Task2Task_Handler;  /* ������ */
void task2(void *pvParameters);             /* ������ */

/******************************************************************************************************/

/* LCDˢ��ʱʹ�õ���ɫ */
uint16_t lcd_discolor[11] = {WHITE, BLACK, BLUE, RED,
                             MAGENTA, GREEN, CYAN, YELLOW,
                             BROWN, BRRED, GRAY};

/**
 * @brief       FreeRTOS������ں���
 * @param       ��
 * @retval      ��
 */
uint32_t num=0;
void freertos_demo(void)
{
    lcd_show_string(10, 10, 220, 32, 32, "STM32", RED);
    lcd_show_string(10, 47, 220, 24, 24, "FreeRTOS Porting", RED);
    lcd_show_string(10, 76, 220, 16, 16, "ATOM@ALIENTEK", RED);
    lcd_clear(WHITE);                      /* ˢ����Ļ */
    xTaskCreate((TaskFunction_t )task1,
                (const char*    )"task1",
                (uint16_t       )TASK1_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK1_PRIO,
                (TaskHandle_t*  )&Task1Task_Handler);
    /* ��������2 */
    xTaskCreate((TaskFunction_t )task2,
                (const char*    )"task2",
                (uint16_t       )TASK2_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK2_PRIO,
                (TaskHandle_t*  )&Task2Task_Handler);
    vTaskStartScheduler();
}

/**
 * @brief       start_task
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 */
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* �����ٽ��� */
    /* ��������1 */
    
    
    taskEXIT_CRITICAL();            /* �˳��ٽ��� */
    vTaskDelete(StartTask_Handler); /* ɾ����ʼ���� */
    
}

/**
 * @brief       task1
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 */
void task1(void *pvParameters)
{ 
   
    char s[10]="     ";
    uint16_t times=5;
    while(times--)
    { 
        //times--;
        s[5-times-1]=num+'0';
        num=num+1;
        lcd_show_string(10, 10, 220, 32, 32, s, RED);
        //lcd_show_string(10, 47, 220, 24, 24, "FreeRTOS Porting", RED);
        //lcd_show_string(10, 76, 220, 16, 16, "ATOM@ALIENTEK", RED);
        
        //vTaskDelay(1000);                                               /* ��ʱ1000ticks */
        if(times==3){
            vTaskSuspendAll();
        }
    }
    vTaskDelete(Task1Task_Handler);
    //xTaskResumeAll();
   /* times--;
    s[5-times-1]=num+'0';
    num++;
    lcd_show_string(10, 10, 220, 32, 32, s, RED);
        //lcd_show_string(10, 47, 220, 24, 24, "FreeRTOS Porting", RED);
        //lcd_show_string(10, 76, 220, 16, 16, "ATOM@ALIENTEK", RED);
        
    vTaskDelay(1000);    
    //////lcd_show_string(10, 10, 220, 32, 32, num, RED);
    lcd_show_string(10, 76, 220, 32, 32, "s", RED);*/
}

/**
 * @brief       task2
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 */
void task2(void *pvParameters)
{  
            /* �����ٽ��� */
    uint16_t times=5;
    char s[10]="     ";
    while(times--)
    {
        s[5-times-1]=num+'0';
        times++;
        times--;
        num=num+1;
        lcd_show_string(10, 47, 220, 32, 32, s, BLUE);
      //  lcd_show_string(10, 47, 220, 24, 24, "FreeRTOS Porting", RED);
      //  lcd_show_string(10, 76, 220, 16, 16, "ATOM@ALIENTEK", RED);
       // vTaskDelay(1000);                                               /* ��ʱ1000ticks */
    }////
             /* �˳��ٽ��� */
    //vTaskResume(Task1Task_Handler);
    vTaskDelete(Task2Task_Handler);
}
