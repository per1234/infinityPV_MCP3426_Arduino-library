/**************************************************************************/
/*!
    @file     infinityPV_MCP3426.h
    @author   rava (infinityPV ApS)
    @license  BSD (see license.txt)

    This is a library for all the infinityPV boards using the ADC/I2C converter
    MCP3426:
    - 1. Multiplatform LiBAT5V2A Boost
    ----> https://infinitypv.com/products/electronics

    InfinityPV makes printed organic solar cells. We invests part of our
    time and resources providing open source examples (hardware and code) to
    make easier the use of our solar cells in your projects.
    Printed organic solar cells are flexible, rollable and super light unlike
    other solar cell technologies, please visit our website to find more !

    (*)This libray is a modified version of MCP342X library which is
    protected by BSD license, Copyright 2013 by Chip Schnarel.

    @section  HISTORY

      v1.0  - First release Sep 2017
*/
/**************************************************************************/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

/*=========================================================================
    I2C ADDRESSES
    -----------------------------------------------------------------------*/
    // MCP3421, MCP3425 & MCP3426 are factory programed for any of 0x68 thru 0x6F
    #define MCP342X_DEFAULT_ADDRESS	    0x68

    // MCP3422, MCP3423, MCP3424, MCP3427 & MCP3428 addresses are controlled by address lines A0 and A1
    // each address line can be low (GND), high (VCC) or floating (FLT)
    #define MCP342X_A0GND_A1GND		0x68
    #define MCP342X_A0GND_A1FLT		0x69
    #define MCP342X_A0GND_A1VCC		0x6A
    #define MCP342X_A0FLT_A1GND		0x6B
    #define MCP342X_A0VCC_A1GND		0x6C
    #define MCP342X_A0VCC_A1FLT		0x6D
    #define MCP342X_A0VCC_A1VCC		0x6E
    #define MCP342X_A0FLT_A1VCC		0x6F
/*=========================================================================*/

/*=========================================================================
    CONVERSION MODES
    -----------------------------------------------------------------------*/
    #define MCP342X_MODE_ONESHOT	0x00
    #define MCP342X_MODE_CONTINUOUS	0x10
/*=========================================================================*/

/*=========================================================================
    CHANNELS
    -----------------------------------------------------------------------*/
    // MCP3421 & MCP3425 have only the one channel and ignore this param
    // MCP3422, MCP3423, MCP3426 & MCP3427 have two channels and treat 3 & 4 as repeats of 1 & 2 respectively
    // MCP3424 & MCP3428 have all four channels
    #define	MCP342X_CHANNEL_1	0x00
    #define	MCP342X_CHANNEL_2	0x20
    #define	MCP342X_CHANNEL_3	0x40
    #define	MCP342X_CHANNEL_4	0x60
    #define	MCP342X_CHANNEL_MASK	0x60
/*=========================================================================*/

/*=========================================================================
    SAMPLE SIZE
    -----------------------------------------------------------------------*/
    // Sample size definitions - these also affect the sampling rate
    // 12-bit has a max sample rate of 240sps
    // 14-bit has a max sample rate of  60sps
    // 16-bit has a max sample rate of  15sps
    // 18-bit has a max sample rate of   3.75sps (MCP3421, MCP3422, MCP3423, MCP3424 only)
    #define MCP342X_SIZE_12BIT	0x00
    #define MCP342X_SIZE_14BIT	0x04
    #define MCP342X_SIZE_16BIT	0x08
    #define MCP342X_SIZE_18BIT	0x0C
    #define MCP342X_SIZE_MASK	0x0C
/*=========================================================================*/

/*=========================================================================
    PROGRAMMABLE GAINS
    -----------------------------------------------------------------------*/
    #define MCP342X_GAIN_1X	0x00
    #define MCP342X_GAIN_2X	0x01
    #define MCP342X_GAIN_4X	0x02
    #define MCP342X_GAIN_8X	0x03
    #define MCP342X_GAIN_MASK 0x03
/*=========================================================================*/
/*=========================================================================
    RDY bit definition
    -----------------------------------------------------------------------*/
#define MCP342X_RDY	0x80


class MCP342X {
    public:
        MCP342X();
        MCP342X(uint8_t address);

        bool testConnection(void);

        // Set/Get the configuration bits for the ADC
      //  void configure(uint8_t config);
        void setSettingsCH1(float v_max,float RUP,float RD);
        void setSettingsCH2(float i_max,float RS1);
        uint8_t getConfigRegShdw(uint8_t channel);

	   //float getStepSize(); // returns step size based on configRegShdw

        // Start a conversion
        bool startConversion(uint8_t channel);

        // Read the ADC result
        uint8_t getResult(uint8_t channel, int16_t *data);
        uint8_t getResult(uint8_t channel, int32_t *data);
        float getCH1Voltage_V(void);
        float getCH2Current_mA(void);

        // Non-blocking Read the ADC result
        uint8_t checkforResult(uint8_t channel,int16_t *data);
        uint8_t checkforResult(uint8_t channel,int32_t *data);


    private:
        uint8_t devAddr;
        uint8_t configRegShdw_CH1=0;
        uint8_t configRegShdw_CH2=0;
        uint8_t configRegShdw_CH3=0;
        uint8_t configRegShdw_CH4=0;
        uint8_t GAIN_CH1=1;
        uint8_t GAIN_CH2=1;
        uint8_t GAIN_CH3=1;
        uint8_t GAIN_CH4=1;
        float VD_ratio=0; //voltage divider ratio in CH1
        float RS=0;       //shunt resistance in CH2 (Ohms)
	//float	stepSizeTbl[];
};