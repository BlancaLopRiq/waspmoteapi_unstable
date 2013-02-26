/*
 *  Copyright (C) 2009 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
   
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:		0.13
 *  Design:			David Gascón
 *  Implementation:	Alberto Bielsa, Manuel Calahorra, Yuri Carmona
 */


#ifndef __WPROGRAM_H__
#include <WaspClasses.h>
#endif

#include "WaspSensorAgr_v20.h"

// Constructors ////////////////////////////////////////////////////////////////

/*	Constructor: 	Sets the mode of the digital pins and initializes them
 * 
 */
WaspSensorAgr_v20::WaspSensorAgr_v20()
{
	pinMode(LOW_BAT_MON, INPUT);
	digitalWrite(LOW_BAT_MON, HIGH);
	
	pinMode(DIGITAL8,OUTPUT);
	pinMode(DIGITAL7,OUTPUT);
	pinMode(DIGITAL6,OUTPUT);
	pinMode(DIGITAL5,OUTPUT);
	pinMode(DIGITAL4,INPUT);
	pinMode(DIGITAL3,OUTPUT);
	pinMode(DIGITAL2,INPUT);	
	pinMode(DIGITAL1,OUTPUT);	
	pinMode(ANA0,OUTPUT);
	pinMode(SENS_PW_3V3,OUTPUT);
	pinMode(SENS_PW_5V,OUTPUT);
	pinMode(15, INPUT);
	pinMode(17, INPUT);
	pinMode(19, INPUT);
	
	digitalWrite(DIGITAL8,LOW);
	digitalWrite(DIGITAL7,LOW);
	digitalWrite(DIGITAL6,LOW);
	digitalWrite(DIGITAL5,LOW);
	digitalWrite(DIGITAL3,LOW);
	digitalWrite(DIGITAL1,LOW);
	digitalWrite(ANA0,LOW);
	digitalWrite(SENS_PW_3V3,LOW);
	digitalWrite(SENS_PW_5V,LOW);
}

// Public Methods //////////////////////////////////////////////////////////////

/*	ON: Calls the setBoardMode function to turn on the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorAgr_v20::ON(void)
{
	setBoardMode(SENS_ON);
}

/*	OFF: Calls the setBoardMode function to turn off the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorAgr_v20::OFF(void)
{
	setBoardMode(SENS_OFF);
}

/*	setBoardMode: Sets the board mode indicated
 *	Parameters:	uint8_t mode 
 * 						- SENS_ON : turn on the board
 * 						- SENS_OFF : turn off the board
 *  Return:		uint8_t error
 * 						- 1 : success / no error detected
 * 						- 0 : wrong mode introduced
 */
int8_t	WaspSensorAgr_v20::setBoardMode(uint8_t mode)
{
	
	switch( mode )
	{
		case	SENS_ON :	digitalWrite(SENS_PW_3V3,HIGH);
							digitalWrite(SENS_PW_5V,HIGH);
							// Sets RTC on to enable I2C
							if(!RTC.isON) RTC.setMode(RTC_ON, RTC_I2C_MODE);
							digitalWrite(DIGITAL5,HIGH);
							break;
		case	SENS_OFF:	digitalWrite(SENS_PW_3V3,LOW);
							digitalWrite(SENS_PW_5V,LOW);
							digitalWrite(DIGITAL5,LOW);
							break;
		default			:	return 0;
	}
	
	return 1;
}

/*	setSensorMode: It sets ON/OFF the different sensor switches
 *	Parameters:	uint8_t mode 
 * 						- SENS_ON : turn on the sensor
 * 						- SENS_OFF : turn off the sensor
 * 				uint16_t sensor
 * 							- SENS_AGR_PRESSURE : Atmospheric Pressure Sensor
 * 							- SENS_AGR_WATERMARK1 : Soil Moisture 1 Sensor
 * 							- SENS_AGR_WATERMARK2 : Soil Moisture 2 Sensor
 * 							- SENS_AGR_WATERMARK3 : Soil Moisture 3 Sensor
 * 							- SENS_AGR_ANEMOMETER : Weather Station Sensor
 * 							- SENS_AGR_VANE : Weather Station Sensor
 * 							- SENS_AGR_DENDROMETER : Trunk diameter Sensor
 *	 						- SENS_AGR_PT100 : Soil temperature Sensor
 * 							- SENS_AGR_LEAF_WETNESS : Leaf wetness Sensor
 * 							- SENS_AGR_TEMPERATURE : Temperature Sensor
 * 							- SENS_AGR_HUMIDITY : Humidity Sensor
 * 							- SENS_AGR_RADIATION : Solar radiation Sensor
 * 							- SENS_AGR_SENSIRION : Humidity and temperature Sensor
 * 							- SENS_AGR_LDR : Luminosity Sensor
 *  Return:		int8_t error
 * 						1 : success
 * 						0 : wrong mode selected
 * 						-1: wrong sensor selected
 * 
 */
