/*
 * DPS310XTSA1.h
 *
 *  Created on: 10 juil. 2023
 *      Author: yaxsomo
 */

#ifndef INC_PRESSURE_H_
#define INC_PRESSURE_H_


#include <Reg_Addresses.h>
#include <main.h>
extern I2C_HandleTypeDef hi2c1;


typedef struct {
    float pressure_hpa;
    float temperature_celsius;
} PressureTempData;


/*
 * Barometer -> DPS310XTSA1
 */
#define I2C_DPS310_ADDRESS     0x77 << 1  // Barometer Device Address


#include "stdint.h"


#define DPS310_READ_WAIT_FOR_REG_ATTEMPTS 3
#define DPS310_OK 0

#define DPS310_HW_ID_ERROR -1
#define DPS310_PRODUCT_ID_ERROR -2
#define DPS310_TOO_BUSY_ERROR -3
#define DPS310_WAIT_TIMEOUT_ERROR -4
#define DPS310_UNKNOWN_RATE_ERROR -5
#define DPS310_TMP_COEF_SRC_INTERNAL_ERROR -6

#define DPS310_I2C_FAIL_ERROR -10

#define DPS310_I2C_MAX_BUFF_SIZE 10

#define DPS310_PSR_B2_REG 0x00u
#define DPS310_DSP_B1_REG 0x01u
#define DPS310_DSP_B0_REG 0x02u

#define DPS310_TMP_B2_REG 0x03u
#define DPS310_TMP_B1_REG 0x04u
#define DPS310_TMP_B0_REG 0x05u

#define DPS310_PRS_CFG_REG 0x06u

#define DPS310_PRS_CFG_PM_RATE_MASK 0x70u

#define DPS310_CFG_RATE_1_MEAS 0x00u
#define DPS310_CFG_RATE_2_MEAS 0x10u
#define DPS310_CFG_RATE_4_MEAS 0x20u
#define DPS310_CFG_RATE_8_MEAS 0x30u
#define DPS310_CFG_RATE_16_MEAS 0x40u
#define DPS310_CFG_RATE_32_MEAS 0x50u
#define DPS310_CFG_RATE_64_MEAS 0x60u
#define DPS310_CFG_RATE_128_MEAS 0x70u

#define DPS310_PRS_CFG_PM_PRC_SINGLE 0x00u  // low precision
#define DPS310_PRS_CFG_PM_PRC_2_TIMES 0x01u  // low power
#define DPS310_PRS_CFG_PM_PRC_4_TIMES 0x02u
#define DPS310_PRS_CFG_PM_PRC_8_TIMES 0x03u
#define DPS310_PRS_CFG_PM_PRC_16_TIMES 0x04u // standard
#define DPS310_PRS_CFG_PM_PRC_32_TIMES 0x05u
#define DPS310_PRS_CFG_PM_PRC_64_TIMES 0x06u // high precision
#define DPS310_PRS_CFG_PM_PRC_128_TIMES 0x07u

#define DPS310_TMP_CFG_REG 0x07u

#define DPS310_TMP_CFG_REG_TMP_EXT_INTERNAL 0x00u  // in ASIC
#define DPS310_TMP_CFG_REG_TMP_EXT_EXTERNAL 0x80u  // in pressure sensor MEMS element

#define DPS310_TMP_CFG_TMP_RATE_MASK 0x70u

#define DPS310_TMP_CFG_TMP_PRC_SINGLE 0x00u  // default - measurment time 3.6 ms
#define DPS310_TMP_CFG_TMP_PRC_2_TIMES 0x01u
#define DPS310_TMP_CFG_TMP_PRC_4_TIMES 0x02u
#define DPS310_TMP_CFG_TMP_PRC_8_TIMES 0x03u
#define DPS310_TMP_CFG_TMP_PRC_16_TIMES 0x04u
#define DPS310_TMP_CFG_TMP_PRC_32_TIMES 0x05u
#define DPS310_TMP_CFG_TMP_PRC_64_TIMES 0x06u
#define DPS310_TMP_CFG_TMP_PRC_128_TIMES 0x07u

#define DPS310_MEAS_CFG_REG 0x08u

