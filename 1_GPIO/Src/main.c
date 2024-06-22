#include"stm32f4xx_ll_bus.h"
#include"stm32f4xx_ll_gpio.h"


int main(){

		//Enabling clock access to the port GPIOA
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

		//setting the mode of the port A pin 5.
	LL_GPIO_SetPinMode (GPIOA,LL_GPIO_PIN_5 , LL_GPIO_MODE_OUTPUT);

	while(1){

		//Toggle the state of the pin in the specified port.
		LL_GPIO_TogglePin(GPIOA,LL_GPIO_PIN_5);
		for(int itr=0;itr<900000;itr++){
			// This loop is here to waste time.
		}


	}

}