int8_t	WaspSensorAgr_v20::setSensorMode(uint8_t mode, uint16_t sensor)
{	
	if( mode==SENS_ON )
	{
		switch( sensor )
		{
			case	SENS_AGR_PRESSURE	:	digitalWrite(SENS_SWITCH_1,HIGH);
											break;
			case	SENS_AGR_WATERMARK_1:	digitalWrite(SENS_SWITCH_2,HIGH);
											break;
			case	SENS_AGR_WATERMARK_2:	digitalWrite(SENS_SWITCH_2,HIGH);
											break;
			case	SENS_AGR_WATERMARK_3:	digitalWrite(SENS_SWITCH_2,HIGH);
											break;				
			case	SENS_AGR_ANEMOMETER	:	digitalWrite(SENS_SWITCH_3,HIGH);
											break;
			case	SENS_AGR_VANE		:	digitalWrite(SENS_SWITCH_3,HIGH);
											break;
			case	SENS_AGR_DENDROMETER:	digitalWrite(SENS_SWITCH_4,HIGH);
											break;
			case	SENS_AGR_PT1000		:	digitalWrite(SENS_SWITCH_4,HIGH);
											break;
			case	SENS_AGR_LEAF_WETNESS:	digitalWrite(SENS_SWITCH_4,HIGH);
											digitalWrite(SENS_MUX_SEL,HIGH);
											break;
			case	SENS_AGR_TEMPERATURE:	digitalWrite(SENS_SWITCH_4,HIGH);
											digitalWrite(SENS_MUX_SEL,HIGH);
											break;
			case	SENS_AGR_HUMIDITY	:	digitalWrite(SENS_SWITCH_4,HIGH);
											digitalWrite(SENS_MUX_SEL,HIGH);
											break;
			case	SENS_AGR_RADIATION	:	digitalWrite(SENS_SWITCH_4,HIGH);
											break;
			case	SENS_AGR_SENSIRION	:	digitalWrite(SENS_SWITCH_4,HIGH);
											break;
			case	SENS_AGR_LDR		:	digitalWrite(SENS_SWITCH_4,HIGH);
											break;
			default						:	return -1;
		}
	} else if( mode==SENS_OFF )
	{
		switch( sensor )
		{
			case	SENS_AGR_PRESSURE	:	digitalWrite(SENS_SWITCH_1,LOW);
											break;
			case	SENS_AGR_WATERMARK_1:	digitalWrite(SENS_SWITCH_2,LOW);
											break;
			case	SENS_AGR_WATERMARK_2:	digitalWrite(SENS_SWITCH_2,LOW);
											break;
			case	SENS_AGR_WATERMARK_3:	digitalWrite(SENS_SWITCH_2,LOW);
											break;				
			case	SENS_AGR_ANEMOMETER	:	digitalWrite(SENS_SWITCH_3,LOW);
											break;
			case	SENS_AGR_VANE		:	digitalWrite(SENS_SWITCH_3,LOW);
											break;
			case	SENS_AGR_DENDROMETER:	digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_PT1000		:	digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_LEAF_WETNESS:	digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_TEMPERATURE:	digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_HUMIDITY	:	digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_RADIATION:		digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_SENSIRION:		digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_LDR:			digitalWrite(SENS_SWITCH_4,LOW);
											break;
			default						:	return -1;
		}
	} else return 0;
	
	return 1;
}

/*	readValue: Calls the readValue function with no type specified
 *	Parameters:	uint16_t sensor
 * 							- SENS_AGR_PRESSURE : Atmospheric Pressure Sensor
 * 							- SENS_AGR_WATERMARK1 : Soil Moisture 1 Sensor
 * 							- SENS_AGR_WATERMARK2 : Soil Moisture 2 Sensor
 * 							- SENS_AGR_WATERMARK3 : Soil Moisture 3 Sensor
 * 							- SENS_AGR_ANEMOMETER : Anemometer Sensor
 * 							- SENS_AGR_VANE : Vane Sensor
 * 							- SENS_AGR_PLUVIOMETER : Pluviometer Sensor
 * 							- SENS_AGR_DENDROMETER : Trunk diameter Sensor
 *	 						- SENS_AGR_PT100 : Soil temperature Sensor
 * 							- SENS_AGR_LEAF_WETNESS : Leaf wetness Sensor
 * 							- SENS_AGR_TEMPERATURE : Temperature Sensor
 * 							- SENS_AGR_HUMIDITY : Humidity Sensor
 * 							- SENS_AGR_RADIATION : Solar radiation Sensor
 * 							- SENS_AGR_LDR : Luminosity Sensor
 *  Return:		float value : value read from the sensor
 * 
 */
