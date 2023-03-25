#ifndef BMP280_H_
#define BMP280_H_

#include <math.h>
#include "stm32f1xx_hal.h"

#define BMP280_dev_address 		0xEE

#define BMP280_SPI_MASK_WRITE 	0b01111111

#define BMP280_REG_CALIB      	0x88
#define BMP280_REG_DATA			0xF7

//REGISTER 0xF4
#define F4_osrs_t_skipped			0b00000000
#define F4_osrs_t_oversampling1		0b00100000
#define F4_osrs_t_oversampling2		0b01000000
#define F4_osrs_t_oversampling4		0b01100000
#define F4_osrs_t_oversampling8		0b10000000
#define F4_osrs_t_oversampling16	0b10100000

#define F4_osrs_p_skipped			0b00000000
#define F4_osrs_p_oversampling1		0b00000100
#define F4_osrs_p_oversampling2		0b00001000
#define F4_osrs_p_oversampling4		0b00001100
#define F4_osrs_p_oversampling8		0b00010000
#define F4_osrs_p_oversampling16	0b00010100

#define F4_mode_sleep				0b00000000
#define F4_mode_forced				0b00000001
#define F4_mode_normal				0b00000011

//REGISTER 0xF5
#define F5_t_sb_500us				0b00000000
#define F5_t_sb_62500us				0b00100000
#define F5_t_sb_125ms				0b01000000
#define F5_t_sb_250ms				0b01100000
#define F5_t_sb_500ms				0b10000000
#define F5_t_sb_1sec				0b10100000
#define F5_t_sb_2sec				0b11000000
#define F5_t_sb_4sec				0b11100000

#define F5_filter_1					0b00000000
#define F5_filter_2					0b00000010
#define F5_filter_5					0b00000100
#define F5_filter_11				0b00000110
#define F5_filter_22				0b00001010

#define F5_spi4w_en					0b00000000
#define F5_spi3w_en					0b00000001



extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi2;

typedef struct reading
{
	float temp;
	float press;
	float alti;
} read_value;

extern signed long temperature_raw, pressure_raw;
extern unsigned short dig_T1, dig_P1;
extern signed short dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
extern float temperature, pressure, altitude, init_height;


extern uint8_t spiReadWrite(uint8_t tx_message);
extern uint8_t readRegister(uint8_t address);
extern void writeRegister(uint8_t address, uint8_t value);
extern void readMBRegister(uint8_t address, uint8_t *values, uint8_t length);

extern struct reading BMP280_measure();
extern int32_t compensate_temperature(int32_t uncomp_temp);
extern uint32_t compensate_pressure(int32_t uncomp_pres);
extern void BMP280_get_calib_values();
extern void BMP280_init();
//extern void BMP280_calc_values(void);

#endif /* BMP280_H_ */
