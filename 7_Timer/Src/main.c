#include"stm32f4xx_ll_bus.h"
#include"stm32f4xx_ll_gpio.h"
#include"stm32f4xx_ll_tim.h"


void tim2_1hz_init(void);
void led_init(void);

int main(){

	tim2_1hz_init();
	led_init();


	while(1){

		while(!(LL_TIM_IsActiveFlag_UPDATE(TIM2))){

		}
		LL_TIM_ClearFlag_UPDATE(TIM2);
		LL_GPIO_TogglePin(GPIOA,LL_GPIO_PIN_5);



	}




}

void tim2_1hz_init(void){

	//Enable clock access to TIM2 module
	LL_APB1_GRP1_EnableClock (LL_APB1_GRP1_PERIPH_TIM2);

	//Set the prescaler
	LL_TIM_SetPrescaler (TIM2, 1600-1); // 16 000 000 MHz /1600 = 10 000

	//Set auto-reload value
	LL_TIM_SetAutoReload (TIM2, 10000 - 1);

	// Enable the timer
	LL_TIM_EnableCounter (TIM2);

}

void led_init(void){

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	//setting the mode of the port A pin 5.
	LL_GPIO_SetPinMode (GPIOA,LL_GPIO_PIN_5 , LL_GPIO_MODE_OUTPUT);

}
