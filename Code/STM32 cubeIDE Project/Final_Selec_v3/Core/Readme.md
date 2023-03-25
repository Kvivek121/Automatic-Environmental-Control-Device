Selec Controls Mini Project

	1.	Project details: -

•	Project Title: -Automatic Environment Control device
•	Problem Statement: - To develop an Industrial automation device which will operate certain functionalities based on the various Environmental parameters (Temperature, Pressure and Humidity level) of a Container/Room.
•	Project Objectives: - 

i.	Sense the Temperature, Humidity and Pressure from BMP280 and DHT11 sensor.
ii.	Take measure to control the Environmental parameter if the value crosses a certain limit.
iii.	Provide a functionality to user to change the Threshold values of Environmental parameters through a switch.
iv.	Display the Sensed value of temperature, Humidity, pressure.  
 
	2. Design consideration containing
	
		a.	 Block diagram 

![Alt text](C:\Users\acer\STM32CubeIDE\workspace_1.10.2\Final_Selec_v3\Core\s1.jpg?raw=true "Title")




General Device Block diagram


		b.	Calculation for components 

			i.	Voltage Regulation 
			In the project I have used IC 7805 for voltage regulation, there are two different circuitries which are electrically isolated from each other one is using a 9-volt battery to operate and another is using a 12-volt adaptor to operate. Circuitry consisting of relay is using an adaptor rating 12-volt 1.5 ampere and IC7805 is converting it into 5 volts, the microcontroller circuitry consisting of the sensors, the LCD screen user control switches is been operated by a 9-volt battery IC7805 is converting the 9 volts into 5 volts.
			Adapter Rating 12V ,1.5A
			Vin=12V
			Vout= 5V with 1.5A
			(Excess energy will be dissipated in form of heat.)  

			ii.	Relay Circuitry 
			The relay coil resistance =65 ohms
			Supply voltage =5V
			Relay current I = 5/65 = 0.076 or 76 mA.
			Thus, the back EMF current will be much smaller than this. A 1N4007 will be perfectly able to handle this reverse current. PIV of a 1N4007 is 1000 V and the current handling capacity is 1 amp.
				A resistor of 560ohms is used at the base to limit the current to trigger the transistor.
			
			iii.	
		c.	Selection criteria 

![Alt text](C:\Users\acer\STM32CubeIDE\workspace_1.10.2\Final_Selec_v3\Core\s7.png?raw=true "Title")

S no.	Component	Requirement	Selected Component
1.	Microcontroller	1 SPI port, 1 I2C port and 1 Timer with 5 digital I/O pins  	Stm32f103c8t6
2.	Temperature Sensor 	Sensor able to provide Temperature reading in range of (-10 to 50)	BMP280
3.	Humidity Sensor	Sensor able to provide Humidity reading with 5% accuracy	ADA386
4.	Pressure Sensor	Sensor able to provide Pressure reading 	BMP280
5.	16X2 LCD with I2C Extender	A screen for displaying the reading.	JHD162A + PCF8574
6.	Relay	Able to handle heating, cooling and compression generating devices	SRD-05VDC-SL-C
7.	NPN transistor 	To facilitate in operating relay.	BC547
8.	Resistors	To resist current 	Generic
9.	Optocoupler 	To isolate relay circuitry from microcontroller and sensors, so as to protect microcontroller from rebooting. 	EL817
10.	3 Pin terminal connectors	To facilitate connect AC appliances.	KF301

11.	IC7805	To provide a regulated 5V power supply.	IC7805
12.	Push button	To provide user control facilities.	1825910-2   
13.	9V Battery	To provide power to microcontroller and sensors.	generic
14.	DC jack 	For connecting power sources to the board.	PJ-002AH
15.	Led	To indicate relay operation.	
16.	Freewheeling Diode	To facilitate relay circuitry.	1N4007
17.	Bug strip	To mount microcontroller.	generic
18.	Copper Clad PCB Board	To make a PCB board.	generic


The various components are selected based on the required functionality, easy availability, cost and pression up to which the sensor can provide the output, below is the detailed selection criterion and the available alternatives in the market. 

1.	Microcontroller: - STM32f103c8t6 is used in the project to collect the sensory inputs from BMP280 and DHT11 sensor which work on SPI and digital input interfaces, while and 16X2 LCD with an I2C extender is used which uses I2C protocol for communication.
Blue pill provides SPI, I2C ports and digital I/O pins and Timers with 64KB Flash and 20KB of SRAM which satisfied the need for the application with minimum wastage of resources.
Available alternatives: - A range of Microcontrollers board by STM32, PIC, Arduino, Espressif, Raspberry pi are available. The closest alternative was the STM32f103c6t6 board but due to only 32Kbytes of Flash available the board was not capable to handle the Firmware.

