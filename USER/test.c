#include "sys.h"
#include "usart.h"	
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "motor.h"
#include "detector.h"

#include "usart2.h"
#include "hc05.h"
#include "string.h"

void xunji(void);

int main(void)
{	
	u8 sendbuf[20];	  
	u8 reclen=0;  
	
	Stm32_Clock_Init(9);
	delay_init(72);
	
	LED_Init(); 
	KEY_Init();
	PWM_Init(899,0);//pwmƵ��=72000/��899+1��=80Khz ����why�Ȳ���
	detectorInit();
	
	uart_init(72,9600); 	//����1��ʼ��Ϊ9600
	HC05_Init();	//��ʼ��ATK-HC05ģ��  
	
	while(1){
		
		if(USART2_RX_STA&0X8000)			//���յ�һ��������
		{		
 			reclen=USART2_RX_STA&0X7FFF;	//�õ����ݳ���
		  	USART2_RX_BUF[reclen]=0;	 	//���������
			
			if(strcmp((const char*)USART2_RX_BUF,"X")==0){
				xunji();
			}
			if(strcmp((const char*)USART2_RX_BUF,"F")==0)
			{	LED1=~LED1;
				carStraight(450,899);
				
			}
			if(strcmp((const char*)USART2_RX_BUF,"B")==0)
			{	LED1=~LED1;
				carBack(500,899);
			}
			if(strcmp((const char*)USART2_RX_BUF,"L")==0)
			{	
				LED1=~LED1;	//��LED1
				carLeft(300,899);
			}
			if(strcmp((const char*)USART2_RX_BUF,"R")==0)
			{	LED1=~LED1;
				carRight(400,300);
			}
			if(strcmp((const char*)USART2_RX_BUF,"S")==0)
			{	LED1=~LED1;
				carStop();
			}
 			USART2_RX_STA=0;	 
		}	 															     				   
	}
}
/*ѭ������
*/
void xunji(){
	
	u8 sendbuf[20];	  
	u8 reclen=0;  
	while(1){
		
		if(USART2_RX_STA&0X8000)			//���յ�һ��������
			{		
				reclen=USART2_RX_STA&0X7FFF;	//�õ����ݳ���
				USART2_RX_BUF[reclen]=0;	 	//���������
				
				if(strcmp((const char*)USART2_RX_BUF,"O")==0){
					//xunji();
					break;
				}
				USART2_RX_STA=0;	 
		}	 
		//�����߼�⵽����
		//�к����Ǹߵ�ƽ
		if(LEFT_DETECTOR == 1 && RIGHT_DETECTOR == 0){
			carLeft(100,899);
			delay_ms(500);
			//�ұ߼�⵽����
		}else if(RIGHT_DETECTOR == 1 && LEFT_DETECTOR == 0){
			carRight(600,300);
			delay_ms(500);
		}else{
			carStraight(400,600);
		}
	}	
}
	
	
