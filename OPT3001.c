#include "OPT3001.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"



/*
*@brief Reads 16 bit register (or two 8bit registers).
Can be used to read one 16bit register or two stacked 8bit registers.
*@param reg_addr: register address
*@return uint16_t value of registers
*/
uint16_t OPT3001_Read2ByteRegister(uint8_t reg_addr){
    uint16_t buffer = I2C1_Read2ByteRegister(OPT3001_I2C_ADDR, reg_addr);
    return buffer;
}

/*
*@brief Write 16 bit value to 16 bit register (or two 8bit registers).
*@param reg_addr: register address
*@param data_tw: data to write to register
*/
void OPT3001_Write2ByteRegister(uint8_t reg_addr, uint16_t data_tw){
    I2C1_Write2ByteRegister(OPT3001_I2C_ADDR, reg_addr, data_tw);
}

/*
*@brief ReadnReplace function first reads the value from 16 bit register into a buffer. 
*Then it changes only the values of specified bits.
*Can be used to write to a register that has reserved or read only bits.
*Also can be used to change 1 bit.
*@param reg_addr: register address
*@param value: mask to changes specified bits
*/
void OPT3001_ReadnReplace(uint16_t reg_addr, uint16_t value){
    uint16_t buffer = OPT3001_Read2ByteRegister(reg_addr);
    uint16_t new_reg = (buffer | value);
    OPT3001_Write2ByteRegister(reg_addr, new_reg);
}

void OPT3001_full_scale_mode(void){
    //0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    //1100000000000000

    uint8_t current_reg_val[2];
    uint16_t buffer;
    
    I2C1_ReadDataBlock(OPT3001_I2C_ADDR, OPT3001_CONFIG_REG, current_reg_val, 2);
    buffer = (buffer | current_reg_val[0]) << 8;
    buffer |= current_reg_val[1];
    buffer |= 0x00CE;
    I2C1_Write2ByteRegister(OPT3001_I2C_ADDR, OPT3001_CONFIG_REG, buffer);
}

void OPT3001_init(void){
    I2C1_Write2ByteRegister(OPT3001_I2C_ADDR, OPT3001_CONFIG_REG, 0xCE10);
}

uint16_t read_data(void){
    uint8_t buffer[2];
    uint16_t result;
    
    I2C1_ReadDataBlock(OPT3001_I2C_ADDR, OPT3001_RESULT_REG, buffer, 2);
    result = (buffer[0] << 8) | buffer[1];
    return result;
}
/*  Returns the calculated value in lux */
float OPT3001_calculate_lux(uint16_t data){
    float lux;
    uint16_t mantissa, exponent;
    
    mantissa = data & 0x0FFF;
    exponent = (data & 0xF000) >> 12;
    lux = mantissa * (0.01 * (1 << exponent));

    return lux;
}