# Automatic-Environmental-Control-Device



Mini Project-Selec Controls Pvt. Ltd. 




Report 









Automatic Environment Control Device


Submitted by:
Vivek kaushik
Shri Ramdeobaba College of Engineering and Management Nagpur
Content

 
1.	Project details ---------------------------------------------------------------------1
(– Problem Statement / Objectives / Expectations / Working principle)
2.	Design consideration containing------------------------------------------------2
 a. Block diagram -----------------------------------------------------------------2
a.	Selection criteria -------------------------------------------------------------2
b.	Calculation for components ------------------------------------------------7
c.	Firmware consideration  ----------------------------------------------------7
d.	Firmware block diagram / Flow chart ------------------------------------8
e.	Test plan  --------------------------------------------------------------------10
3.	Component values and part number ------------------------------------------11
4.	Circuit simulation ---------------------------------------------------------------12
5.	Simulation results ---------------------------------------------------------------12
6.	Test Reports ----------------------------------------------------------------------14
7.	Conclusion------------------------------------------------------------------------14














1.	Project details: -

•	Project Title: -Automatic Environment Control device
•	Problem Statement: - To develop an Industrial automation device which will operate certain functionalities based on the various Environmental parameters (Temperature, Pressure and Humidity level) of a Container/Room.

•	Project Objectives: - 
i.	Sense the Temperature, Humidity and Pressure from BMP280 and DHT11 sensor.
ii.	Take measure to control the Environmental parameter if the value crosses a certain limit.
iii.	Provide a functionality to user to change the Threshold values of Environmental parameters through a switch.
iv.	Display the Sensed value of temperature, Humidity, pressure.  

Working: - The Automatic environmental control device work on the principle of acquisition of sensory data from the environment and process them, based on set threshold by the user the various environmental control measures can be taken to control the environmental parameters up to the desired limit. On booting up of the device the 16x2  LCD display welcome message after this  BMP280 temperature and pressure sensor and DHT11digital  humidity and temperature sensor start sensing the various environmental parameter , STM32f103C8t6 based microcontroller communicate with the  sensors through different Communication protocols like SPI with BMP 280 and digital read for DHT 11 sensor based on the set algorithm the raw values of the sensors are converted into useful data and simultaneously the process data is displayed on the 16x2 LCD display which is using I2C  protocol for communication with the microcontroller. Sensors are directly been powered from microcontroller which is been powered by a 9 volt battery,  the user also get three switches which are used to generate interrupt the first switch is a menu switch the second switch increment the threshold and the third switch is to decrement the threshold when the user press the menu button the program enter into a menu program based on the number of times user press the menu button the functionality changes, if the user presses button once temperature threshold update menu open while for two pressure update menu and for three Humidity threshold update menu. If the user presses five times the program returns back to the Main program where the continuous measurement of the environmental parameter is taking. 
If a particular parameter viz. temperature, pressure or humidity exceeds the set threshold value, a trigger to the   relay circuitry is generated which is separated by an opto-isolator. Relay circuitry operates the environmental control measures, for example if temperature of a room increases above a set threshold value the air conditioner or a fan can be operated similarly if Humidity exceeds a certain limit dry air can be pumped in and if pressure is increased above a certain limit the Chamber can be pressurized or de-pressurized based on the requirement.
	2. Design consideration containing
	
a.	 Block diagram 

General Device Block diagram

b.	Selection criteria 
The various components are selected based on the required functionality, easy availability, cost and pression up to which the sensor can provide the output, below is the detailed selection criterion and the available alternatives in the market. 

1.	Microcontroller: - STM32f103c8t6 is used in the project to collect the sensory inputs from BMP280 and DHT11 sensor which work on SPI and digital input interfaces, while and 16X2 LCD with an I2C extender is used which uses I2C protocol for communication.
Blue pill provides SPI, I2C ports and digital I/O pins and Timers with 64KB Flash and 20KB of SRAM which satisfied the need for the application with minimum wastage of resources.
Available alternatives: - A range of Microcontrollers board by STM32, PIC, Arduino, Espressif, Raspberry pi are available. The closest alternative was the STM32f103c6t6 board but due to only 32Kbytes of Flash available the board was not capable to handle the Firmware.
2.	Sensor: - The sensors used in the project are Temperature, Humidity and Pressure sensor.

