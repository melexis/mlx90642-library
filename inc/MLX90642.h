/**
 * @copyright (C) 2017 Melexis N.V.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <MLX90642_depends.h>

#ifndef _MLX90642_H_
#define _MLX90642_H_

#define MLX90642_NACK_ERR 1
#define MLX90642_INVAL_VAL_ERR 2
#define MLX90642_TIMEOUT_ERR 3

#define MLX90642_YES 1
#define MLX90642_NO 0

#define SA_90642_DEFAULT 0x66
#define SA_90642_MIN 0x01
#define SA_90642_MAX 0x7F

#define MLX90642_RESET_TIME 10 /**Time to wait after hot reset with I2C command, in milliseconds)*/
#define MLX90642_EE_WRITE_TIME 15 /**Time to wait for EEPROM write, in milliseconds)*/

#define MLX90642_AUX_DATA_ADDRESS 0x2E02
#define MLX90642_IR_DATA_ADDRESS 0x2E2A
#define MLX90642_TO_DATA_ADDRESS 0x342C
#define MLX90642_TA_DATA_ADDRESS 0x3A2C
#define MLX90642_PROGRESS_DATA_ADDRESS 0x3C10
#define MLX90642_FLAGS_ADDRESS 0x3C14
#define MLX90642_FLAGS_BUSY_MASK 0x0001
#define MLX90642_FLAGS_READY_MASK 0x0100
#define MLX90642_FLAGS_READY_SHIFT 8

#define MLX90642_REFRESH_RATE_ADDRESS 0x11F0
#define MLX90642_REFRESH_RATE_MASK 0x0007

#define MLX90642_EMISSIVITY_ADDRESS 0x11F2
#define MLX90642_APPLICATION_CONFIG_ADDRESS 0x11F4
#define MLX90642_OUTPUT_FORMAT_MASK 0x0100
#define MLX90642_OUTPUT_FORMAT_SHIFT 8
#define MLX90642_MEAS_MODE_MASK 0x0800
#define MLX90642_MEAS_MODE_SHIFT 11

#define MLX90642_I2C_CONFIG_ADDRESS 0x11FC
#define MLX90642_I2C_MODE_MASK 0x0001
#define MLX90642_I2C_SDA_CUR_LIMIT_MASK 0x0002
#define MLX90642_I2C_SDA_CUR_LIMIT_SHIFT 1
#define MLX90642_I2C_LEVEL_MASK 0x0004
#define MLX90642_I2C_LEVEL_SHIFT 2

#define MLX90642_I2C_SA_ADDRESS 0x11FE
#define MLX90642_I2C_SA_MASK 0x007F

#define MLX90642_REFLECTED_TEMP_ADDRESS 0xEEEE

#define MLX90642_NUMBER_OF_ID_WORDS 4
#define MLX90642_ID1_ADDR 0x1230
#define MLX90642_ID2_ADDR 0x1232
#define MLX90642_ID3_ADDR 0x1234
#define MLX90642_ID4_ADDR 0x1236
#define MLX90642_NUMBER_OF_FWVER_WORDS 2
#define MLX90642_FW_VER_ADDRESS1 0xFFF8
#define MLX90642_FW_VER_ADDRESS2 0xFFFA

#define MLX90642_TOTAL_NUMBER_OF_AUX 20
#define MLX90642_TOTAL_NUMBER_OF_PIXELS 768

#define MLX90642_POLL_TIME_MS 2
#define MLX90642_MAX_POLL_TRIES 100
#define MLX90642_REF_TIME 2000

#define MLX90642_CONT_MEAS_MODE 0
#define MLX90642_STEP_MEAS_MODE 0x0800
#define MLX90642_TEMPERATURE_OUTPUT 0
#define MLX90642_NORMALIZED_DATA_OUTPUT 0x0100
#define MLX90642_REF_RATE_2HZ 2
#define MLX90642_REF_RATE_4HZ 3
#define MLX90642_REF_RATE_8HZ 4
#define MLX90642_REF_RATE_16HZ 5
#define MLX90642_REF_RATE_32HZ 6
#define MLX90642_I2C_MODE_FM 1
#define MLX90642_I2C_MODE_FM_PLUS 0
#define MLX90642_I2C_SDA_CUR_LIMIT_OFF 2
#define MLX90642_I2C_SDA_CUR_LIMIT_ON 0
#define MLX90642_I2C_LEVEL_VDD 0
#define MLX90642_I2C_LEVEL_1P8 4