2.	Sensor: - The sensors used in the project are Temperature, Humidity and Pressure sensor.
i.	Temperature -BMP280 sensor by Bosch is used which is a Barometric pressure and temperature measurement sensor. DHT11 sensor used in the project is also capable to measure temperature but BMP280’s measurements are more preferred due to its high accuracy.
ii.	BMP280 sensor by Bosch is used which is a Barometric pressure and pressure measurement sensor.
iii.	DHT11 sensor which is a digital Humidity and temperature sensor is used to measure the humidity levels in percentage. 

3.	LCD: - A generic 16X2 LCD display is selected to display the measured sensor readings, in addition to it an LCD I2C extender is use to reduce the number of pins used to control the LCD. 
4.	5V Relay and circuitry: - A generic 5V relay which can be triggered from microcontroller and can operate small appliances which can work on up to 240V Ac with maximum 10A of current.

d.	 Firmware consideration: - 
During the firmware consideration stage STMcubeIDE is used to write code in C language separate libraries are created for each functionality viz. BMP 280 sensor dht 11 sensors to display on LCD for writing the code for menu program and for debugging purpose.


		e.	Firmware block diagram / Flow chart 

![Alt text](C:\Users\acer\STM32CubeIDE\workspace_1.10.2\Final_Selec_v3\Core\s4.png?raw=true "Title")

		f.	Test plan: -

i.	Unit testing 

S no.	Unit tests	Functionalities tested 	Remark
1.		BMP280 sensor 	Data acquisition on SPI 	Successfully able to communicate with sensor and able to read/ write its registers.
2.		BMP280 sensor	Tested the algorithm for conversion of Raw sensor data into useful values.	Used burst read to reduce the mismatch on register data and resist there overwriting 
3.		DHT11 sensor	Timer and microsecond delay generation for communication with sensor. 	Successfully able to generate the delay and communicate with sensor.
4.		LCD I2C 	Communicate with LCD I2C extender to be able to display on LCD	Used references and able to display on LCD
5.		Relay circuit	Able to trigger relay gpio of Microcontroller	Faced problem of restarting of Microcontroller when relay gets triggered due to diversion of current to coil, used opto coupler to create isolated circuitry to solve problem.
6.		Interfacing tactile push button	Able to create functionalities through push buttons	Used Interrupt to develop the functionalities. 

ii.	Integration testing
During integration testing I integrated DHT 11 sensor, BMP280 sensor, LCD i2c display and relay circuit, for integration I use the previously built libraries and called the various functions based on the requirement of functionalities. To solve the problem of diversion of current from microcontroller to relay and to stop the microcontroller from restarting while triggering the relay I used opto-coupler to isolate the relay circuitry and the microcontroller, sensor and LCD circuitry. During the testing device was accessed on the parameter of their accuracy, the sensor was providing viz DHT11 and BMP 280 and simultaneously displaying the results on the LCD display, the menu program was also tested during this integration menu button was pressed an interrupt was triggered and the program shift from the main program to the menu program and various threshold were able to be changed. Due to not able to generate non-blocking delay the previous functionality of 15 second timer based returning from the menu program to the main program was discarded and a functionality of pressing the menu button 5 times is used to come out from the menu program come out to the main program.
iii.	Field testing

	3. Component values and part number 

S no.	Component	Part no	Value	Quantity	Cost
1.		Microcontroller	Stm32f103c8t6	NA	1	
2.		BMP280	BMP280	NA	1	
3.		DHT11	ADA386	NA	1	
4.		16x2 LCD 	JHD162A
	NA	1	
5.		I2C Extender	PCF8574	NA	1	
6.		Relay	SRD-05VDC-SL-C		3	
7.		NPN transistor 	BC547	NA	3	
8.		Resistors	Generic	3- 100ohms,
3-220ohms,
3-560 ohms.	9	
9.		Optocoupler 	EL817	NA	3	
10.		3 Pin terminal connectors	KF301
	NA	3	
11.		Voltage Regulator 	IC7805	NA	2	
12.		Tactile Push button	1825910-2   	NA	3	
13.		9V Battery	generic	9V	1	
14.		DC jack 	PJ-002AH	NA	2	
15.		Led		NA		
16.		Freewheeling Diode	1N4007	NA	3	
17.		Bug strip	generic	NA	2	
18.		Copper Clad PCB Board	generic	NA	1	

	5.	Circuit and Schematic  

![Alt text](C:\Users\acer\STM32CubeIDE\workspace_1.10.2\Final_Selec_v3\Core\s3.png?raw=true "Title")

![Alt text](C:\Users\acer\STM32CubeIDE\workspace_1.10.2\Final_Selec_v3\Core\s5.jpg?raw=true "Title")![Alt text](C:\Users\acer\STM32CubeIDE\workspace_1.10.2\Final_Selec_v3\Core\s6.jpg?raw=true "Title")