float	WaspSensorAgr_v20::readValue(uint16_t sensor)
{
	return readValue(sensor,0);
}

/*	readValue: Reads the analog to digital converter input indicated of the given
 * 			   sensor socket and converts the value into the proper units
 *	Parameters:	uint16_t sensor
 * 							- SENS_AGR_PRESSURE : Atmospheric Pressure Sensor
 * 							- SENS_AGR_WATERMARK1 : Soil Moisture 1 Sensor
 * 							- SENS_AGR_WATERMARK2 : Soil Moisture 2 Sensor
 * 							- SENS_AGR_WATERMARK3 : Soil Moisture 3 Sensor
 * 							- SENS_AGR_ANEMOMETER : Anemometer Sensor
 * 							- SENS_AGR_VANE : Vane Sensor
 * 							- SENS_AGR_PLUVIOMETER : Pluviometer Sensor
 * 							- SENS_AGR_DENDROMETER : Trunk diameter Sensor
 *	 						- SENS_AGR_PT100 : Soil temperature Sensor
 * 							- SENS_AGR_LEAF_WETNESS : Leaf wetness Sensor
 * 							- SENS_AGR_TEMPERATURE : Temperature Sensor
 * 							- SENS_AGR_HUMIDITY : Humidity Sensor
 * 							- SENS_AGR_RADIATION : Solar radiation Sensor
 * 							- SENS_AGR_SENSIRION : Humidity and temperature Sensor
 * 							- SENS_AGR_LDR : Luminosity Sensor
 *  Return:		float value : value read from the sensor
 * 
 */
float	WaspSensorAgr_v20::readValue(uint16_t sensor, uint8_t type)
{
	float aux=0;
	uint16_t aux2=0;
 	
	switch( sensor )
	{
		case	SENS_AGR_PRESSURE	:	aux2=analogRead(ANALOG3);
										aux=pressureConversion(aux2); // KPa
										break;
		case	SENS_AGR_WATERMARK_1:	digitalWrite(SENS_MUX_SEL,LOW);
										aux=readWatermark(SENS_AGR_WATERMARK_1);
										// 50Hz - 200cbar || 10KHz - 0cbar
										digitalWrite(SENS_MUX_SEL,HIGH);
										break;
		case	SENS_AGR_WATERMARK_2:	digitalWrite(SENS_MUX_SEL,LOW);
										aux=readWatermark(SENS_AGR_WATERMARK_2);
										// 50Hz - 200cbar || 10KHz - 0cbar
										digitalWrite(SENS_MUX_SEL,HIGH);
										break;
		case	SENS_AGR_WATERMARK_3:	digitalWrite(SENS_MUX_SEL,LOW);
										aux=readWatermark(SENS_AGR_WATERMARK_3);
										// 50Hz - 200cbar || 10KHz - 0cbar
										digitalWrite(SENS_MUX_SEL,HIGH);
										break;
		case	SENS_AGR_ANEMOMETER	:	aux=readAnemometer();
										break;
		case	SENS_AGR_VANE		:	aux2=analogRead(ANALOG5);
										aux=(aux2*3.3)/1023; // Volts
										getVaneDirection(aux); // Direction
										break;
		case	SENS_AGR_DENDROMETER:	aux=readDendrometer(); //mm
										break;
		case	SENS_AGR_PT1000		:	aux=readPT1000(); // º Celsius
										break;
		case	SENS_AGR_LEAF_WETNESS:	aux2=analogRead(ANALOG6);
										aux= 100-(float(aux2)*100/1023);
										break;
		case	SENS_AGR_TEMPERATURE:	aux2=analogRead(ANALOG4);
										aux=mcpConversion(aux2); // ºCelsius
										break;
		case	SENS_AGR_HUMIDITY	:	aux2=analogRead(ANALOG2);
										aux=senceraConversion(aux2); // %Hum
										break;
		case	SENS_AGR_RADIATION	:	aux=readRadiation(); //Volts
										break;
		case	SENS_AGR_SENSIRION	:	if( type==SENSIRION_TEMP )
										{
											aux=readSensirion(SENSIRION_TEMP); 
											// ºCelsius
										} else if( type==SENSIRION_HUM )
										{
											aux=readSensirion(SENSIRION_HUM);
											// %Hum
										}
										break;
		case	SENS_AGR_PLUVIOMETER:	aux2=readPluviometer();
										aux=float(aux2) * 0.2794 * 20; // mm/min
										break;	
		case	SENS_AGR_LDR		:	aux2=analogRead(ANALOG7);
										aux=float(aux2*3.3) / 1023;
										break;	
		default						:	;
	}
	
	return	aux;
}


