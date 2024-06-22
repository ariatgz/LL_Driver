#include"stm32f4xx_ll_usart.h"
#include"stm32f4xx_ll_gpio.h"
#include"stm32f4xx_ll_bus.h"

void uart2_init(void);
void uart2_write(int ch);
char uart2_read(void);
void led_init(void);
void psuedo_delay(volatile int delay);
void led_play(int val);
char rcv;

int main(){


	uart2_init();
	led_init();
	while(1){

		rcv = uart2_read();
		led_play(rcv);

	}




}

void uart2_init(){

	//Enable clock access for UART GPIO Pin.
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	// clock access to UART module
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

	// set mode of uart tx pin to AF
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_2 , LL_GPIO_MODE_ALTERNATE);

	// set mode of uart Rx pin to AF
	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_3 , LL_GPIO_MODE_ALTERNATE);

	// select uart tx alternate function type
	LL_GPIO_SetAFPin_0_7(GPIOA,LL_GPIO_PIN_2,LL_GPIO_AF_7 );

	// select uart Rx alternate function type
	LL_GPIO_SetAFPin_0_7(GPIOA,LL_GPIO_PIN_3,LL_GPIO_AF_7 );

	// configure uart protocol parameters
	LL_USART_Disable(USART2);

	LL_USART_SetTransferDirection(USART2,LL_USART_DIRECTION_TX_RX);

	//Configure all USART module parameters in one function.
	LL_USART_ConfigCharacter(USART2, LL_USART_DATAWIDTH_8B,LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);

	LL_USART_SetBaudRate(USART2, 16000000,
			LL_USART_OVERSAMPLING_16, 115200);

	LL_USART_Enable(USART2);
}

char uart2_read(){

	while(!LL_USART_IsActiveFlag_RXNE (USART2)){}
	return LL_USART_ReceiveData8(USART2);

}

void uart2_write(int ch){


	//wait for TXE flag to be set.
	//wait as long as the USART Enabled flag is false.
	while(!LL_USART_IsActiveFlag_TXE(USART2)){}
	LL_USART_TransmitData8(USART2,ch);


}

void led_init(){
	//Enabling clock access to the port GPIOA
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

		//setting the mode of the port A pin 5.
	LL_GPIO_SetPinMode (GPIOA,LL_GPIO_PIN_5 , LL_GPIO_MODE_OUTPUT);



}

void psuedo_delay(volatile int delay){

	for(int itr=0;itr<delay;itr++){

		for(int i=0;i<5000;i++){}
	}

}

void led_play(int val){

	//Taking mod 16 with the ascii value of any number will give us the number.
	val %= 16;
	for(;val>0;val--){
		LL_GPIO_SetOutputPin(GPIOA,LL_GPIO_PIN_5);
		psuedo_delay(70);
		LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_5);
	}

}
