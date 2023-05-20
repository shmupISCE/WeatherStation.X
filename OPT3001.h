#ifndef OPT3001_H
#define	OPT3001_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define OPT3001_I2C_ADDR                    (0x44)

    /*  Registers   */
#define OPT3001_RESULT_REG                  (0x00)
#define OPT3001_CONFIG_REG                  (0x01)
#define OPT3001_LOW_LIMIT_REG               (0x02)
#define OPT3001_HIGH_LIMIT_REG              (0x03)
#define OPT3001_DEV_ID                      (0x7F)
    
    /*  Configuration   */
#define OPT3001_CONVERSION_TIME_100_ms      (0x00) 
#define OPT3001_CONVERSION_TIME_800_ms      (0x01) 
    
#define OPT3001_CONVERSION_MODE_SHT_DWN     (0x00)
#define OPT3001_CONVERSION_MODE_SINGLE_SHOT (0x01)
#define OPT3001_CONVERSION_MODE_CONTINUOUS  (0x02)
    
#define OPT3001_ONE_FAULT_COUNT             (0x00)
#define OPT3001_TWO_FAULT_COUNTS            (0x01)
#define OPT3001_FOUR_FAULT_COUNTS           (0x02)
#define OPT3001_EIGHT_FAULT_COUNTS          (0x03)
    
    
uint16_t OPT3001_Read2ByteRegister(uint8_t reg_addr);    
void OPT3001_Write2ByteRegister(uint8_t reg_addr, uint16_t data_tw);  
void OPT3001_ReadnReplace(uint16_t reg_addr, uint16_t value);

void OPT3001_Config(uint8_t conversion_time, uint8_t conversion_mode, uint8_t fault_counts);
float OPT3001_calculate_lux(uint16_t data);
void OPT3001_full_scale_mode(void);



#ifdef	__cplusplus
}
#endif

#endif	/* OPT3001_H */