/*  attacPluvioInt: It attaches the pluviometer interruptions
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorAgr_v20::attachPluvioInt(void) 
{
		enableInterrupts(PLV_INT | HAI_INT);
}


/*  detachPluvioInt: It detaches the pluviometer interruptions
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorAgr_v20::detachPluvioInt(void) 
{
	disableInterrupts(PLV_INT | HAI_INT);
}

/*  sleepAgr: Calls the sleepAgr without agriculture interruptions
 *	Parameters:	const char*	time2wake
 * 				uint8_t offset
 * 				uint8_t mode
 * 				uint8_t option
 * 
 * 				See deepSleep function in PWR library			
 * 
 *  Return:		void
 * 
 */
void	WaspSensorAgr_v20::sleepAgr(const char*	time2wake,
									uint8_t offset,
									uint8_t mode,
									uint8_t option)
{
	sleepAgr(time2wake, offset, mode, option, 0);
}

/*  sleepAgr: sleep function to turn off the sensors without disabling the board
 *	Parameters:	const char*	time2wake
 * 				uint8_t offset
 * 				uint8_t mode
 * 				uint8_t option
 * 
 * 				See deepSleep function in PWR library			
 * 
 *  Return:		void
 * 
 */
void	WaspSensorAgr_v20::sleepAgr(const char* time2wake,
									uint8_t offset, 
									uint8_t mode, 
									uint8_t option, 
									uint8_t agr_interrupt)
{
	// Set RTC alarme to wake up from Sleep Power Down Mode
	RTC.ON();
	RTC.setAlarm1(time2wake,offset,mode);
	RTC.close();
	digitalWrite(SENS_SWITCH_1, LOW);
	digitalWrite(SENS_SWITCH_2, LOW);
	digitalWrite(SENS_SWITCH_4, LOW);
	digitalWrite(SENS_MUX_SEL, LOW);
	digitalWrite(SENS_DATA, LOW);
	digitalWrite(SENS_SWITCH_3, LOW);

    Utils.muxOFF();
    RTC.OFF();
        
    pinMode(I2C_SDA,OUTPUT);
	digitalWrite(I2C_SDA,LOW);
	pinMode(I2C_SCL,OUTPUT);
	digitalWrite(I2C_SCL,LOW);    
	
	pinMode(SD_SS,OUTPUT);
    digitalWrite(SD_SS,HIGH);
    
    pinMode(XBEE_MON,INPUT);
	digitalWrite(XBEE_MON,LOW);

	PWR.switchesOFF(option);


	if (agr_interrupt && SENS_AGR_PLUVIOMETER)
	{
		enableInterrupts(PLV_INT | HAI_INT);
	}


	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_mode();
	sleep_disable();
	delay(500);
	PWR.switchesON(option);
	RTC.ON();
	RTC.clearAlarmFlag();
	if( option & RTC_OFF ) RTC.OFF();
	if( option & SENS_OFF )
	{
		pinMode(SENS_PW_3V3,OUTPUT);
		digitalWrite(SENS_PW_3V3,LOW);	
		pinMode(SENS_PW_5V,OUTPUT);
		digitalWrite(SENS_PW_5V,LOW);
	}
}


// Private Methods //////////////////////////////////////////////////////////////

/*	readDendrometer: reads the analog to digital converter input to which is
 * 					 connected the dendrometer through the I2C and converts its
 * 					 value into mm
 *	Parameters: void
 *  Return:	float value : trunk diameter read by the dendrometer in mm
 * 
 */
