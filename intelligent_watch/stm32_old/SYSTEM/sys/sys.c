#include "sys.h"  

//********************************************************************************
//�޸�˵��
//��
//////////////////////////////////////////////////////////////////////////////////  

/*THUMBָ�֧�ֻ������
�������·���ʵ��ִ�л��ָ��WFI 
WFI�ǵȴ��жϣ�Wait For Interrupt������д����ִ������ָ��ʱ��
CPU�����͹���״̬��ֱ�����жϷ���ʱ�Żỽ��*/
__asm void WFI_SET(void)
{
	WFI;		  
}

//�ر������ж�(���ǲ�����fault��NMI�ж�)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}

//���������ж�
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}

//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}

///* �ض��򣬿�ʹ��printf����,��Ҫ��������Ĵ���*/
//struct __FILE { int handle; /* Add whatever you need here */ };
//FILE __stdout;
//FILE __stdin;

//int fputc(int ch, FILE *f)
//{
//	USART_SendData(USART1,ch);	
//	while( USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET );
//		
//	return ch;
//}
