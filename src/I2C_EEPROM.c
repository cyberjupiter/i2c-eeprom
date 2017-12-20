//I2C_EEPROM.c

#include "I2CinC.h"
#include "I2C_EEPROM.h"

/************************************************************************
Write a byte to the eeprom.

Parameter: slave address, eeprom memory address, data in byte

Example: EEPROMwrite_byte(0xA0, 0x01, 'J');

************************************************************************/
void EEPROMwrite_byte(uint8_t devAddr, uint8_t addr, uint8_t data)
{
  I2C_start();
  I2C_writeAddr(devAddr | I2C_WRITE);
  I2C_writeData(addr>>8);
  I2C_writeData(addr);
  I2C_writeData(data);
  I2C_stop();
}

/************************************************************************
Read a byte from the eeprom.

Parameter: slave address, eeprom memory address, 

Return: the byte of the specified eeprom memory address

Example: EEPROMread_byte(0xA0, 0x01);

************************************************************************/
uint8_t EEPROMread_byte(uint8_t devAddr, uint8_t addr)
{
  uint8_t tempData;
  I2C_start_wait(devAddr | I2C_WRITE);
  I2C_writeData(addr>>8);
  I2C_writeData(addr);
  I2C_restart(); 
  I2C_writeAddr(devAddr | I2C_READ);
  tempData = I2C_read_nack();
  I2C_stop();
  
  return tempData;
}

/********************************************************************************
Write a stream of bytes to the eeprom.

Parameter: slave address, eeprom memory address, data string, the length of data(number of characters)

Example: EEPROMwrite(0xA0, 0x01, "Jagung", 6);

*******************************************************************************/
void EEPROMwrite(uint8_t devAddr, uint16_t addr, uint8_t *data, uint8_t length)
{
  I2C_start();
  I2C_writeAddr(devAddr | I2C_WRITE);
  I2C_writeData(addr>>8);
  I2C_writeData(addr);
  for (uint8_t i = 0; i<length; i++)
  {
	I2C_writeData(data[i]);
  }
  I2C_stop();
}

/*******************************************************************************
Read a stream of bytes from the eeprom.

Parameter: slave address, eeprom memory address, the length of data(number of characters), array for data to be stored

Example: EEPROMread(0xA0, 0x01, 6, store);

*store must be declared as a char array

******************************************************************************/
void EEPROMread(uint8_t devAddr, uint16_t addr, uint8_t length, uint8_t *dataArray)
{
  I2C_start_wait(devAddr | I2C_WRITE);
  I2C_writeData(addr>>8);
  I2C_writeData(addr); 
  I2C_restart(); 
  I2C_writeAddr(devAddr | I2C_READ);
  for (uint8_t i = 0; i<length-1; i++)
  {
	dataArray[i] = I2C_read_ack();
  }
  dataArray[length-1] = I2C_read_nack();
  
  I2C_stop(); 
}
 
/*******************************************************************************
Write a new byte if only it is different from the current byte.

If current byte is 'a', and the new byte is 'a', no write is executed.
If current byte is 'a', and the new byte is 'b', write will be executed.

Parameter: slave address, eeprom memory address, data

Example: EEPROMupdate(0xA0, 0x01, 'j');

******************************************************************************/
void EEPROMupdate(uint8_t devAddr, uint8_t addr, uint8_t newData)
{
  uint8_t tempData;
  I2C_start_wait(devAddr | I2C_WRITE);
  I2C_writeData(addr>>8);
  I2C_writeData(addr); 
  I2C_restart();
  I2C_writeAddr(devAddr | I2C_READ);
	
  tempData = I2C_read_nack();
	
  if (tempData != newData)
  {
	I2C_restart();
	I2C_writeAddr(devAddr | I2C_WRITE);
	I2C_writeData(addr>>8);
	I2C_writeData(addr);
	I2C_writeData(newData);
  }
  I2C_stop();
}

/****************************************************************************
Write a float value to the eeprom

Parameter: slave adress, eeprom memory adress, address of float variable

Example: EEPROMwrite_float(0xA0, 0x01, &var);

*write_var is declared as float

****************************************************************************/
void EEPROMwrite_float(uint8_t devAddr, uint16_t addr, float data)
{
  float *fp;
  fp = &data;
  
  uint8_t *p;
  p = (uint8_t*) fp;
  
  /*
  uint8_t *p;
  p = (uint8_t*) data;
  */
  
  I2C_start();																	
  I2C_writeAddr(devAddr | I2C_WRITE);
  I2C_writeData(addr>>8);
  I2C_writeData(addr);
	
  for (uint8_t i = 0; i<4; i++)
  {
	I2C_writeData(*p++);
  }
  
  I2C_stop();
}

/****************************************************************************
Read a float value to the eeprom(if only you know there is a float value!)

Parameter: slave address, eeprom memory address, address of float variable

Example: EEPROMread_float(0xA0, 0x01, &read_var);

*read_var is declared as float

****************************************************************************/
void EEPROMread_float(uint8_t devAddr, uint16_t addr, float *data)
{
  
  uint8_t *p;
  p = (uint8_t*) data;
   
  I2C_start_wait(devAddr | I2C_WRITE);
  I2C_writeData(addr>>8);
  I2C_writeData(addr); 
  I2C_restart(); 
  I2C_writeAddr(devAddr | I2C_READ);
  for (uint8_t i = 0; i<3; i++)
  {
	*p++ = I2C_read_ack();	
  }
  *p++ = I2C_read_nack();
  
  I2C_stop(); 
}