#define MLX90642_CONFIG_OPCODE 0x3A2E
#define MLX90642_CMD_OPCODE 0x0180
#define MLX90642_ADRESSED_RESET_CMD 0x0006
#define MLX90642_START_SYNC_MEAS_CMD 0x0001
#define MLX90642_SLEEP_CMD 0x0007

#define MLX90642_MS_BYTE(reg)   (reg >> 8)
#define MLX90642_LS_BYTE(reg)   (reg & 0x00FF)

/** Get the ID of the MLX90642 device
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[out] mlxid Pointer to where the device ID is stored
 *
 * @retval <0 Error while reading the device ID
 *
 */
int MLX90642_GetID(uint8_t slaveAddr, uint16_t *mlxid);

/** Get the firmware version of the MLX90642 device
 * @note Different version of the FW may support different features
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[out] fwver Pointer to where the firmware versioin is stored
 *
 * @retval <0 Error while reading the firmware version
 *
 */
int MLX90642_GetFWver(uint8_t slaveAddr, uint8_t *fwver);

/** Get the measurement mode of the MLX90642 device
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval = @link MLX90642_CONT_MEAS_MODE @endlink Continuous measurement mode
 * @retval = @link MLX90642_STEP_MEAS_MODE @endlink Step measurement mode
 * @retval <0 Error while getting the measurement mode
 *
 */
int MLX90642_GetMeasMode(uint8_t slaveAddr);

/** Set the measurement mode of the MLX90642 device
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[in] meas_mode Measurement mode to set - @link MLX90642_CONT_MEAS_MODE @endlink - continuous mode, @link MLX90642_STEP_MEAS_MODE @endlink - Step measurement mode
 *
 * @retval 0 Measurement mode successfully set
 * @retval <0 Error setting the measurement mode
 *
 */
int MLX90642_SetMeasMode(uint8_t slaveAddr, uint16_t meas_mode);

/** Get the output data format of the MLX90642 device
 * @note The current FW version supports refresh rates of up to 15Hz for the temperature data ouput and up to 20Hz for the normalized data output
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval = @link MLX90642_TEMPERATURE_OUTPUT @endlink Temperature data output
 * @retval = @link MLX90642_NORMALIZED_DATA_OUTPUT @endlink Normalized data output
 * @retval <0 Error while getting the output data format
 *
 */
int MLX90642_GetOutputFormat(uint8_t slaveAddr);

/** Set the output format of the MLX90642 device
 * @note The current FW version supports refresh rates of up to 15Hz for the temperature data ouput and up to 20Hz for the normalized data output
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[in] output_format Output format to set - @link MLX90642_TEMPERATURE_OUTPUT @endlink - temperature data, @link MLX90642_NORMALIZED_DATA_OUTPUT @endlink - Normalized data
 *
 * @retval 0 Output data format successfully set
 * @retval <0 Error setting the output data format
 *
 */
int MLX90642_SetOutputFormat(uint8_t slaveAddr, uint16_t output_format);

/** Get the refresh rate of the MLX90642 device
 * @note Refresh rates < 2Hz are not allowed and the device will default to 2Hz
 * @note The current FW version supports refresh rates of up to 15Hz (at 16Hz and 32Hz settings) for the temperature data ouput and up to 20Hz (at 32Hz setting) for the normalized data output
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval = @link MLX90642_REF_RATE_2HZ @endlink Refresh rate is 2Hz
 * @retval = @link MLX90642_REF_RATE_4HZ @endlink Refresh rate is 4Hz
 * @retval = @link MLX90642_REF_RATE_8HZ @endlink Refresh rate is 8Hz
 * @retval = @link MLX90642_REF_RATE_16HZ @endlink Refresh rate is 16Hz (15Hz for temperature data output)
 * @retval = @link MLX90642_REF_RATE_32HZ @endlink Refresh rate is 32Hz (15Hz for temperature data output and 20Hz for normalized data output)
 * @retval <0 Error while getting the refresh rate
 *
 */
int MLX90642_GetRefreshRate(uint8_t slaveAddr);

/** Set the refresh rate of the MLX90642 device
 * @note Refresh rates < 2Hz are not allowed and the device will default to 2Hz
 * @note The current FW version supports refresh rates of up to 15Hz (at 16Hz and 32Hz settings) for the temperature data ouput and up to 20Hz (at 32Hz setting) for the normalized data output
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[in] ref_rate Refresh rate value between @link MLX90642_REF_RATE_2HZ @endlink and @link MLX90642_REF_RATE_32HZ @endlink
 *
 * @retval 0 Refresh rate successfully set
 * @retval <0 Error setting the refresh rate
 *
 */
