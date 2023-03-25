/*
 * DHT11.h
 *
 *  Created on: Feb 15, 2023
 *      Author: acer
 */
#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#endif /* INC_DHT11_H_ */

#define DHT11_PORT GPIOB
#define DHT11_PIN GPIO_PIN_9

extern TIM_HandleTypeDef htim1;
//structure to store DHT11 sensor values
typedef struct DHT11_value
{
	uint8_t DHT11_temp,DHT11_humi;
}DHT11_read_value;

extern uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
extern uint16_t SUM, RH, TEMP;

extern void delay (uint16_t time);
/*************************GPIO pin configuration*****************************/
extern void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
extern void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/*************************DHT11 Function*************************************/
extern void DHT11_Start (void);
extern uint8_t DHT11_Read (void);
extern uint8_t DHT11_Check_Response (void);
extern DHT11_read_value DHT11_Print_Value(void);
