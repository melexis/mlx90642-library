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
#include <MLX90642.h>

int MLX90642_GetID(uint8_t slaveAddr, uint16_t *mlxid)
{

    return MLX90642_I2CRead(slaveAddr, MLX90642_ID1_ADDR, MLX90642_NUMBER_OF_ID_WORDS, mlxid);

}

int MLX90642_GetFWver(uint8_t slaveAddr, uint8_t *fwver)
{

    uint16_t data[2];
    int status = MLX90642_I2CRead(slaveAddr, MLX90642_FW_VER_ADDRESS1, MLX90642_NUMBER_OF_FWVER_WORDS, data);

    fwver[0] = MLX90642_MS_BYTE(data[0]);
    fwver[1] = MLX90642_LS_BYTE(data[1]);
    fwver[2] = MLX90642_MS_BYTE(data[1]);

    return status;
}

int MLX90642_GetMeasMode(uint8_t slaveAddr)
{

    uint16_t data;
    int status = MLX90642_I2CRead(slaveAddr, MLX90642_APPLICATION_CONFIG_ADDRESS, 1, &data);
    if(status < 0)
        return status;

    status = data & MLX90642_MEAS_MODE_MASK;

    return status;
}

int MLX90642_SetMeasMode(uint8_t slaveAddr, uint16_t meas_mode)
{

    uint16_t data;
    int status = 0;

    if((meas_mode != MLX90642_CONT_MEAS_MODE) && (meas_mode != MLX90642_STEP_MEAS_MODE))
        return -MLX90642_INVAL_VAL_ERR;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_APPLICATION_CONFIG_ADDRESS, 1, &data);
    if(status < 0)
        return status;

    data &= ~MLX90642_MEAS_MODE_MASK;
    data |= meas_mode;

    status = MLX90642_Config(slaveAddr, MLX90642_APPLICATION_CONFIG_ADDRESS, data);

    MLX90642_Wait_ms(MLX90642_EE_WRITE_TIME);

    return status;
}

int MLX90642_GetOutputFormat(uint8_t slaveAddr)
{

    uint16_t data;
    int status = MLX90642_I2CRead(slaveAddr, MLX90642_APPLICATION_CONFIG_ADDRESS, 1, &data);
    if(status < 0)
        return status;

    status = data & MLX90642_OUTPUT_FORMAT_MASK;

    return status;
}

int MLX90642_SetOutputFormat(uint8_t slaveAddr, uint16_t output_format)
{

    uint16_t data;
    int status = 0;

    if((output_format != MLX90642_TEMPERATURE_OUTPUT) && (output_format != MLX90642_NORMALIZED_DATA_OUTPUT))
        return -MLX90642_INVAL_VAL_ERR;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_APPLICATION_CONFIG_ADDRESS, 1, &data);
    if(status < 0)
        return status;

    data &= ~MLX90642_OUTPUT_FORMAT_MASK;
    data |= output_format;

    status = MLX90642_Config(slaveAddr, MLX90642_APPLICATION_CONFIG_ADDRESS, data);

    MLX90642_Wait_ms(MLX90642_EE_WRITE_TIME);

    return status;
}

int MLX90642_GetRefreshRate(uint8_t slaveAddr)
{

    uint16_t data;
    int status = MLX90642_I2CRead(slaveAddr, MLX90642_REFRESH_RATE_ADDRESS, 1, &data);
    if(status < 0)
        return status;

    status = data & MLX90642_REFRESH_RATE_MASK;

    if(status < MLX90642_REF_RATE_2HZ)
        return MLX90642_REF_RATE_2HZ;

    return status;
}

int MLX90642_SetRefreshRate(uint8_t slaveAddr, uint16_t ref_rate)
{

    uint16_t data;
    int status = 0;

    if((ref_rate < MLX90642_REF_RATE_2HZ) || (ref_rate > MLX90642_REF_RATE_32HZ))
        return -MLX90642_INVAL_VAL_ERR;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_REFRESH_RATE_ADDRESS, 1, &data);
    if(status < 0)
        return status;

    data &= ~MLX90642_REFRESH_RATE_MASK;
    data |= ref_rate;

    status = MLX90642_Config(slaveAddr, MLX90642_REFRESH_RATE_ADDRESS, data);
    MLX90642_Wait_ms(MLX90642_EE_WRITE_TIME);

    return status;
}

/** Reads the refresh rate setting and calculates the expected refresh time
 * @note The time may vary due to oscillator variations
 *
 * @param[in] slaveAddr I2C slave address of the device
 *
 * @retval >=0 Expected refresh time in ms
 * @retval <0 Error while getting the refresh time
 *
 */
int MLX90642_GetRefreshTime(uint8_t slaveAddr)
{

    uint16_t ref_time_ms = MLX90642_REF_TIME;
    int status = 0;

    status = MLX90642_GetRefreshRate(slaveAddr);
    if(status < 0)
        return status;

    ref_time_ms >>= status;

    return (int16_t)ref_time_ms;

}

