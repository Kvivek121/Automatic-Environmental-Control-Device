#include "BMP280.h"
#include "liquidcrystal_i2c.h"

signed long temperature_raw, pressure_raw;
unsigned short dig_T1, dig_P1;
signed short dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
float temperature, pressure, altitude, init_height;

float p_reference = 95500;
int32_t t_fine = 0;

uint8_t readRegister(uint8_t address)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);//spiCSNlow();
	spiReadWrite(address);
	uint8_t value = spiReadWrite(0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);//spiCSNhigh();
	return value;
}

void writeRegister(uint8_t address, uint8_t value)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);//spiCSNlow();
	spiReadWrite(address & BMP280_SPI_MASK_WRITE);
	spiReadWrite(value);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);//spiCSNhigh();
}

void readMBRegister(uint8_t address, uint8_t *values, uint8_t length)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);//spiCSNlow();
	spiReadWrite(address);
	while (length--)
	{
		*values++ = spiReadWrite(0);
	}
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);//spiCSNhigh();
}

uint8_t spiReadWrite(uint8_t tx_message)
{
	uint8_t rx_message = 255;
	HAL_SPI_TransmitReceive(&hspi2, &tx_message, &rx_message, 1,HAL_MAX_DELAY);
	return rx_message;
}


void BMP280_get_calib_values(void)
{
	uint8_t rx_buff[24];
	readMBRegister(BMP280_REG_CALIB, rx_buff, 24);

	dig_T1=(rx_buff[0])+(rx_buff[1]<<8);
	dig_T2=(rx_buff[2])+(rx_buff[3]<<8);
	dig_T3=(rx_buff[4])+(rx_buff[5]<<8);
	dig_P1=(rx_buff[6])+(rx_buff[7]<<8);
	dig_P2=(rx_buff[8])+(rx_buff[9]<<8);
	dig_P3=(rx_buff[10])+(rx_buff[11]<<8);
	dig_P4=(rx_buff[12])+(rx_buff[13]<<8);
	dig_P5=(rx_buff[14])+(rx_buff[15]<<8);
	dig_P6=(rx_buff[16])+(rx_buff[17]<<8);
	dig_P7=(rx_buff[18])+(rx_buff[19]<<8);
	dig_P8=(rx_buff[20])+(rx_buff[21]<<8);
	dig_P9=(rx_buff[22])+(rx_buff[23]<<8);

}

void BMP280_init()
{
	writeRegister( 0xF5,  0b10010000);
	writeRegister( 0xF4,  0b01010111);

	BMP280_get_calib_values();
}

struct reading BMP280_measure()
{
	read_value read_value_bmp280;
	uint8_t data[6];
	readMBRegister(BMP280_REG_DATA, data, 6);

	int32_t adc_P = data[0] << 12 | data[1] << 4 | data[2] >> 4;
	int32_t adc_T = data[3] << 12 | data[4] << 4 | data[5] >> 4;

	temperature = (float) compensate_temperature(adc_T) / 100.0;
	pressure = (float) compensate_pressure(adc_P) / 256.0;

	if (p_reference > 0)
	{
		altitude = (1.0 - pow(pressure / p_reference, 0.1903)) * 4433076.0;
	}
	/******************************Displaying Temperature and Pressure*****************************/
	/*char buf1[10],buf2[10];

	HAL_Delay(500);
	HD44780_SetCursor(0,0);
	gcvt(temperature, 10, buf1);
	HD44780_Clear();					//converting float to string

	HD44780_PrintStr(buf1);			//print temperature values to LCD
	HAL_Delay(500);
	HD44780_SetCursor(0,1);
	gcvt(pressure/4, 10, buf2);

	HD44780_PrintStr(buf2);	*/	//print pressure values to LCD
	/**********************************************************************************************/
	/******************************Returing Values in a Structure**********************************/
	read_value_bmp280.temp=temperature;
	read_value_bmp280.press=pressure;
	read_value_bmp280.alti=altitude;

	return read_value_bmp280;
}

int32_t compensate_temperature(int32_t uncomp_temp)
{
	int32_t var1, var2;
	var1 = ((((uncomp_temp / 8)- ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) / 2048;
	var2 = (((((uncomp_temp / 16) - ((int32_t)dig_T1)) * ((uncomp_temp / 16) - ((int32_t)dig_T1))) / 4096) * ((int32_t)dig_T3)) / 16384;
	t_fine = var1 + var2;
	return (t_fine * 5 + 128) / 256;
}

uint32_t compensate_pressure(int32_t uncomp_pres)
{
	int64_t var1, var2, p;

	var1 = ((int64_t) (t_fine)) - 128000;
	var2 = var1 * var1 * (int64_t)dig_P6;
	var2 = var2 + ((var1 * (int64_t)dig_P5) * 131072);
	var2 = var2 + (((int64_t)dig_P4) * 34359738368);
	var1 = ((var1 * var1 * (int64_t)dig_P3) / 256) + ((var1 * (int64_t)dig_P2) * 4096);
	var1 = ((INT64_C(0x800000000000) + var1) * ((int64_t)dig_P1)) / 8589934592;
	if (var1 == 0)
	{
		return 0;
	}
	p = 1048576 - uncomp_pres;
	p = (((((p * 2147483648U)) - var2) * 3125) / var1);
	var1 = (((int64_t)dig_P9) * (p / 8192) * (p / 8192)) / 33554432;
	var2 = (((int64_t)dig_P8) * p) / 524288;
	p = ((p + var1 + var2) / 256) + (((int64_t)dig_P7) * 16);
	return (uint32_t) p;
}
