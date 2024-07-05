#include"stm32f4xx_ll_bus.h"
#include"stm32f4xx_ll_gpio.h"
#include"stm32f4xx_ll_exti.h"
#include"stm32f4xx_ll_system.h"

void gpio_interrupt_init(void);
void led_init(void);
void EXTI15_10_IRQHandler();
void button_callback();

int main(){
	gpio_interrupt_init();
	led_init();



}


void gpio_interrupt_init(void){

	//Enabling clock access to the port GPIOA
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);


	//setting the mode of the port c pin 13.
	LL_GPIO_SetPinMode (GPIOC,LL_GPIO_PIN_13 , LL_GPIO_MODE_INPUT);

	//Enable clock access to interrupt module
	LL_APB2_GRP1_EnableClock (LL_APB2_GRP1_PERIPH_SYSCFG);

	//Set the source for External Interrupt which is our button in this case
	LL_SYSCFG_SetEXTISource (LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);

	//Enabling the interrupt line. Line = port of source
	LL_EXTI_EnableIT_0_31 (LL_EXTI_LINE_13);

	//The trigger for our interrupt which is the Falling edge in our case.
	LL_EXTI_EnableFallingTrig_0_31 (LL_EXTI_LINE_13);

	//Enabling the Interrupt controller for line 10 to 15
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	//Setting the priority of the line we enable.
	NVIC_SetPriority(EXTI15_10_IRQn,0);
}

void led_init(void){

	//setting the mode of the port A pin 5.
	LL_GPIO_SetPinMode (GPIOA,LL_GPIO_PIN_5 , LL_GPIO_MODE_OUTPUT);

		//Enabling clock access to the port GPIOC
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

}

void EXTI15_10_IRQHandler(){

	//checks to see if the line that we are interested in was enabled.
	if(LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_13)!= RESET){
		button_callback();
	}
	//clear the flag for the line so it's not triggered twice.
	LL_EXTI_ClearFlag_0_31 (LL_EXTI_LINE_13);

}

void button_callback(){

	LL_GPIO_TogglePin(GPIOA,LL_GPIO_PIN_5);

}