#define DPS310_MEAS_CFG_COEF_RDY_AVAILABLE 0x80u
#define DPS310_MEAS_CFG_SENSOR_RDY_COMPLETE 0x40u
#define DPS310_MEAS_CFG_TMP_RDY 0x20u
#define DPS310_MEAS_CFG_PRS_RDY 0x10u

#define DPS310_MEAS_CFG_MEAS_CTRL_MASK 0x07u
#define DPS310_MEAS_CFG_MEAS_CTRL_IDLE 0x00u
#define DPS310_MEAS_CFG_MEAS_CTRL_PRS 0x01u
#define DPS310_MEAS_CFG_MEAS_CTRL_TMP 0x02u
#define DPS310_MEAS_CFG_MEAS_CTRL_CONTINUOUS_PRS 0x05u
#define DPS310_MEAS_CFG_MEAS_CTRL_CONTINUOUS_TMP 0x06u
#define DPS310_MEAS_CFG_MEAS_CTRL_CONTINUOUS_PRS_TMP 0x07u

#define DPS310_CFG_REG_REG 0x09u
#define DPS310_CFG_RET_INT_HL 0x80u
#define DPS310_CFG_RET_INT_SEL 0x70u
#define DPS310_CFG_RET_TMP_SHIFT_EN 0x08u
#define DPS310_CFG_RET_PRS_SHIFT_EN 0x04u
#define DPS310_CFG_RET_FIFO_EN 0x02u
#define DPS310_CFG_RET_TMP_SPI_MODE 0x01u

#define DPS310_INT_STS_REG 0x0Au
#define DPS310_INT_STS_INT_FIFO_FULL_MASK 0x04u
#define DPS310_INT_STS_INT_TMP_MASK 0x02u
#define DPS310_INT_STS_INT_PRS_MASK 0x01u

#define DPS310_FIFO_STS_REG 0x0Bu
#define DPS310_FIFO_STS_FIFO_FULL_MASK 0x02u
#define DPS310_FIFO_STS_FIFO_EMPTY_MASK 0x01u

#define DPS310_RESET_REG 0x0Cu
#define DPS310_RESET_FIFO_FLUSH 0x80u
#define DPS310_RESET_SOFT_RST_VALUE 0x09u

#define DPS310_PRODUCT_ID_REG 0x0Du
#define DPS310_PRODUCT_ID_VALUE 0x10u
#define DPS310_PRODUCT_ID_REV_ID_MASK 0xF0u
#define DPS310_PRODUCT_ID_PROD_ID_MASK 0x0Fu

#define DPS310_COEF_REG 0x10u

#define DPS310_TMP_COEF_SRCE 0x28u

#define DPS310_TMP_COEF_SRCE_MASK 0x80u
#define DPS310_TMP_COEF_SRCE_EXTERNAL 0x80u
#define DPS310_TMP_COEF_SRCE_INTERNAL 0x00u


#define PRESSURE_HECTO_PASCAL_CONVERSION 0.01f
#define PRESSURE_PASCAL_CONVERSION 1.00f




typedef enum {
    IDLE = DPS310_MEAS_CFG_MEAS_CTRL_IDLE,
    PRESSURE_MEASUREMENT = DPS310_MEAS_CFG_MEAS_CTRL_PRS,
    TEMPERATURE_MEASUREMENT = DPS310_MEAS_CFG_MEAS_CTRL_TMP
} dps310_mode_t;

void UART_Transmit_Messages_Pressure(const char* str);

int32_t Pressure_Init();

int16_t dps310_probe();

int16_t dps310_configure_temperature(uint8_t data);

int16_t dps310_configure_pressure(uint8_t data);

int16_t dps310_read(float *p_temperature, float *p_pressure);

int16_t dps310_wakeup(dps310_mode_t mode);

int16_t dps310_sleep();

int16_t dps310_reset();

void dps310_i2c_init(void);

int8_t dps310_i2c_read(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);

int8_t dps310_i2c_write(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);

int16_t read_temperature(float *p_temperature);

int16_t read_pressure(float *p_pressure);

void dps310_i2c_wakeup();

void dps310_i2c_sleep();

void dps310_i2c_delay_ms(uint32_t delay);

PressureTempData Transmit_Pressure_Temp_Data();




#endif /* INC_PRESSURE_H_ */



