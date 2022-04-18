#include "stm32f10x.h"
#include "GPIO.h"
#include "delay.h"
#include "pwm.h"
#include "usart.h"
#include "stm32f10x.h"
#include "OLED.h"

 void Delay(u32 count)
 {
   u32 i=0;
   for(;i<count;i++);
 }
 int main(void)
 {	
	 
	 u16 t,s;  
	u16 len;	
	u16 times=0;
	 OLED_Init();
	 gpio_Init();
	 delay_init();	
	 uart_init(9600);
    TIM3_PWM_Init(600,71);
	
	 OLED_ShowString(1 , 1 , "hello world!");
	  OLED_ShowString(2 , 1 , "hello zhangkai!");
	  
  while(1)
	{

		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			switch(USART_RX_BUF[0]){
				case '1':moter_tLeft();break;
				case '2':moter_tRight();break;
				case '0':moter_straight();break;
				default:moter_stop();
			}
			
			printf("message==");
			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}
			printf("\r\n");//插入换行
			USART_RX_STA=0;
		}else
		{
			times++;
 
			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		}
	}	 
 }
 
