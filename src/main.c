#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef 		GPIO_InitStruct;

float distance=0;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  // TRIG PIN CONFIG

	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT; // tetikleme pini olduðu için output olarak tanýmladýk.
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

   // ECHO PIN CONFIG

	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN; // okuma yapacaðý için input olarak tanýmladýk
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;
 	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void delayUS(uint32_t time)
{
	uint32_t newTime = time * 21;
	while(newTime--);
}

float HCSR_Read()
{
	uint32_t time = 0;
	float templeDistance = 0;

	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	delayUS(10);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	delayUS(10);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	delayUS(10);

	while(!(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))); // echo'dan gelen veriyi okuyana kadar bekle

	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
	{
		time++;
		delayUS(1);
	}



	templeDistance = (float)time/58;  // datasheet'de eðer 58'e bölersek cm cinsinden öðreneceðimizi söylüyor.
	delayUS(1000);

	return templeDistance*10/7.2;
}

int main(void)
{
	GPIO_Config();
  while (1)
  {
	  distance  = HCSR_Read()+3;
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
