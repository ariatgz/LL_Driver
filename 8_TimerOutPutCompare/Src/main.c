#include"stm32f4xx_ll_bus.h"
#include"stm32f4xx_ll_gpio.h"
#include"stm32f4xx_ll_tim.h"


void tim2_oc_init(void);
void led_init(void);

int main(){

	tim2_oc_init();
	led_init();


	while(1){



	}




}

void tim2_oc_init(void){

	//Enable clock access to TIM2 module
	LL_APB1_GRP1_EnableClock (LL_APB1_GRP1_PERIPH_TIM2);

	//Set the prescaler
	LL_TIM_SetPrescaler (TIM2, 1600-1); // 16 000 000 MHz /1600 = 10 000

	//set output compare mode :TOGGLE
	LL_TIM_OC_SetMode (TIM2,LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_TOGGLE);

	// enable the channel 1
	LL_TIM_CC_EnableChannel (TIM2, LL_TIM_CHANNEL_CH1);
	//Set auto-reload value
	LL_TIM_SetAutoReload (TIM2, 10000 - 1);

	//Reset the counter
	LL_TIM_SetCounter(TIM2,0);

	// Enable the timer
	LL_TIM_EnableCounter (TIM2);

}

void led_init(void){

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	//setting the mode of the port A pin 5.
	LL_GPIO_SetPinMode (GPIOA,LL_GPIO_PIN_5 , LL_GPIO_MODE_ALTERNATE);

	LL_GPIO_SetAFPin_0_7(GPIOA,LL_GPIO_PIN_5 ,LL_GPIO_AF_1);

}
