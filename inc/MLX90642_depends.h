/**
 * @copyright (C) 2025 Melexis N.V.
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

/** MLX90642 block write I2C command
 * @note Sends multiple bytes on the I2C bus. This function is used by the Config, Command, Sleep and Wake-up functions
 *
 * @param[in] slaveAddr I2C slave address of the device
 * @param[in] buffer Pointer to the buffer that contains the data to send
 * @param[in] bytesNum Number of bytes to send
 *
 * @retval  <0 Error while sending the data
 *
 */

int MLX90642_I2CWrite(uint8_t slaveAddr, const uint8_t *buffer, uint8_t bytesNum);

/** Delay function
 *
 * @param[in] wait_ms Time to wait in milliseconds
 *
 */
void MLX90642_Wait_ms(uint16_t time_ms);

#endif
