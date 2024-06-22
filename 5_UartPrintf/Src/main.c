#include"stm32f4xx_ll_usart.h"
#include"stm32f4xx_ll_gpio.h"
#include"stm32f4xx_ll_bus.h"
#include<stdio.h>

void uart2_init(void);
void uart2_write(int ch);

int __io_putchar(int ch){

	uart2_write(ch);
	return ch;

}


int main(){

	uart2_init();
	while(1){

		printf("Hello from stm32F446 \n\r");
		for(int itr=0;itr<90000;itr++){

		}

	}




}

void uart2_init(){

	//Enable clock access for UART GPIO Pin.
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	// clock access to UART module
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

	// set mode of uart tx pin to AF
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_2 , LL_GPIO_MODE_ALTERNATE);

	// select uart tx alternate function type
	LL_GPIO_SetAFPin_0_7(GPIOA,LL_GPIO_PIN_2,LL_GPIO_AF_7 );

	// configure uart protocol parameters
	LL_USART_Disable(USART2);

	LL_USART_SetTransferDirection(USART2,LL_USART_DIRECTION_TX);

	//Configure all USART module parameters in one function.
	LL_USART_ConfigCharacter(USART2, LL_USART_DATAWIDTH_8B,LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);

	LL_USART_SetBaudRate(USART2, 16000000,
			LL_USART_OVERSAMPLING_16, 115200);

	LL_USART_Enable(USART2);
}

void uart2_write(int ch){


	//wait for TXE flag to be set.
	//wait as long as the USART Enabled flag is false.
	while(!LL_USART_IsActiveFlag_TXE(USART2)){}
	LL_USART_TransmitData8(USART2,ch);


}
