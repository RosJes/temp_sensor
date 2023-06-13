 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

int16_t temperatureConvert(uint16_t data);
//======================================================
int16_t temperatureConvert(uint16_t data)
{
	uint16_t sigrow_offset = SIGROW.TEMPSENSE1 /2; //TEMPSENSE1/2
	uint16_t sigrow_slope = SIGROW.TEMPSENSE0 * 2;//TEMPSENSE0*2
	int32_t temp;
	/* Clear the interrupt flag by reading the result (ADC0.RES) */
	temp = sigrow_offset - data;
	/* Result will overflow 16-bit variable */
	temp *= sigrow_slope;
	/* Add 4096/2 to get correct rounding on division below */
	temp += 0x0800;
	/* Round off to nearest degree in Kelvin, by dividing with 2^12 (4096) */
	temp >>= 12;
	/* Convert from Kelvin to Celsius (0 Kelvin - 273.15 = -273.1°C) */
	return temp - 273;
}

int main(void)
{
    SYSTEM_Initialize();


    int16_t temp_C;
    uint16_t adcVal;
  
    
    while (1)
    {
	    /* Read the conversion result */
	    adcVal = ADC0_GetConversion(ADC_MUXPOS_TEMPSENSE_gc);
	    /* Convert the ADC result in degrees C */
	    temp_C = temperatureConvert(adcVal);
		printf("%d",temp_C);
		
    }
}