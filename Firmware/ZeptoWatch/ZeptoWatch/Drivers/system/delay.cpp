#include "delay.h"

#include "tim.h"

void Delay_us(uint32_t t) {
	uint32_t delay = (HAL_RCC_GetHCLKFreq() / 6000000 * t);
	while (delay --) __NOP();
//	__HAL_TIM_SET_COUNTER(&htim7, 0);
//	__HAL_TIM_ENABLE(&htim7);
//	while (__HAL_TIM_GET_COUNTER(&htim7) < t);
//	__HAL_TIM_DISABLE(&htim7);
}

void Delay_ms(uint32_t t) {
	Delay_us(1000 * t); // HAL_Delay 依赖于 HAL Tick, 无法在中断之类的场景使用
}
