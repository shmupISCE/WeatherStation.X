#include "mcc_generated_files/mcc.h"
#include "BME280.h"     //Weather click
#include "OPT3001.h"    //Ambient 2 click
#include <stdio.h>

void single_shot_register(void);



int32_t burst_read_temperature() {
    int8_t temperature[3];
    I2C1_ReadDataBlock(BME280_I2C_ADDR, 0xFA, temperature, 3);
    int32_t temp = ((temperature[0] << 8) | temperature[1]);
    temp = (temp << 8) | temperature[2];
    temp = temp >> 4; //  Should work
    return temp;

}

void print_bme280_settings(BME280_DeviceSettings *settings){
    printf("Temperature oversampling: %s\n", settings->Temperature_oversampling);
    printf("Pressure oversampling: %s\n", settings->Pressure_oversampling);
    printf("Humidity oversampling: %s\n", settings->Humidity_oversampling);
    printf("Filter: %s\n", settings->Filter);
    printf("Time standby: %s\n", settings->Time_standby);
}

void main(void){
    // Initialize the device
    SYSTEM_Initialize();
    
    bme280_calib_data calib_data;
    bme280_uncomp_data uncomp_data;
    bme280_data comp_data;
    BME280_DeviceSettings *dev;
    
    BME280_Init();
    BME280_readFactoryCalibration(&calib_data);
     
    BME280_Write1ByteRegister(CTRL_MEAS, 0x25);
    uint8_t osrs_h_sett = BME280_Read1ByteRegister(CTRL_HUM);
                
    uint8_t test;
    while (1) {
        
        //Set to Forced mode
        BME280_WakeUp_FM();
        bme280_parse_settings(&dev);
        print_bme280_settings(&dev);
        
        test = BME280_Read1ByteRegister(CTRL_MEAS);
        printf("CTRL_MEAS: %x\nCTRL_HUM: %x\n", test, osrs_h_sett);
        
        // Read raw data
        BME280_read_measurement(&uncomp_data);
        //Compensate raw data and return to data structure BME280_data
        BME280_compensate_data(&uncomp_data, &comp_data, &calib_data);
        BME280_NormalizeMeasurements(&comp_data);
        
        
        printf("\nRaw temp: %d\tRaw press: %d\tRaw humidity: %d\n", uncomp_data.temperature, uncomp_data.pressure, uncomp_data.humidity);
        printf("\nTemperature: %d \tPressure: %d\tHumidity: %d%% \n", comp_data.temperature, comp_data.pressure, comp_data.humidity);
        __delay_ms(2000);
    }
}

/**
 End of File
 */














void single_shot_register(void) {
    uint8_t temp_msb_reg;
    uint8_t temp_lsb_reg;
    uint8_t temp_xlsb_reg;

    uint8_t humidity_msb_reg;
    uint8_t humidity_lsb_reg;

    uint8_t pressure_msb_reg;
    uint8_t pressure_lsb_reg;
    uint8_t pressure_xlsb_reg;

    pressure_msb_reg = I2C1_Read1ByteRegister(BME280_I2C_ADDR, 0xF7);
    pressure_lsb_reg = I2C1_Read1ByteRegister(BME280_I2C_ADDR, 0xF8);
    pressure_xlsb_reg = I2C1_Read1ByteRegister(BME280_I2C_ADDR, 0xF9);

    temp_msb_reg = I2C1_Read1ByteRegister(BME280_I2C_ADDR, 0xFA);
    temp_lsb_reg = I2C1_Read1ByteRegister(BME280_I2C_ADDR, 0xFB);
    temp_xlsb_reg = I2C1_Read1ByteRegister(BME280_I2C_ADDR, 0xFC);

    humidity_msb_reg = I2C1_Read1ByteRegister(BME280_I2C_ADDR, 0xFD);
    humidity_lsb_reg = I2C1_Read1ByteRegister(BME280_I2C_ADDR, 0xFE);

    printf("*** Temperature registers ***");
    printf("\nTemp MSB: %d\nTemp LSB: %d\nTemp XLSB: %d\n", temp_msb_reg, temp_lsb_reg, temp_xlsb_reg);
    printf("*** Humidity registers  ***");
    printf("\nHumidity MSB: %d\nHumidity LSB: %d\n", humidity_msb_reg, humidity_lsb_reg);
    printf("*** Pressure registers  ***");
    printf("\nPressure MSB: %d\nPressure LSB: %d\nPressure XLSB: %d\n", pressure_msb_reg, pressure_lsb_reg, pressure_xlsb_reg);
}