float WaspSensorAgr_v20::readDendrometer(void)
{
	const byte address_ADC = B0010110;
	const byte dendro_channel = B10100001;
	byte data_dendro[3] = {0,0,0};
	float value_dendro = 0;
	
	if( !Wire.I2C_ON ) Wire.begin();
	delay(100);
	delay(100);
	
	delay(100);
  
	Wire.beginTransmission(B0010110);
	Wire.send(dendro_channel);
	Wire.send(B01010101);
	Wire.endTransmission();

	delay(300);
  
	Wire.requestFrom(B0010110, 3);
  
	int i=0;
	while(Wire.available())
	{
		data_dendro[i]=Wire.receive();
		i++;
	}
	
	if( Wire.I2C_ON && !ACC.isON && RTC.isON!=1){
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
  
	return value_dendro = conversion(data_dendro,0);
}

/*	readAnemometer: reads the number of anemometer pulses during three seconds
 * 					and turns the value into speed (km/h)
 *	Parameters: void
 *  Return:	float value : wind speed (km/h)
 * 
 */
float WaspSensorAgr_v20::readAnemometer(void)
{
	int reading_anemometer = 0;
	int previous_reading_anemometer = 0;
	int value_anemometer = 0;
	float wind_speed = 0;
	unsigned long start_anemometer=0;

	value_anemometer = 0;
	start_anemometer = millis();
	while((millis()-start_anemometer)<=3000)
	{
		previous_reading_anemometer = reading_anemometer;
		reading_anemometer = digitalRead(DIGITAL2);
    
		if((previous_reading_anemometer == 1)&&(reading_anemometer == 0))
		{
			value_anemometer++;
		}
		//avoid millis overflow problem
		if( millis()-start_anemometer < 0 ) start_anemometer=millis(); 
	}
	delay(100);
	
	wind_speed = value_anemometer * 0.8;
  
	return wind_speed;
}

/*	readPT1000: reads the analog to digital converter input to which is connected
 * 				the	PT1000 sensor through the I2C and converts its value into
 * 				temperature (ºC)
 *	Parameters: void
 *  Return:	float value : temperature in Celsius (ºC)
 * 
 */
float WaspSensorAgr_v20::readPT1000(void)
{
	const byte address_ADC = B0010110;
	const byte pt1000_channel = B10100000;
	byte data_pt1000[3] = {0,0,0};
	float value_pt1000 = 0;
	
	if( !Wire.I2C_ON ) Wire.begin();
	delay(100);
	delay(100);
	
	delay(100);

	Wire.beginTransmission(B0010110);
	Wire.send(pt1000_channel);
	Wire.send(B01010101);
	Wire.endTransmission();
  
	delay(300);
  
	Wire.requestFrom(B0010110, 3);

	int k=0;
	while(Wire.available())
	{
		data_pt1000[k]=Wire.receive();
		k++;
	}

	if( Wire.I2C_ON && !ACC.isON && RTC.isON!=1){
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
	return value_pt1000 = conversion(data_pt1000,1);  
}

/*	readRadiation: reads the analog to digital converter to which is connected the
 * 				   solar radiation sensor through the I2C and converts its value
 * 				   into voltage
 *	Parameters: void
 *  Return:	float value : temperature in Celsius (ºC)
 * 
 */
float WaspSensorAgr_v20::readRadiation(void)
{
	const byte address = B0010100;
	byte data_apogee[2] = {0,0};
	long val = 0;
	float val_def = 0;
	
	if( !Wire.I2C_ON ) Wire.begin();
  
	delay(100);
  
	delay(50);
	
	Wire.requestFrom(B0010100, 2);
  
	int i = 0;
	while(Wire.available())
	{
		data_apogee[i] = Wire.receive();
		i++;
	}
  
	if( Wire.I2C_ON && !ACC.isON && RTC.isON!=1){
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
 
	val = long(data_apogee[1]) + long(data_apogee[0])*256;
    
	val_def = (val - 32769)*9;
	return val_def = val_def/65535;
}

/*	readWatermark: reads the frequency of the adaptation circuit of the Watermark
 * 				   sensor indicated in sens
 *	Parameters: uint8_t sens
 * 						- SENS_AGR_WATERMARK_1
 * 						- SENS_AGR_WATERMARK_2
 * 						- SENS_AGR_WATERMARK_3
 *  Return:	float value : watermark circuit frequency
 * 						  -1 if wrong sensor selected
 * 
 */
float WaspSensorAgr_v20::readWatermark(uint8_t sens)
{
	uint8_t pin=0;
	int value_watermark = 0;
	int previous_value_watermark = 0;
	int counter_watermark = 0;
	unsigned long start = 0;
	float freq = 0;
	
	pinMode(15, INPUT);
	pinMode(17, INPUT);
	pinMode(19, INPUT);
    
 	digitalWrite(SENS_MUX_SEL,LOW);
	
	switch( sens )
	{
		case SENS_AGR_WATERMARK_1	:	pin=15;
										break;
		case SENS_AGR_WATERMARK_2	:	pin=19;
										break;
		case SENS_AGR_WATERMARK_3	:	pin=17;
										break;
		default						:	return -1.0;
	}
 	
	counter_watermark = 0;
	start = millis();
	while(counter_watermark < 2000)
	{
		previous_value_watermark = value_watermark;
		value_watermark = digitalRead(pin);
    
		if((previous_value_watermark ==1)&&(value_watermark == 0))
		{
			counter_watermark++;
		}
	}
  
	return freq = 2000000 / float((millis() - start));
}

/*	readSensirion: reads the temperature or humidity value from the Sensirion
 * 				   digital temperature and humidity sensor
 *	Parameters: uint8_t parameter
 * 						- SENSIRION_TEMP
 * 						- SENSIRION_HUM
 *  Return:	float value : temperature (ºC) or humidity (%RH) value
 * 						  out of range values if connection problem
 * 
 */
float WaspSensorAgr_v20::readSensirion(uint8_t parameter)
{
	int ack = 0;
	int val_read = 0;
	int ack2, ack3, i = 0;
	long a = 0;
	long b = 0;
	
	const byte HUMIDITY = B00000101;
	const byte TEMPERATURE = B00000011;
	
	

	if( parameter==SENSIRION_TEMP ) parameter=TEMPERATURE;
	else if( parameter==SENSIRION_HUM ) parameter=HUMIDITY;
		
  //************************************* 
  // First Transmission cycle (START)
  
	pinMode(SENS_DATA,  OUTPUT);
	pinMode(SENS_CLK, OUTPUT);
	digitalWrite(SENS_DATA,  HIGH);
	digitalWrite(SENS_CLK, HIGH);
	delayMicroseconds(1);
	digitalWrite(SENS_DATA,  LOW);
	digitalWrite(SENS_CLK, LOW);
	delayMicroseconds(1);
	digitalWrite(SENS_CLK, HIGH);
	digitalWrite(SENS_DATA,  HIGH);
	delayMicroseconds(1);
	digitalWrite(SENS_CLK, LOW);

  //***************************************
  // Write the command (3 first bits: always 000, last five bits: command)

	//parameter: B00000011 for temperature and B00000101 for humidity
	shiftOut(SENS_DATA, SENS_CLK, MSBFIRST, parameter);  
	digitalWrite(SENS_CLK, HIGH);
	pinMode(SENS_DATA, INPUT);

	a = millis();
	ack = digitalRead(SENS_DATA);
	while((ack == HIGH)&&((millis()-a)<10))
	{
		ack = digitalRead(SENS_DATA);
		if (millis() < a) a = millis();	//to avoid millis overflow
	}

	digitalWrite(SENS_CLK, LOW);

	a = millis();
	ack = digitalRead(SENS_DATA);
	while((ack == LOW)&&((millis()-a)<10))
	{
		ack = digitalRead(SENS_DATA);
		if (millis() < a) a = millis();	//to avoid millis overflow
	}
  
  //****************************************
  //Wait for a complete conversion
  
	ack = digitalRead(SENS_DATA);
	a = millis();
	while((ack == HIGH)&&((millis()-a)<400))
	{
		ack = digitalRead(SENS_DATA);
	}
 
  //*****************************************
  //Read the 8 most significative bits

	a = millis();
	for(int i = 0; i < 8; i++)
	{
		digitalWrite(SENS_CLK, HIGH);
		val_read = (val_read * 2) + digitalRead(SENS_DATA);
		digitalWrite(SENS_CLK, LOW);
	}
  
	ack = digitalRead(SENS_DATA);
	a = millis();
	while((ack == LOW)&&((millis()-a)<10))
	{
		ack = digitalRead(SENS_DATA);
		if (millis() < a) a = millis();	//to avoid millis overflow
	}
  
  //****************************************
  //ACK from the  microcontroller
	pinMode(SENS_DATA, OUTPUT);
	digitalWrite(SENS_DATA, LOW);
	delayMicroseconds(1);
	digitalWrite(SENS_CLK, HIGH);
	delayMicroseconds(400);
	digitalWrite(SENS_CLK, LOW);
	pinMode(SENS_DATA, INPUT);
   
  //***************************************
  //Read the 8 least significative bits
	a = millis();
	for(int i = 0; i < 8; i++)
	{
		digitalWrite(SENS_CLK, HIGH);
		val_read = val_read * 2 + digitalRead(SENS_DATA);
		digitalWrite(SENS_CLK, LOW);
	}
	b = millis()-a;

  
  //**************************************
  //CRC not taken into account
  
	pinMode(SENS_DATA, OUTPUT);
	digitalWrite(SENS_DATA, HIGH);
	digitalWrite(SENS_CLK, HIGH);
	delayMicroseconds(400);
	digitalWrite(SENS_CLK, LOW);
	
	digitalWrite(SENS_DATA, LOW);
  
	if( parameter==TEMPERATURE ) return temperatureConversion(val_read,SENS_PREC_HIGH);
	else if( parameter==HUMIDITY ) return humidityConversion(val_read,SENS_PREC_HIGH);
} 

/*	temperatureConversion: converts the value read from the Sensirion into a
 * 						   temperature value
 *	Parameters:	int readValue : value read from the Sensirion
 * 				int precision : format at which the sensor was read
 *  Return:		float value : temperature measured by the sensor in ºC
 * 
 */
float WaspSensorAgr_v20::temperatureConversion(int readValue, int precision)
{
	float temperature = 0;
	float d1 = -39.7;
	float d2 = 0;
	
	float aux=0;
  
	switch(precision)
	{
		case SENS_PREC_HIGH:    d2 = 0.01;
					temperature = d1 + (d2 * float(readValue));
					break;    
		case SENS_PREC_LOW:     d2 = 0.04;
					temperature = d1 + (d2 * float(readValue));
					break;
	}
  
	return(temperature);
}


/*	humidityConversion: converts the value read from the Sensirion into a
 * 						humidity value
 *	Parameters:	int readValue : value read from the Sensirion
 * 				int precision : format at which the sensor was read
 *  Return:		float value : humidity measured by the sensor in %RH
 *  
 */
float WaspSensorAgr_v20::humidityConversion(int readValue, int precision)
{
	float humidity = 0;
	float c1 = -2.0468;
	float c2 = 0;
	float c3 = 0;
  
	switch(precision)
	{
		case SENS_PREC_HIGH	:	c2 = 0.0367;
								c3 = -1.5955e-6;
								humidity = c1 + (c2 * float(readValue)) 
										   + (c3 * float(readValue) * float(readValue));
								break;

		case SENS_PREC_LOW	:	c2 = 0.5872;
								c3 = -4.0845e-4;
								humidity = c1 + (c2 * float(readValue))
										   + (c3 * float(readValue) * float(readValue));
								break;
		default			  	:	;
	}
  
	//in case of saturation
	if( humidity > 99.0 )
	{
		humidity = 100.0;
	}
	
	return(humidity);
}


/*	readPluviometer: reads the number of anemometer pulses during three seconds
 * 					 and turns the value into mm of rain
 *	Parameters: void
 *  Return:	float value : precipitations (mm)
 * 
 */
uint16_t WaspSensorAgr_v20::readPluviometer()
{
	int reading_pluviometer = 0;
	int previous_reading_pluviometer = 0;
	int value_pluviometer = 0;
	unsigned long start_pluviometer=0;

	value_pluviometer = 0;
	start_pluviometer = millis();
	while((millis()-start_pluviometer)<=3000)
	{
		previous_reading_pluviometer = reading_pluviometer;
		reading_pluviometer = digitalRead(DIGITAL4);
    
		if((previous_reading_pluviometer == 1)&&(reading_pluviometer == 0))
		{
			value_pluviometer++;
		}
		//avoid millis overflow problem
		if( millis()-start_pluviometer < 0 ) start_pluviometer=millis();
	}
	delay(100);
  
	return value_pluviometer;
}

/*	conversion: converts the value read from the PT1000 and dendrometer ADC into
 * 				the units of the sensor
 *	Parameters: byte data_input[3] : three bytes from the ADC conversion
 * 				uint8_t type : 1 for PT1000 reading, 0 for dendrometer reading
 *  Return:	float value : temperature (ºC) or diameter (mm) in function of the sensor
 * 
 */
float WaspSensorAgr_v20::conversion(byte data_input[3], uint8_t type)
{
	long val = 0;
	float val_def = 0;
	int signo = 0;
	int overflow = 0;
	float Vcc = 3.3;
	float R1           = 1005.0; 
	float R2           = 1005.0;
	float R3           = 1005.0;
	float Rx           = 0.0;
	float tempPt       = 0.0;
	float equis        = 0.0;
  
	signo = int(data_input[0] >> 7);
	overflow = int((data_input[0] >> 6)&B00000001);

	val = long((data_input[2] >> 6)&B00000011) + long(data_input[1])*4 
		  + long((data_input[0])&B00111111)*1024;

  
	if (signo == 1)
	{
		if (overflow == 1)
		{
      //OVERFLOW High
			val_def = 2;
		}
		else
		{
			val_def = val*1.5;
			val_def = val_def/65535;
		}
	}
	else
	{
		if (overflow == 0)
		{
      //OVERFLOW LOW
			val_def = -2;
		}
		else
		{
			val_def = -(65535 - val)*1.5;
			val_def = val_def/65535;
		}
	}

	if( type==1 ){
		Rx = (Vcc*R2*R3 + val_def*R3*(R1+R2)) / (Vcc*R1 - val_def*(R1+R2));
		equis = (Rx - 1001.52) / 1351.99;
		Rx = equis * 1494.46 + 996.04;
		tempPt = (Rx-1000)/3.9083;
		return(tempPt);
	}
	else if( type==0) return ( (val_def * 11000)/1000.0 );
}



/*	pressureConversion: converts the value read at the analog to digital
 * 						converter corresponding to the atmospheric pressure
 * 						sensor into a pressure value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : temperature measured by the sensor in kilopascals
 * 
 */float WaspSensorAgr_v20::pressureConversion(int readValue)
{
	float pressure = 0;   
	
	pressure = (float(readValue) * 3300.0 / 1023.0)/0.6; //sensor output (mV)  
	 
	pressure = (((pressure + 270) / 5000) + 0.095 ) / 0.0088; // kPa
   
	return(pressure);
}


/*	lwsConversion: converts the value read at the analog to digital	converter
 * 				   input corresponding to the leaf wetness sensor into a voltage
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : voltage between 0 and 3.3V
 * 
 */
float WaspSensorAgr_v20::lwsConversion(int readValue)
{
	float lws = 0;
   
	lws = float(readValue) * 3.3 / 1023;
   
	return(lws);
   
}
 
/*	getVaneDirection: stores in the vaneDirection variable the orientation of the
 * 					  vane calculated from the voltage read at its output
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		void
 * 
 */
void WaspSensorAgr_v20::getVaneDirection(float vane)
{
	if( vane<0.25 ) vaneDirection=SENS_AGR_VANE_ESE;
	else if( vane>=0.25 && vane<0.28 ) vaneDirection=SENS_AGR_VANE_ENE;
	else if( vane>=0.28 && vane<0.35 ) vaneDirection=SENS_AGR_VANE_E;
	else if( vane>=0.35 && vane<0.5 ) vaneDirection=SENS_AGR_VANE_SSE;
	else if( vane>=0.5 && vane<0.65 ) vaneDirection=SENS_AGR_VANE_SE;
	else if( vane>=0.65 && vane<0.85 ) vaneDirection=SENS_AGR_VANE_SSW;
	else if( vane>=0.85 && vane<1.1 ) vaneDirection=SENS_AGR_VANE_S;
	else if( vane>=1.1 && vane<1.38 ) vaneDirection=SENS_AGR_VANE_NNE;
	else if( vane>=1.38 && vane<1.6 ) vaneDirection=SENS_AGR_VANE_NE;
	else if( vane>=1.6 && vane<1.96 ) vaneDirection=SENS_AGR_VANE_WSW;
	else if( vane>=1.96 && vane<2.15 ) vaneDirection=SENS_AGR_VANE_SW;
	else if( vane>=2.15 && vane<2.35 ) vaneDirection=SENS_AGR_VANE_NNW;
	else if( vane>=2.35 && vane<2.6 ) vaneDirection=SENS_AGR_VANE_N;
	else if( vane>=2.6 && vane<2.8 ) vaneDirection=SENS_AGR_VANE_WNW;
	else if( vane>=2.8 && vane<3.1 ) vaneDirection=SENS_AGR_VANE_W;
	else if( vane>=3.1 ) vaneDirection=SENS_AGR_VANE_NW;
}

/*	senceraConversion: converts the value read at the analog to digital
 * 					   converter corresponding to the humidity sensor
 * 					   into a humidity value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : humidity measured by the sensor in %RH
 * 
 */
float WaspSensorAgr_v20::senceraConversion(int readValue)
{
	float humidity = 0.0;   
	
    humidity = (float(readValue) * 3300.0 / 1023.0)/0.6; //sensor output (mV)
	humidity = (humidity - 800) / 31; // %hum
   
	return(humidity);
   
}
 
/*	mcpConversion: converts the value read at the analog to digital converter
 * 				   corresponding to the temperature sensor into a temperature value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : temperature measured by the sensor in ºC
 * 
 */
float WaspSensorAgr_v20::mcpConversion(int readValue)
{
	float temperature = 0;
   
	temperature = float(readValue) * 3300 / 1023; //sensor output (mV)
   
	temperature = (temperature - 500) / 10; 
   
	return(temperature);
   
}

WaspSensorAgr_v20 SensorAgrv20=WaspSensorAgr_v20();
