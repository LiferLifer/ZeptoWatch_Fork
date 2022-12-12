#include "power.h"

#include "delay.h"

#include "brightness.h"
#include "vibrator.h"

TIM_HandleTypeDef *Power_TIMHandle = nullptr;

/* 0: Normal
 * 1: Pause
 * 2: Shutdown */
int Power_CurrentState = 0;

void Power_SetTIMHandle(TIM_HandleTypeDef *htim) {
	Power_TIMHandle = htim;
}

int Power_GetState() {
	return Power_CurrentState;
}

void Power_SetState(int state) {
	if (state == 0 || state == 1 || state == 2) {
		Power_CurrentState = state;
	}
}

void Power_InterruptHandler_Key() {
	if (Power_TIMHandle == nullptr) return;
	Delay_ms(50);
	GPIO_PinState tmpState = HAL_GPIO_ReadPin(KEY_INT_GPIO_Port, KEY_INT_Pin);
	Delay_ms(50);
	if (HAL_GPIO_ReadPin(KEY_INT_GPIO_Port, KEY_INT_Pin) == tmpState) {
		if (tmpState == GPIO_PIN_RESET) {
			// Falling -> Released
			HAL_TIM_Base_Stop_IT(Power_TIMHandle);
			if (Power_GetState() == 2) {
				// Long Pressed
				// TODO: Shuting down UI.
				Delay_ms(200);
				HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
				HAL_PWR_EnterSTANDBYMode();
			} else {
				// Short Pressed
				if (Power_GetState() == 0) {
					Power_SetState(1);
					Brightness_GoDark();
//					while (Power_GetState() == 1) HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
				} else {
					Power_SetState(0);
					Brightness_LightUp();
				}
			}
		} else {
			// Rising -> Pressed
			__HAL_TIM_SET_COUNTER(Power_TIMHandle, 0);
			__HAL_TIM_CLEAR_IT(Power_TIMHandle, TIM_IT_UPDATE); // Clear flag to avoid the immediate trigger.
			HAL_TIM_Base_Start_IT(Power_TIMHandle);
		}
	}
	Delay_ms(200);
}

void Power_InterruptHandler_Tim() {
	if (Power_TIMHandle == nullptr) return;
	HAL_TIM_Base_Stop_IT(Power_TIMHandle);
	Power_SetState(2);
}
