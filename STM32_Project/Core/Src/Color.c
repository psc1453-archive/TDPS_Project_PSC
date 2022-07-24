//
// Created by 彭世辰 on 2021/5/29.
//

#include "Color.h"


/*******************************************************************************
 * @brief Writes data into TCS34725 registers, starting from the selected
 *        register address pointer.
 *
 * @param subAddr - The selected register address pointer.
 * @param dataBuffer - Pointer to a buffer storing the transmission data.
 * @param bytesNumber - Number of bytes that will be sent.
 *
 * @return None.
*******************************************************************************/
void TCS34725_Write(TCS34725* tcs34725, uint8_t subAddr, uint8_t* dataBuffer, uint8_t bytesNumber)
{
    uint8_t sendBuffer[10] = {0, };
    uint8_t byte = 0;

    sendBuffer[0] = subAddr | TCS34725_COMMAND_BIT;
    for(byte = 1; byte <= bytesNumber; byte++)
    {
        sendBuffer[byte] = dataBuffer[byte - 1];
    }
    HAL_I2C_Master_Transmit(tcs34725->i2c_port, TCS34725_ADDRESS<<1, sendBuffer, bytesNumber + 1, 10);
}
/*******************************************************************************
 * @brief Reads data from TCS34725 registers, starting from the selected
 *        register address pointer.
 *
 * @param subAddr - The selected register address pointer.
 * @param dataBuffer - Pointer to a buffer that will store the received data.
 * @param bytesNumber - Number of bytes that will be read.
 *
 * @return None.
*******************************************************************************/
void TCS34725_Read(TCS34725* tcs34725, uint8_t subAddr, uint8_t* dataBuffer, uint8_t bytesNumber)
{
    subAddr |= TCS34725_COMMAND_BIT;

    HAL_I2C_Master_Transmit(tcs34725->i2c_port, TCS34725_ADDRESS<<1, &subAddr, 1, 10);
    HAL_I2C_Master_Receive(tcs34725->i2c_port, TCS34725_ADDRESS<<1, dataBuffer, bytesNumber, 10);
}
/*******************************************************************************
 * @brief TCS34725设置积分时间
 *
 * @return None
*******************************************************************************/
void TCS34725_SetIntegrationTime(TCS34725* tcs34725, uint8_t time)
{
    TCS34725_Write(tcs34725, TCS34725_ATIME, &time, 1);
}
/*******************************************************************************
 * @brief TCS34725设置增益
 *
 * @return None
*******************************************************************************/
void TCS34725_SetGain(TCS34725* tcs34725, uint8_t gain)
{
    TCS34725_Write(tcs34725, TCS34725_CONTROL, &gain, 1);
}
/*******************************************************************************
 * @brief TCS34725使能
 *
 * @return None
*******************************************************************************/
void TCS34725_Enable(TCS34725* tcs34725)
{
    uint8_t cmd = TCS34725_ENABLE_PON;

    TCS34725_Write(tcs34725, TCS34725_ENABLE, &cmd, 1);
    cmd = TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN;
    TCS34725_Write(tcs34725, TCS34725_ENABLE, &cmd, 1);
    //delay_us(600000);//delay_ms(3);//延时应该放在设置AEN之后
}
/*******************************************************************************
 * @brief TCS34725失能
 *
 * @return None
*******************************************************************************/
void TCS34725_Disable(TCS34725* tcs34725)
{
    uint8_t cmd = 0;

    TCS34725_Read(tcs34725,TCS34725_ENABLE, &cmd, 1);
    cmd = cmd & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
    TCS34725_Write(tcs34725,TCS34725_ENABLE, &cmd, 1);
}
/*******************************************************************************
 * @brief TCS34725初始化
 *
 * @return ID - ID寄存器中的值
*******************************************************************************/
uint8_t TCS34725_Init(TCS34725* tcs34725, I2C_HandleTypeDef* color_i2c)
{
    tcs34725->i2c_port = color_i2c;

    uint8_t id=0;

    TCS34725_Read(tcs34725, TCS34725_ID, &id, 1);  //TCS34725 的 ID 是 0x44 可以根据这个来判断是否成功连接,0x4D是TCS34727;
    if(id==0x4D | id==0x44)
    {
        TCS34725_SetIntegrationTime(tcs34725, TCS34725_INTEGRATIONTIME_50MS);
        TCS34725_SetGain(tcs34725, TCS34725_GAIN_1X);
        TCS34725_Enable(tcs34725);
        return 1;
    }
    return 0;
}
/*******************************************************************************
 * @brief TCS34725获取单个通道数据
 *
 * @return data - 该通道的转换值
*******************************************************************************/
uint16_t TCS34725_GetChannelData(TCS34725* tcs34725, uint8_t reg)
{
    uint8_t tmp[2] = {0,0};
    uint16_t data;

    TCS34725_Read(tcs34725, reg, tmp, 2);
    data = (tmp[1] << 8) | tmp[0];

    return data;
}
/*******************************************************************************
 * @brief TCS34725获取各个通道数据
 *
 * @return 1 - 转换完成，数据可用
 *   	   0 - 转换未完成，数据不可用
*******************************************************************************/
uint8_t TCS34725_GetRawData(TCS34725* tcs34725, COLOR_RGBC_RAW *rgbc)
{
    uint8_t status = TCS34725_STATUS_AVALID;

    TCS34725_Read(tcs34725, TCS34725_STATUS, &status, 1);

    if(status & TCS34725_STATUS_AVALID)
    {
        rgbc->c = TCS34725_GetChannelData(tcs34725, TCS34725_CDATAL);
        rgbc->r = TCS34725_GetChannelData(tcs34725, TCS34725_RDATAL);
        rgbc->g = TCS34725_GetChannelData(tcs34725, TCS34725_GDATAL);
        rgbc->b = TCS34725_GetChannelData(tcs34725, TCS34725_BDATAL);
        return 1;
    }
    return 0;
}