int MLX90642_GetEmissivity(uint8_t slaveAddr, int16_t *emissivity)
{

    uint16_t data;
    int status;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_EMISSIVITY_ADDRESS, 1, &data);
    if(data == 0)
        data = 0x4000;

    *emissivity = (int16_t)data;

    return status;
}

int MLX90642_SetEmissivity(uint8_t slaveAddr, int16_t emissivity)
{

    int status = MLX90642_Config(slaveAddr, MLX90642_EMISSIVITY_ADDRESS, (uint16_t)emissivity);
    MLX90642_Wait_ms(MLX90642_EE_WRITE_TIME);

    return status;
}

int MLX90642_GetI2CMode(uint8_t slaveAddr)
{

    uint16_t data;
    int status = MLX90642_I2CRead(slaveAddr, MLX90642_I2C_CONFIG_ADDRESS, 1, &data);
    if(status >= 0)
        status = data & MLX90642_I2C_MODE_MASK;

    return status;
}

int MLX90642_SetI2CMode(uint8_t slaveAddr, uint8_t i2c_mode)
{

    uint16_t data;
    int status;

    if((i2c_mode != MLX90642_I2C_MODE_FM) && (i2c_mode != MLX90642_I2C_MODE_FM_PLUS))
        return -MLX90642_INVAL_VAL_ERR;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_I2C_CONFIG_ADDRESS, 1, &data);
    if(status < 0)
        return status;

    data &= ~MLX90642_I2C_MODE_MASK;
    data |= i2c_mode;

    status = MLX90642_Config(slaveAddr, MLX90642_I2C_CONFIG_ADDRESS, data);
    MLX90642_Wait_ms(MLX90642_EE_WRITE_TIME);

    return status;

}

int MLX90642_GetSDALimitState(uint8_t slaveAddr)
{

    uint16_t data;
    int status = MLX90642_I2CRead(slaveAddr, MLX90642_I2C_CONFIG_ADDRESS, 1, &data);
    if(status >= 0)
        status = data & MLX90642_I2C_SDA_CUR_LIMIT_MASK;

    return status;
}

int MLX90642_SetSDALimitState(uint8_t slaveAddr, uint8_t sda_limit_state)
{

    uint16_t data;
    int status;

    if((sda_limit_state != MLX90642_I2C_SDA_CUR_LIMIT_OFF) && (sda_limit_state != MLX90642_I2C_SDA_CUR_LIMIT_ON))
        return -MLX90642_INVAL_VAL_ERR;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_I2C_CONFIG_ADDRESS, 1, &data);
    if(status < 0)
        return status;

    data &= ~MLX90642_I2C_SDA_CUR_LIMIT_MASK;
    data |= sda_limit_state;

    status = MLX90642_Config(slaveAddr, MLX90642_I2C_CONFIG_ADDRESS, data);
    MLX90642_Wait_ms(MLX90642_EE_WRITE_TIME);

    return status;

}

int MLX90642_GetI2CLevel(uint8_t slaveAddr)
{

    uint16_t data;
    int status = MLX90642_I2CRead(slaveAddr, MLX90642_I2C_CONFIG_ADDRESS, 1, &data);
    if(status >= 0)
        status = data & MLX90642_I2C_LEVEL_MASK;

    return status;
}

int MLX90642_SetI2CLevel(uint8_t slaveAddr, uint8_t i2c_level)
{

    uint16_t data;
    int status;

    if((i2c_level != MLX90642_I2C_LEVEL_VDD) && (i2c_level != MLX90642_I2C_LEVEL_1P8))
        return -MLX90642_INVAL_VAL_ERR;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_I2C_CONFIG_ADDRESS, 1, &data);
    if(status < 0)
        return status;

    data &= ~MLX90642_I2C_LEVEL_MASK;
    data |= i2c_level;

    status = MLX90642_Config(slaveAddr, MLX90642_I2C_CONFIG_ADDRESS, data);
    MLX90642_Wait_ms(MLX90642_EE_WRITE_TIME);

    return status;

}

int MLX90642_SetI2CSlaveAddress(uint8_t slaveAddr, uint8_t new_slaveAddr)
{

    uint16_t data;
    int status;

    if((new_slaveAddr > SA_90642_MAX) || (new_slaveAddr < SA_90642_MIN))
        return -MLX90642_INVAL_VAL_ERR;

    data = (uint16_t)new_slaveAddr;

    status = MLX90642_Config(slaveAddr, MLX90642_I2C_SA_ADDRESS, data);
    MLX90642_Wait_ms(MLX90642_EE_WRITE_TIME);

    return status;
}

int MLX90642_SetTreflected(uint8_t slaveAddr, int16_t tr)
{

    return MLX90642_Config(slaveAddr, MLX90642_REFLECTED_TEMP_ADDRESS, (uint16_t)tr);

}

