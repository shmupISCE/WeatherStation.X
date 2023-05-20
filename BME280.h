#ifndef BME280_H
#define BME280_H

#include <stdint.h>
#include <xc.h>
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "BME280_def.h"


//Specific read functions
uint8_t BME280_Read1ByteRegister(uint8_t reg_addr);
uint16_t BME280_Read2ByteRegister(uint8_t reg_addr);
void BME280_ReadnReplace(uint8_t reg_addr, uint8_t value);
//Specific write functions
void BME280_Write1ByteRegister(uint8_t reg_addr, uint8_t data_tw);
void BME280_Write2ByteRegister(uint8_t reg_addr, uint16_t data_tw);

void BME280_Reset(void);
void BME280_Init(void);
void BME280_WakeUp_FM(void);
void BME280_set_mode(uint8_t BME280_MODE);
void BME280_Config(uint8_t osrs_t, uint8_t osrs_p, uint8_t osrs_h, uint8_t filter, uint8_t t_sb, uint8_t mode);

void BME280_NormalizeMeasurements(bme280_data *comp_data, bme280_res *res);
void BME280_readFactoryCalibration(bme280_calib_data *calib_data);
void bme280_parse_settings(BME280_DeviceSettings *settings);
void BME280_read_measurement(bme280_uncomp_data *uncomp_data);
void BME280_compensate_data(bme280_uncomp_data *uncomp_data,
                            bme280_data *comp_data,
                            bme280_calib_data *calib_data);

#endif	/* BME280_H */