int MLX90642_SetRefreshRate(uint8_t slaveAddr, uint16_t ref_rate);

/** Get the emissivity used by the MLX90642 device to compensate the data
 * @note The emissivity value is scaled by 2^14 (0x4000 corresponds to emissivity 1.0)
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[out] emissivity Pointer to where the emissivity is stored
 *
 * @retval Emissivity * 2^14
 * @retval <0 Error while getting the emissivity
 *
 */
int MLX90642_GetEmissivity(uint8_t slaveAddr, int16_t *emissivity);

/** Set the emissivity used by the MLX90642 device to compensate the data
 * @note The emissivity value must be scaled by 2^14 (emissivity 1.0 corresponds to value 0x4000)
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[in] emissivity The emissivity value scaled by 2^14
 *
 * @retval 0 Emissivity successfully set
 * @retval <0 Error setting the emissivity
 *
 */
int MLX90642_SetEmissivity(uint8_t slaveAddr, int16_t emissivity);

/** Get the mode of the MLX90642 device I2C
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval = @link MLX90642_I2C_MODE_FM_PLUS @endlink FM+ mode is enabled
 * @retval = @link MLX90642_I2C_MODE_FM @endlink FM+ mode is disabled
 * @retval <0 Error while getting the MLX90642 I2C mode
 *
 */
int MLX90642_GetI2CMode(uint8_t slaveAddr);

/** Set the mode of the MLX90642 device I2C
 * @note Enable/Disable FM+ mode
 * @note For more details refer to the MLX90642 datasheet
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[in] i2c_mode MLX90642 I2C mode
 *
 * @retval <0 Error setting the MLX90642 I2C mode
 *
 */
int MLX90642_SetI2CMode(uint8_t slaveAddr, uint8_t i2c_mode);

/** Get the status of the SDA current limit of MLX90642 device I2C
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval = @link MLX90642_I2C_SDA_CUR_LIMIT_ON @endlink Current limit of SDA is enabled
 * @retval = @link MLX90642_I2C_SDA_CUR_LIMIT_OFF @endlink Current limit of SDA is disabled
 * @retval <0 Error reading the MLX90642 I2C configuration register
 *
 */
int MLX90642_GetSDALimitState(uint8_t slaveAddr);

/** Control the SDA current limit of MLX90642 device I2C
 * @note Enable/Disable SDA current limit
 * @note For more details refer to the MLX90642 datasheet
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[in] sda_limit_state MLX90642 SDA current limit state - @link MLX90642_I2C_SDA_CUR_LIMIT_OFF @endlink or @link MLX90642_I2C_SDA_CUR_LIMIT_ON @endlink
 *
 * @retval <0 Error controlling the MLX90642 SDA current limit
 *
 */
int MLX90642_SetSDALimitState(uint8_t slaveAddr, uint8_t sda_limit_state);

/** Get the threshold level reference of MLX90642 device I2C
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval = @link MLX90642_I2C_LEVEL_VDD @endlink The level for both I2C lines is VDD
 * @retval = @link MLX90642_I2C_LEVEL_1P8 @endlink The level for both I2C lines is 1.8V
 * @retval <0 Error reading the MLX90642 I2C configuration register
 *
 */
int MLX90642_GetI2CLevel(uint8_t slaveAddr);

/** Set the threshold level reference of MLX90642 device I2C
 * @note Select VDD or 1.8V
 * @note For more details refer to the MLX90642 datasheet
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[in] i2c_level MLX90642 SDA current limit state - @link MLX90642_I2C_LEVEL_VDD @endlink or @link MLX90642_I2C_LEVEL_1P8 @endlink
 *
 * @retval <0 Error setting th I2C threshold level reference
 *
 */
int MLX90642_SetI2CLevel(uint8_t slaveAddr, uint8_t i2c_level);

/** Set a new I2C slave address for the MLX90642 device
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[in] new_slaveAddr New I2C slave address to be set
 *
 * @retval <0 Error setting the MLX90642 I2C slave address
 *
 */
int MLX90642_SetI2CSlaveAddress(uint8_t slaveAddr, uint8_t new_slaveAddr);