i.	Temperature -BMP280 sensor by Bosch is used which is a Barometric pressure and temperature measurement sensor. DHT11 sensor used in the project is also capable to measure temperature but BMP280’s measurements are more preferred due to its high accuracy.
Features used for selection: 
i.	Small size,
ii.	Low power requirement, 
iii.	Support of SPI communication port, 
iv.	Had high accuracy of ±0.12 hPa (typical) equivalent to ±1 m
v.	Resolution of data Pressure: 0.01 hPa (< 10 cm)
vi.	Operation range of Pressure: 300...1100 hPa
vii.	Average measurement time 5.5   msec

ii.	BMP280 sensor by Bosch is used which is a Barometric pressure and pressure measurement sensor.
Features used for selection: 
i.	Small size,
ii.	Low power requirement, 
iii.	Support of SPI communication port, 
iv.	Had high accuracy between 0 to 50 ° C
v.	Resolution of data Temperature: 0.01° C
vi.	Operation range of Temperature: -40…85°C
vii.	Average measurement time 5.5   msec

iii.	DHT11 sensor which is a digital Humidity and temperature sensor is used to measure the humidity levels in percentage. 
Features used for selection: 
i.	Operating Voltage: 3.5V to 5.5V
ii.	Operating current: 0.3mA (measuring) 60uA (standby)
iii.	Output: Serial data
iv.	Temperature Range: 0°C to 50°C
v.	Humidity Range: 20% to 90%
vi.	Resolution: Temperature and Humidity both are 16-bit
vii.	Accuracy: ±1°C and ±1%
3.	LCD: - A generic 16X2 LCD display is selected to display the measured sensor readings, in addition to it an LCD I2C extender is use to reduce the number of pins used to control the LCD. 
Features used for selection: 

i.	The operating voltage of this LCD is 4.7V-5.3V
ii.	It includes two rows where each row can produce 16-characters.
iii.	The utilization of current is 1mA with no backlight
iv.	Every character can be built with a 5×8-pixel box.

4.	5V Relay and circuitry: - A generic 5V relay which can be triggered from microcontroller and can operate small appliances which can work on up to 240V Ac with maximum 10A of current.
Features used for selection: 
i.	Normal Voltage is 5V DC
ii.	Normal Current is 70mA
iii.	AC load current Max is 10A at 250VAC or 120V AC
iv.	It includes 5-pins & designed with plastic material
v.	Operating time is 10msec
vi.	Release time is 5msec
vii.	Maximum switching is 300 operating per minute

S no.	Component	Requirement	Selected Component
1.	Microcontroller	1 SPI port, 1 I2C port and 1 Timer with 5 digital I/O pins  	Stm32f103c8t6
2.	Temperature Sensor 	Sensor able to provide Temperature reading in range of (-10 to 50)	BMP280
3.	Humidity Sensor	Sensor able to provide Humidity reading with 5% accuracy	ADA386
4.	Pressure Sensor	Sensor able to provide Pressure reading 	BMP280
5.	16X2 LCD with I2C Extender	A screen for displaying the reading.	JHD162A + PCF8574
sc6.	Relay	Able to handle heating, cooling and compression generating devices	SRD-05VDC-SL-C
7.	NPN transistor 	To facilitate in operating relay.	BC547
8.	Resistors	To resist current 	Generic
9.	Optocoupler 	To isolate relay circuitry from microcontroller and sensors, so as to protect microcontroller from rebooting. 	EL817
10.	3 Pin terminal connectors	To facilitate connect AC appliances.	KF301

