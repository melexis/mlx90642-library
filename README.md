
This is 90642 example driver with virtual i2c read/write functions. The actual
implementation of the i2c functions is MCU dependent and therefore needs to be
done individually. Functions that need to be implemented for each MCU are listed 
in `MLX90642_depends.h` file.

Since there is one source and two header files they can be built also just as
normal source files.

There are 4 types of i2c communications to implement:
1. Block read - this function is used for all data read-outs, including a signle
word read-out. For more information please refer to the datasheet chapter regarding
the communication protocol
2. Configuration - this function is used for the device configurations such as 
refresh rate, measurement mode, output format, emissivity background temperature,
i2c settings, etc. For more information please refer to the datasheet chapter regarding
the user configurable options.
3. Command - this function is used for sending commands such as reset, goto sleep,
force start/sync. For more information please refer to the datasheet chapter regarding
the communication protocol
4. Wake up - this function is used to get the device out of sleep mode.
For more information please refer to the datasheet chapter regarding
the communication protocol

The driver functions may also use a wait function. That funbction is also included
in the MLX90642_depends.h file and needs to be implemented individually for a given MCU. 

# Device configuration
There are set functions for every user configurable parameter. The different options
are pre-defined in the MLX90642.h header file. For more information and the default 
values please refer to the datasheet. After the required configuration changes are
made it may take up to 1 refresh period until they take effect.

```C
status = MLX90642_SetMeasMode(SA_90642, MLX90642_CONT_MEAS_MODE);               //set continuous measurement mode
status = MLX90642_SetMeasMode(SA_90642, MLX90642_STEP_MEAS_MODE);               //set step measurement mode

status = MLX90642_SetOutputFormat(SA_90642, MLX90642_TEMPERATURE_OUTPUT);       //set temperature output
status = MLX90642_SetOutputFormat(SA_90642, MLX90642_NORMALIZED_DATA_OUTPUT);   //set normalized data output

status = MLX90642_SetRefreshRate(SA_90642, MLX90642_REF_RATE_2HZ);              //set refresh rate to 2Hz
status = MLX90642_SetRefreshRate(SA_90642, MLX90642_REF_RATE_4HZ);              //set refresh rate to 4Hz
status = MLX90642_SetRefreshRate(SA_90642, MLX90642_REF_RATE_8HZ);              //set refresh rate to 8Hz
status = MLX90642_SetRefreshRate(SA_90642, MLX90642_REF_RATE_16HZ);             //set refresh rate to 16Hz

status = MLX90642_SetEmissivity(SA_90642, scaled_emissivity);                   //set the emissivity

status = MLX90642_SetI2CMode(SA_90642, MLX90642_I2C_MODE_FM);                   //set I2C FM mode
status = MLX90642_SetI2CMode(SA_90642, MLX90642_I2C_MODE_FM_PLUS);              //set I2C FM+ mode

status = MLX90642_SetSDALimitState(SA_90642, MLX90642_I2C_SDA_CUR_LIMIT_ON);    //enable SDA current limit
status = MLX90642_SetSDALimitState(SA_90642, MLX90642_I2C_SDA_CUR_LIMIT_OFF);   //disable SDA current limit

status = MLX90642_SetI2CLevel(SA_90642, MLX90642_I2C_LEVEL_VDD);                //set I2C level to Vdd
status = MLX90642_SetI2CLevel(SA_90642, MLX90642_I2C_LEVEL_1P8);                //set I2C level to 1.8V

status = MLX90642_SetTreflected(SA_90642, background_temperature_x100);         //set the background temperature

```

# Example program flow in continuous mode

After the environment is set you need to enter below flow to your program.

```C
#include "MLX90642.h"

/* Declare and implement here functions you find in MLX90642_depends.h */


int main(void)
{
    int status = 0; /**< Variable will store return values */
    uint16_t mlxto[MLX90642_TOTAL_NUMBER_OF_PIXELS + 1]; /**< Image data in degC*50 or normalized depending on the output format congifuration */
    
    /* Initialize the MLX90642 device - Prepare a clean start - start or sync a new measurement and wait for the data to be available for reading */
    status = MLX90642_Init(SA_90642);
    // if status < 0, handle the error
    
    /* This point can be the start of a loop */   
    /* Read out the image data */
    status = MLX90642_GetImage(SA_90642, mlxto);
    // if status < 0, handle the error
    
    /* Process the data */
    
    /* wait for new data */
    
    status = MLX90642_NO; 
    while(status == MLX90642_NO){
            
        status = MLX90642_IsReadWindowOpen(SA_90642);
        // if status < 0, handle the error         
    }
    /* Loop */

}
```

# Example program flow in step mode

After the environment is set you need to enter one of the below flows to your program.

1. Very simple flow with a function that automates the process

```C
#include "MLX90642.h"

/* Declare and implement here functions you find in MLX90642_depends.h */


int main(void)
{
    int status = 0; /**< Variable will store return values */
    uint16_t mlxto[MLX90642_TOTAL_NUMBER_OF_PIXELS + 1]; /**< Image data in degC*50 or normalized depending on the output format congifuration */
    
    /* Initialize the MLX90642 device - Prepare a clean start - start or sync a new measurement and wait for the data to be available for reading */
    status = MLX90642_Init(SA_90642);
    // if status < 0, handle the error
    
    /* Read out the image data */
    
    /* This point can be the start of a loop */   
    status = MLX90642_MeasureNow(SA_90642, mlxto);
    // if status < 0, handle the error
    
    /* Process the data */
    /* Loop */

}
```

2. A flow that allows for more flexibility

```C
#include "MLX90642.h"

/* Declare and implement here functions you find in MLX90642_depends.h */


int main(void)
{
    int status = 0; /**< Variable will store return values */
    uint16_t mlxto[MLX90642_TOTAL_NUMBER_OF_PIXELS + 1]; /**< Image data in degC*50 or normalized depending on the output format congifuration */
    
    /* Initialize the MLX90642 device - Prepare a clean start - start or sync a new measurement and wait for the data to be available for reading */
    status = MLX90642_Init(SA_90642);
    // if status < 0, handle the error
    
    /* This point can be the start of a loop */
    status = MLX90642_GetImage(SA_90642, mlxto);
    // if status < 0, handle the error
    
    /* Process the data */

    /* Clear the data ready flag - can be skipped if the full frame has already been read */ 
    status = MLX90642_ClearDataReady(SA_90642);
    // if status < 0, handle the error
    
    /* Start a new measurement */
    status = MLX90642_StartSync(SA_90642);
    // if status < 0, handle the error
      
    status = MLX90642_NO; 
    while(status == MLX90642_NO){
            
        status = MLX90642_IsDataReady(SA_90642);
        // if status < 0, handle the error         
    }
    
    /* Loop */

}
```
