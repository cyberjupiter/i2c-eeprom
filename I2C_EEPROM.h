//I2C_EEPROM.h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EEPROM_Master_h
#define EEPROM_Master_h

void EEPROMwrite_byte(uint8_t pDevAddr, uint8_t addr, uint8_t data);
uint8_t EEPROMread_byte(uint8_t pDevAddr, uint8_t addr);
void EEPROMwrite(uint8_t pDevAddr, uint16_t addr, uint8_t *data, uint8_t length);
uint8_t EEPROMread_bytef(uint8_t devAddr, uint8_t addr);
void EEPROMread(uint8_t pDevAddr, uint16_t addr, uint8_t length, uint8_t *dataArray);
void EEPROMupdate(uint8_t pDevAddr, uint8_t addr, uint8_t new_data);
void EEPROMwrite_float(uint8_t devAddr, uint16_t addr, float data);
void EEPROMread_float(uint8_t devAddr, uint16_t addr, float *data);
#endif

#ifdef __cplusplus
} // extern "C"
#endif
