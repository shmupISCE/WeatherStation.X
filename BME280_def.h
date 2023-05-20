#ifndef BME280_DEF_H
#define	BME280_DEF_H

#ifdef	__cplusplus
extern "C" {
#endif

/* I2C addresses */
#define BME280_I2C_ADDR                           UINT8_C(0x76)

#define BME280_TEMP_PRESS_CALIB_DATA_ADDR         UINT8_C(0x88)
#define BME280_HUMIDITY_CALIB_DATA_ADDR           UINT8_C(0xE1)

#define CTRL_HUM                                  (0xF2)
#define STATUS_REG                                (0xF3) 
#define CTRL_MEAS                                 (0xF4) 
#define CONFIG_REG                                (0xF5)
                        
#define PRESS_MSB                                 (0xF7)
#define PRESS_LSB                                 (0xF8)
#define PRESS_XLSB                                (0xF9)
                        
#define TEMP_MSB                                  (0xFA)
#define TEMP_LSB                                  (0xFB)
#define TEMP_XLSB                                 (0xFC)

#define HUM_MSB                                   (0xFD)
#define HUM_LSB                                   (0xFE)

#define BME280_SLEEP_MODE                         UINT8_C(0x00)
#define BME280_FORCED_MODE                        UINT8_C(0x01)
#define BME280_NORMAL_MODE                        UINT8_C(0x03)

/* Oversampling macros */
#define BME280_NO_OVERSAMPLING                    UINT8_C(0x00)
#define BME280_OVERSAMPLING_1X                    UINT8_C(0x01)
#define BME280_OVERSAMPLING_2X                    UINT8_C(0x02)
#define BME280_OVERSAMPLING_4X                    UINT8_C(0x03)
#define BME280_OVERSAMPLING_8X                    UINT8_C(0x04)
#define BME280_OVERSAMPLING_16X                   UINT8_C(0x05)

/* Standby duration selection */
#define BME280_STANDBY_TIME_0_5_MS                (0x00)
#define BME280_STANDBY_TIME_62_5_MS               (0x01)
#define BME280_STANDBY_TIME_125_MS                (0x02)
#define BME280_STANDBY_TIME_250_MS                (0x03)
#define BME280_STANDBY_TIME_500_MS                (0x04)
#define BME280_STANDBY_TIME_1000_MS               (0x05)
#define BME280_STANDBY_TIME_10_MS                 (0x06)
#define BME280_STANDBY_TIME_20_MS                 (0x07)

/* Filter coefficient  */
#define BME280_FILTER_COEFF_OFF                   (0x00)
#define BME280_FILTER_COEFF_2                     (0x01)
#define BME280_FILTER_COEFF_4                     (0x02)
#define BME280_FILTER_COEFF_8                     (0x03)
#define BME280_FILTER_COEFF_16                    (0x04)
    
/* Macros for bit masking */
#define BME280_SENSOR_MODE_MSK                    UINT8_C(0x03)
#define BME280_CTRL_HUM_MSK                       UINT8_C(0x07)
#define BME280_CTRL_PRESS_MSK                     UINT8_C(0x1C)
#define BME280_CTRL_TEMP_MSK                      UINT8_C(0xE0)
#define BME280_FILTER_MSK                         UINT8_C(0x1C)
#define BME280_STANDBY_MSK                        UINT8_C(0xE0)
#define BME280_SPI3W_E_MSK                        UINT8_C(0x01)

typedef struct{
    uint8_t ctrl_meas_reg;
    uint8_t config_reg;
    uint8_t ctrl_hum_reg;
}bme280_settings_reg;

typedef struct{
    uint8_t osrs_t, osrs_p, mode;
    uint8_t osrs_h;
    uint8_t standby_time, filter, spi3w_en;
}bme280_num_settings;



typedef struct{
    char *Mode;
    char *Temperature_oversampling;
    char *Pressure_oversampling;
    char *Humidity_oversampling;
    char *Filter;
    char *Time_standby;
}BME280_DeviceSettings;


//Raw sensor measurement data from BME280
typedef struct{
    /*< un-compensated pressure */
    uint32_t pressure;

    /*< un-compensated temperature */
    uint32_t temperature;

    /*< un-compensated humidity */
    uint32_t humidity;

}bme280_uncomp_data;

typedef struct {
    /*< Compensated pressure */
    uint32_t pressure;

    /*< Compensated temperature */
    uint32_t temperature;

    /*< Compensated humidity */
    uint32_t humidity;

}bme280_data;

typedef struct {
    /*< Compensated pressure */
    float pressure;

    /*< Compensated temperature */
    float temperature;

    /*< Compensated humidity */
    float humidity;

}bme280_res;

typedef struct{
    /*< Calibration coefficient for the temperature sensor */
    uint16_t dig_t1;

    /*< Calibration coefficient for the temperature sensor */
    int16_t dig_t2;
    
    /*< Calibration coefficient for the temperature sensor */
    int16_t dig_t3;
    
    /*< Calibration coefficient for the pressure sensor */
    uint16_t dig_p1;

    /*< Calibration coefficient for the pressure sensor */
    int16_t dig_p2;

    /*< Calibration coefficient for the pressure sensor */
    int16_t dig_p3;

    /*< Calibration coefficient for the pressure sensor */
    int16_t dig_p4;

    /*< Calibration coefficient for the pressure sensor */
    int16_t dig_p5;

    /*< Calibration coefficient for the pressure sensor */
    int16_t dig_p6;

    /*< Calibration coefficient for the pressure sensor */
    int16_t dig_p7;

    /*< Calibration coefficient for the pressure sensor */
    int16_t dig_p8;

    /*< Calibration coefficient for the pressure sensor */
    int16_t dig_p9;

    /*< Calibration coefficient for the humidity sensor */
    uint8_t dig_h1;

    /*< Calibration coefficient for the humidity sensor */
    int16_t dig_h2;

    /*< Calibration coefficient for the humidity sensor */
    uint8_t dig_h3;

    /*< Calibration coefficient for the humidity sensor */
    int16_t dig_h4;

    /*< Calibration coefficient for the humidity sensor */
    int16_t dig_h5;

    /*< Calibration coefficient for the humidity sensor */
    int8_t dig_h6;

    int32_t t_fine;

} bme280_calib_data;

typedef int32_t BME280_S32_t;
typedef uint32_t BME280_U32_t;


#define BME280_CONCAT_BYTES(msb, lsb)             (((uint16_t)msb << 8) | (uint16_t)lsb)


#ifdef	__cplusplus
}
#endif

#endif	/* BME280_DEF_H */

