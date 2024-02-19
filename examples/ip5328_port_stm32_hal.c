#if 0
#include "stm32xxx.h"


uint8_t ip5328_read_reg(uint8_t addr) {
  uint8_t data = 0; 
  HAL_StatusTypeDef status;
  status = HAL_I2C_Master_Transmit(&hi2c1, IP5328_ADDR, &addr, 1, 100);
  if (status != HAL_OK) {
    return 0xFF;
  }
  status = HAL_I2C_Master_Receive(&hi2c1, IP5328_ADDR, &data, 1, 100);
  if (status != HAL_OK) {
    return 0xFF;
  }
  return data;
}

void ip5328_write_reg(uint8_t addr, uint8_t data) {
  uint8_t buffer[2];
  buffer[0] = addr;
  buffer[1] = data;
  HAL_I2C_Master_Transmit(&hi2c1, IP5328_ADDR, buffer, 2, 100);
}


#endif
