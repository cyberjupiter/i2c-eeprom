//I2CinC.h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef I2CinC_h
#define I2CinC_h

#include <inttypes.h>

#define I2C_READ  0x01
#define I2C_WRITE 0x00

#define SDA	A4
#define SCL A5

void I2C_init(void);
uint8_t I2C_start(void);
uint8_t I2C_restart(void);
uint8_t I2C_writeData(uint8_t data);
uint8_t I2C_writeAddr(uint8_t address);
void I2C_start_wait(uint8_t address);
uint8_t I2C_read_nack(void);
uint8_t I2C_read_ack(void);
void I2C_stop(void);

#endif

#ifdef __cplusplus
} // extern "C"
#endif
