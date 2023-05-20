#include "mcc_generated_files/mcc.h"
#include "BME280.h"     //Weather click
#include "OPT3001.h"    //Ambient 2 click
#include <stdio.h>
#include "glcd.h"

#include "systfont.h"
#include <stdlib.h>

void main(void){
    // Initialize the device
    SYSTEM_Initialize();

    //Initialize the GLCD
    
    glcd_reset(); 
    glcd_on();
    glcd_clear();
    
    // Base text
    glcd_adv_systext(1, 1, "Temperature: ", 13);   //(x, y, text, text_size)
    glcd_adv_systext(1, 12, "Pressure: ", 10);   //(x, y, text, text_size)
    glcd_adv_systext(1, 23, "Humidity: ", 13);   //(x, y, text, text_size)

    bme280_calib_data calib_data;
    bme280_uncomp_data uncomp_data;
    bme280_data comp_data;
    bme280_res result;

    BME280_Init();
    BME280_readFactoryCalibration(&calib_data);
    
    // Float -> string to send to glcd
    char temp[15];
    char press[15];
    char humidity[15];
    
    while (1) {
        //Set to Forced mode
        BME280_WakeUp_FM();
        // Read raw data
        BME280_read_measurement(&uncomp_data);
        //Compensate raw data and return to data structure BME280_data
        BME280_compensate_data(&uncomp_data, &comp_data, &calib_data);
        BME280_NormalizeMeasurements(&comp_data, &result);

                //Convert float to string 
        sprintf(temp, "%f", result.temperature);
        sprintf(press, "%f", result.pressure);
        sprintf(humidity, "%f", result.humidity);
        
        printf("Temperature: %lu \tPressure: %lu\tHumidity: %lu %%", result.temperature, result.pressure, result.humidity);
        glcd_adv_systext(75, 1, temp, 5); 
        glcd_adv_systext(60, 12, press, 5);
        glcd_adv_systext(60, 24, humidity, 5);
        
        //(x, y, text, text_size)*/
        __delay_ms(2000);
    }
}
