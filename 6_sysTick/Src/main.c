#include"stm32f4xx_ll_rcc.h"
#include"stm32f4xx_ll_system.h"
#include"stm32f4xx_ll_utils.h"
#include"stm32f4xx_ll_gpio.h"
#include"stm32f4xx_ll_bus.h"

int main(void){

	SysTick_Config(16000);

	//Enable the clock
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	//setting the mode of the port A pin 5.
	LL_GPIO_SetPinMode (GPIOA,LL_GPIO_PIN_5 , LL_GPIO_MODE_OUTPUT);

	while(1){

			//Toggle the state of the pin in the specified port.
			LL_GPIO_TogglePin(GPIOA,LL_GPIO_PIN_5);
			LL_mDelay(1000);


		}


}

void SysTick_Handler(void){

}