11.	IC7805	To provide a regulated 5V power supply.	IC7805
12.	Push button	To provide user control facilities.	1825910-2   
13.	9V Battery	To provide power to microcontroller and sensors.	generic
14.	DC jack 	For connecting power sources to the board.	PJ-002AH
15.	Led	To indicate relay operation.	TLHG4405
16.	Freewheeling Diode	To facilitate relay circuitry.	1N4007
17.	Bug strip	To mount microcontroller.	generic
18.	Copper Clad PCB Board	To make a PCB board.	generic


c.	Calculation for components 

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
d.	 Firmware consideration: - 

i.	Platform for code writing.
ii.	Code compilation 
iii.	Debugging feature,
iv.	Support from the company for stm32 microcontroller
v.	User interface 
vi.	Error handling
During the firmware consideration stage STMcubeIDE is used to write code in C language separate libraries are created for each functionality viz. BMP 280 sensor DHT11 sensors to display on LCD for writing the code for menu program and for debugging purpose. 
Input/Output configuration generated by the STMcubeIDE is used as well as the HAL APIs were also used to build the code for the project, references from GitHub are also taken to develop desired functionalities.
e.	Firmware block diagram / Flow chart 



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
During integration testing I integrated DHT 11 sensor, BMP280 sensor, LCD i2c display and relay circuit, for integration I use the previously built libraries and called the various functions based on the requirement of functionalities. To solve the problem of diversion of current from microcontroller to relay and to stop the microcontroller from restarting while triggering the relay I used opto-coupler to isolate the relay circuitry and the microcontroller, sensor and LCD circuitry. During the testing device was accessed on the parameter of their accuracy, the sensor was providing viz DHT11 and BMP 280 and simultaneously displaying the results on the LCD display, the menu program was also tested during this integration menu button was pressed an interrupt was triggered and the program shift from the main program to the menu program and various threshold were able to be changed.
Due to not able to generate non-blocking delay the previous functionality of 15 second timer based returning from the menu program to the main program was discarded and a functionality of pressing the menu button 5 times is used to come out from the menu program come out to the main program.
3. Component values and part number 

S no.	Component	Part no	Value	Quantity
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
15.		Led	TLHG4405	NA	3
16.		Freewheeling Diode	1N4007	NA	3
17.		Bug strip	generic	NA	2

5.	Circuit Simulation and results 

The simulation of Relay circuitry and the power regulator circuitry is simulated on Ni Multisim tool where, the current voltages at different points are accessed virtually and working of relay circuitry is observed with switch operations from an isolated circuitry.

 
Simulation of hardware circuit during its testing and accessing the parameter values, shown above is the reading of DHT11 sensor and sensed Humidity is 33.53 %.

 

Simulation of hardware circuit during its testing and accessing the parameter values, shown above is the reading of BMP280 sensor and sensed pressure value is 976.94 hpa.

 

Simulation of hardware circuit during its testing and accessing the parameter values, shown above is the reading of BMP280 sensor and sensed Temperature value is 32.89-degree Celsius. The set Temperature threshold was 31 degrees, so the triggered relay circuit can be seen in the image.

6.	Test Reports 
After performing various hardware tests and simulation the firmware optimisation and system reliability was accesses and following points are noted based on the observations and findings: -
i.	The system was able to collect temperature and pressure data from BMP280 sensor, which was found to be very closed to the actual values. The pressure reading was able to be collected with an accuracy of 96.2%.  and temperature reading with difference of ±1.5% (empirically).
ii.	The measurement values from DHT11 sensor were observed and found to be stable in low turbulent space, in turbulent space the sensor take time to stabilize to a value, the accuracy of the sensor was found to be ±5to8 %.
iii.	The relay circuitry was found to source current during triggering the transistor with a pin of microcontroller, to solve this problem an opto-isolated circuitry with two power supply is used in the device.
7.	Conclusion
The device works well in compact spaces with less turbulent air, shows all the functionalities of measuring temperature, pressure and humidity and can trigger to control environmental parameters. The device is recommended to be used in cold storage applications, weather monitoring applications, HVAC application, refrigeration applications etc. 
