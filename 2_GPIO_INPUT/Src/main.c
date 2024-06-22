#include"stm32f4xx_ll_bus.h"
#include"stm32f4xx_ll_gpio.h"


int main(){

	//Enabling clock access to the port GPIOA
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

		//setting the mode of the port A pin 5.
	LL_GPIO_SetPinMode (GPIOA,LL_GPIO_PIN_5 , LL_GPIO_MODE_OUTPUT);

		//Enabling clock access to the port GPIOC
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

		//setting the mode of the port c pin 13.
	LL_GPIO_SetPinMode (GPIOC,LL_GPIO_PIN_13 , LL_GPIO_MODE_INPUT);



	while(1){
		if(LL_GPIO_IsInputPinSet(GPIOC,LL_GPIO_PIN_13)){

			LL_GPIO_ResetOutputPin (GPIOA, LL_GPIO_PIN_5);
		}else{

			LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5);

		}


	}

}