int MLX90642_GetProgress(uint8_t slaveAddr)
{

    uint16_t data;
    int status;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_PROGRESS_DATA_ADDRESS, 1, &data);
    if(status >= 0)
        status = data;

    return status;
}

int MLX90642_IsDeviceBusy(uint8_t slaveAddr)
{

    uint16_t data;
    int status;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_FLAGS_ADDRESS, 1, &data);
    if(status >= 0)
        status = data & MLX90642_FLAGS_BUSY_MASK;

    return status;
}

int MLX90642_IsDataReady(uint8_t slaveAddr)
{

    uint16_t data;
    int status;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_FLAGS_ADDRESS, 1, &data);
    if(status >= 0) {
        status = data & MLX90642_FLAGS_READY_MASK;
        status >>= MLX90642_FLAGS_READY_SHIFT;
    }

    return status;
}

int MLX90642_ClearDataReady(uint8_t slaveAddr)
{

    uint16_t data;
    int status;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_TO_DATA_ADDRESS, 1, &data);
    if(status < 0)
        return status;

    return MLX90642_IsDataReady(slaveAddr);

}

int MLX90642_IsReadWindowOpen(uint8_t slaveAddr)
{

    int status;

    status = MLX90642_IsDataReady(slaveAddr);
    if(status != MLX90642_YES)
        return status;

    status = MLX90642_IsDeviceBusy(slaveAddr);
    if(status < 0)
        return status;

    if(status != MLX90642_NO)
        return MLX90642_NO;


    return MLX90642_YES;
}

int MLX90642_Init(uint8_t slaveAddr)
{

    uint16_t ref_time;
    int status;
    int poll_tries;

    status = MLX90642_GetRefreshTime(slaveAddr);
    if(status < 0)
        return status;

    ref_time = (uint16_t)status;

    status = MLX90642_ClearDataReady(slaveAddr);
    if(status !=0)
        return -MLX90642_INVAL_VAL_ERR;

    status = MLX90642_StartSync(slaveAddr);
    if(status < 0)
        return status;

    MLX90642_Wait_ms(ref_time);

    for(poll_tries=0; poll_tries<MLX90642_MAX_POLL_TRIES; poll_tries++) {

        MLX90642_Wait_ms(MLX90642_POLL_TIME_MS);
        status = MLX90642_IsDataReady(slaveAddr);
        if(status < 0)
            return status;

        if(status == MLX90642_YES)
            break;
    }

    if(poll_tries == MLX90642_MAX_POLL_TRIES)
        return -MLX90642_TIMEOUT_ERR;

    return 0;

}

int MLX90642_StartSync(uint8_t slaveAddr)
{

    return MLX90642_I2CCmd(slaveAddr, MLX90642_START_SYNC_MEAS_CMD);

}

int MLX90642_MeasureNow(uint8_t slaveAddr, uint16_t *pixVal)
{

    uint16_t ref_time;
    int status;
    int poll_tries;

    status = MLX90642_GetRefreshTime(slaveAddr);
    if(status < 0)
        return status;

    ref_time = (uint16_t)status;

    status = MLX90642_ClearDataReady(slaveAddr);
    if(status !=0)
        return -MLX90642_INVAL_VAL_ERR;

    status = MLX90642_StartSync(slaveAddr);
    if(status < 0)
        return status;

    MLX90642_Wait_ms(ref_time);

    for(poll_tries=0; poll_tries<MLX90642_MAX_POLL_TRIES; poll_tries++) {

        MLX90642_Wait_ms(MLX90642_POLL_TIME_MS);
        status = MLX90642_IsDataReady(slaveAddr);
        if(status < 0)
            return status;

        if(status == MLX90642_YES)
            break;
    }

    if(poll_tries == MLX90642_MAX_POLL_TRIES)
        return -MLX90642_TIMEOUT_ERR;

    status = MLX90642_GetImage(slaveAddr, pixVal);

    return status;

}

int MLX90642_GetImage(uint8_t slaveAddr, uint16_t *pixVal)
{

    return MLX90642_I2CRead(slaveAddr, MLX90642_TO_DATA_ADDRESS, MLX90642_TOTAL_NUMBER_OF_PIXELS, pixVal);

}

int MLX90642_GetFrameData(uint8_t slaveAddr, uint16_t *aux, uint16_t *rawpix, uint16_t *pixVal)
{

    int status;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_AUX_DATA_ADDRESS, MLX90642_TOTAL_NUMBER_OF_AUX, aux);
    if(status < 0)
        return status;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_IR_DATA_ADDRESS, MLX90642_TOTAL_NUMBER_OF_PIXELS, rawpix);
    if(status < 0)
        return status;

    status = MLX90642_I2CRead(slaveAddr, MLX90642_TO_DATA_ADDRESS, MLX90642_TOTAL_NUMBER_OF_PIXELS + 1, pixVal);

    return status;

}

int MLX90642_GotoSleep(uint8_t slaveAddr)
{

    return MLX90642_I2CCmd(slaveAddr, MLX90642_SLEEP_CMD);

}