void TCS34725_RAW_To_RGB(COLOR_RGBC_RAW *rgbc, COLOR_RGB *rgb)
{
    uint8_t r = (rgbc->r*255)/(rgbc->c);
    uint8_t g = (rgbc->g*255)/(rgbc->c);
    uint8_t b = (rgbc->b*255)/(rgbc->c);

    rgb->r = r;
    rgb->g = g;
    rgb->b = b;
}

/******************************************************************************/
//RGB转HSL
void TCS34725_RAW_To_HSL(COLOR_RGBC_RAW *rgbc, COLOR_HSL *hsl)
{
    uint8_t maxVal,minVal,difVal;
    uint8_t r = rgbc->r*100/rgbc->c;
    uint8_t g = rgbc->g*100/rgbc->c;
    uint8_t b = rgbc->b*100/rgbc->c;

    maxVal = max3v(r,g,b);
    minVal = min3v(r,g,b);
    difVal = maxVal-minVal;

    // Calculate brightness
    hsl->l = (maxVal+minVal)/2;   //[0-100]

    if(maxVal == minVal)// if r=g=b, grayscale
    {
        hsl->h = 0;
        hsl->s = 0;
    }
    else
    {
        // Calculate Hue
        if(maxVal==r)
        {
            if(g>=b)
                hsl->h = 60*(g-b)/difVal;
            else
                hsl->h = 60*(g-b)/difVal+360;
        }
        else
        {
            if(maxVal==g)hsl->h = 60*(b-r)/difVal+120;
            else
            if(maxVal==b)hsl->h = 60*(r-g)/difVal+240;
        }

        // Calculate saturation
        if(hsl->l<=50)hsl->s=difVal*100/(maxVal+minVal);  //[0-100]
        else
            hsl->s=difVal*100/(200-(maxVal+minVal));
    }
}

void TCS34725_RAW_To_CMYK(COLOR_RGBC_RAW *rgbc, COLOR_CMYK *cmyk)
{
    float maxVal;
    float r_temp = rgbc->r/(float)rgbc->c;
    float g_temp = rgbc->g/(float)rgbc->c;
    float b_temp = rgbc->b/(float)rgbc->c;

    maxVal = max3v(r_temp,g_temp,b_temp);

    cmyk->k = 1.0 - maxVal;

    cmyk->c = (1.0-r_temp-cmyk->k) / (1-cmyk->k);
    cmyk->m = (1.0-g_temp-cmyk->k) / (1-cmyk->k);
    cmyk->y = (1.0-b_temp-cmyk->k) / (1-cmyk->k);
}
/******************************************************************************/


