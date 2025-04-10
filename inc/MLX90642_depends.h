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
#ifndef _MLX90642_DEPENDS_H_
#define _MLX90642_DEPENDS_H_

#include <stdint.h>

/** MLX90642 block read I2C command
 * @note For more information refer to the MLX90642 datasheet
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[in] startAddress Start address for the block read
 * @param[in] nMemAddressRead Number of words to read
 * @param[out] rData Pointer to where the read data will be stored
 *
 * @retval  <0 Error while configuring the MLX90642 device
 *
 */

int MLX90642_I2CRead(uint8_t slaveAddr, uint16_t startAddress, uint16_t nMemAddressRead, uint16_t *rData);

/** MLX90642 configuration I2C command
 * @note For more information refer to the MLX90642 datasheet
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[in] writeAddress Configuration address to write to
 * @param[in] wData Data to write
 *
 * @retval  <0 Error while configuring the MLX90642 device
 *
 */
int MLX90642_Config(uint8_t slaveAddr, uint16_t writeAddress, uint16_t wData);

/** MLX90642 I2C commands send
 * @note The addressed reset, start/sync measurement and sleep commands ahsre the same I2C format. For more information refer to the MLX90642 datasheet
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[in] i2c_cmd MLX90642 I2C command to send
 *
 * @retval  <0 Error while sending the I2C command to the MLX90642 device
 *
 */
int MLX90642_I2CCmd(uint8_t slaveAddr, uint16_t i2c_cmd);

/** MLX90642 wake-up command
 * @note For more information refer to the MLX90642 datasheet
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval  <0 Error while sending the wake-up command to the MLX90642 device
 *
 */
int MLX90642_WakeUp(uint8_t slaveAddr);

/** Delay function
 *
 * @param[in] wait_ms Time to wait in milliseconds
 *
 */
void MLX90642_Wait_ms(uint16_t time_ms);

#endif
