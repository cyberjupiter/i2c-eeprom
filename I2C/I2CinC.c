//I2CinC.c

#include <avr/io.h>
#include <compat/twi.h>
#include <inttypes.h>

#include "Arduino.h"

#include "I2CinC.h"

/* define CPU frequency in hz here */
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/* I2C clock in Hz */
#define SCL_CLOCK  100000L


void I2C_init(void)
{
	digitalWrite(SDA, 1);
	digitalWrite(SCL, 1);
	TWSR = 0;
	TWBR = ((F_CPU/SCL_CLOCK)-16)/2;
}

uint8_t I2C_start(void)
{
	TWCR = 0b00000000;

	TWCR = 0b10100100;
	//TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while((TWCR & (1<<TWINT)) == 0);
	
	if((TWSR & 0xF8) != TW_START)
	{
		return 1; 
	}
	
	return 0;
}


/* thanks to Peter for this function */
void I2C_start_wait(uint8_t address)
{
    uint8_t   twst;

    while ( 1 )
    {
	    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    
    	while(!(TWCR & (1<<TWINT)));
    
    	twst = TW_STATUS & 0xF8;
    	if ( (twst != TW_START) && (twst != TW_REP_START)) continue;
    
    	TWDR = address;
    	TWCR = (1<<TWINT) | (1<<TWEN);
    
    	while(!(TWCR & (1<<TWINT)));
    
    	twst = TW_STATUS & 0xF8;
    	if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) ) 
    	{    	    

	        TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	        
	        while(TWCR & (1<<TWSTO));
	        
    	    continue;
    	}
    	//if( twst != TW_MT_SLA_ACK) return 1;
    	break;
     }

}/* i2c_start_wait */

uint8_t I2C_restart(void)
{ 
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while( !(TWCR & (1<<TWINT)) );
	
	if( (TWSR & 0xF8) != TW_REP_START ){ return 1; }
	
	return 0;
}


uint8_t I2C_read_nack(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while( !(TWCR & (1<<TWINT)) );
	
	return TWDR;
}

uint8_t I2C_read_ack(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA); 
	while( !(TWCR & (1<<TWINT)) );

	return TWDR;
}

uint8_t I2C_writeAddr(uint8_t address)
{

	TWDR = address;

	TWCR = (1<<TWINT) | (1<<TWEN);

	while( !(TWCR & (1<<TWINT)) );
	
	if( (TWSR & 0xF8) != TW_MT_SLA_ACK ){ return 1; }
	
	return 0;
}

uint8_t I2C_writeData(uint8_t data)
{

	TWDR = data;

	TWCR = (1<<TWINT) | (1<<TWEN);

	while( !(TWCR & (1<<TWINT)) );
	
	if( (TWSR & 0xF8) != TW_MT_DATA_ACK ){ return 1; }
	
	return 0;
}

void I2C_stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	while(TWCR & (1<<TWSTO));
}
