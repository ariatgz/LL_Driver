#include"stm32f4xx_ll_bus.h"
#include"stm32f4xx_ll_gpio.h"
#include"stm32f4xx_ll_adc.h"


void adc123_init(void);

uint32_t volatile sensor_value=0;

int main(){

	adc123_init();

	while(1){

		// start adc sampling
		LL_ADC_REG_StartConversionSWStart (ADC1);

		// wait for conversion to complete
		while(!LL_ADC_IsActiveFlag_EOCS (ADC1)){}

		// read converted value
		sensor_value=LL_ADC_REG_ReadConversionData32(ADC1);



	}



}

void adc123_init(){

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

	//Enabling clock access to the port GPIOA
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_1 , LL_GPIO_MODE_ANALOG);

	LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);

	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1,LL_ADC_CHANNEL_1);

	LL_ADC_REG_SetSequencerLength(ADC1,LL_ADC_REG_SEQ_SCAN_DISABLE);

	LL_ADC_Enable(ADC1);

}