/** Set the reflected temperature that is being used for emissivity compensations by the MLX90642
 * @note If the emissivity is <1, that means the object is reflecting the surroinding temperature
 * @note By default MLX90642 is using its sensor temperature (Ts) minus 9°C.
 * @note If the object's ambient temperature is known, for better accuracy, it can be loaded into the MLX90642
 * @note This temperature will be used untill a new input or a reset
 * @note After a reset, the MLX90642 reverts back to using Ts-9
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[in] tr The reflected temperature in centicelsius (25.12°C corresponds to 2512)
 *
 * @retval  0 Reflected temperature successfully set
 * @retval <0 Error setting the reflected temperature
 *
 */
int MLX90642_SetTreflected(uint8_t slaveAddr, int16_t tr);

/** Get progress of the MLX90642 device ongoing measurement
 * @note The value is an integer number from 0 to 100 and represents the progress in %
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval Measurement progress in %
 * @retval <0 Error getting the progress bar value
 *
 */
int MLX90642_GetProgress(uint8_t slaveAddr);

/** Check if the device is busy
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval @link MLX90642_YES @endlink The device is busy
 * @retval @link MLX90642_NO @endlink The device is not busy
 * @retval <0 Error getting busy flag status
 *
 */
int MLX90642_IsDeviceBusy(uint8_t slaveAddr);

/** Check if the image data is ready for read-out
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval @link MLX90642_YES @endlink The data is ready for read-out
 * @retval @link MLX90642_NO @endlink The data is not ready for read-out
 * @retval <0 Error getting the ready flag status
 *
 */
int MLX90642_IsDataReady(uint8_t slaveAddr);

/** Clear the data ready flag
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval 0 The data ready flag is cleared
 * @retval 1 The data ready flag is still set
 * @retval <0 Error clearing the ready flag
 *
 */
int MLX90642_ClearDataReady(uint8_t slaveAddr);

/** Check if the image data read window is open
 * @note During the read window it is guaranteed that at I2C frequency of 1MHz, the image data that is being read-out will be from the same frame
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval @link MLX90642_YES @endlink The data is ready for read-out
 * @retval @link MLX90642_NO @endlink The data is not ready for read-out
 * @retval <0 Error getting the read window status
 *
 */
int MLX90642_IsReadWindowOpen(uint8_t slaveAddr);

/** Initializes the MLX90642 device. Starts a new measurement and waits for new image data to be ready
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval 0 The device is initialized and new data is ready for read-out
 * @retval <0 Error initializing the device
 *
 */
int MLX90642_Init(uint8_t slaveAddr);

/** Start a new measurement
 * @note When in step mode, this function will start the new measurement. When in continuous mode, this command will syncronize the measurement by stopping the ongoing measurement and starting a new measurement
 * @note For more details refer to the MLX90642 datasheet
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval 0 The measurement is started/synchronized
 * @retval <0 Error while executing the start/sync command
 *
 */
int MLX90642_StartSync(uint8_t slaveAddr);

/** Start a new measurement, wait for the new data to be available and store the new data in the specified array
 * @note When in step mode, this function will start the new measurement. When in continuous mode, this command will syncronize the measurement by stopping the ongoing measurement and starting a new measurement
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[out] pixVal Pointer to where the image data is stored
 *
 * @retval 0 The image is read-out successfully
 * @retval <0 Error while runnning the new measurement
 *
 */
int MLX90642_MeasureNow(uint8_t slaveAddr, uint16_t *pixVal);

/** Get the calculated image from the MLX90642 device
 * @note The image will contain temperature data or normalized data depending on the output format set
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[out] pixVal Pointer to where the image data is stored
 *
 * @retval 0 The image is read-out successfully
 * @retval <0 Error while getting the image
 *
 */
int MLX90642_GetImage(uint8_t slaveAddr, uint16_t *pixVal);

/** Get the full frame data - raw IR data, aux data and calculated image from the MLX90642 device
 * @note The image will contain temperature data or normalized data depending on the output format set
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[out] aux Pointer to where the aux data is stored
 * @param[out] rawpix Pointer to where the raw IR data is stored
 * @param[out] pixVal Pointer to where the image data is stored
 *
 * @retval 0 The full frame data is read-out successfully
 * @retval <0 Error while getting the full frame data
 *
 */
int MLX90642_GetFrameData(uint8_t slaveAddr, uint16_t *aux, uint16_t *rawpix, uint16_t *pixVal);

/** Puts the MLX90642 device in low power consumption mode
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval 0 The device is in sleep mode
 * @retval <0 Error putting the device in sleep mode
 *
 */
int MLX90642_GotoSleep(uint8_t slaveAddr);

#endif
