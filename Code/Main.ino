#include <avr/io.h>
#include <util/delay.h>
#include "Register.h"
#include "Uart.h"
#include "Lcd.h"
#include "Adc.h"
#include "Dio.h"

int adc_value = 0;
int lowerLimit = 200;       // set lower limit 
int higherLimit = 500;      // set higher limit
char sw1, sw2;
enum{INCREMENT=0, DECREMENT};
char mode = INCREMENT;   // Initial mode incrementing   
char str[10];

int main()
{
    // Initialize pin D10 (PB2) as input switch(Sw1) with no pull-up resistor
    Dio_SetPinDirection(DDR_B, PB2, DIO_DIR_INPUT);
    Dio_ResetRegisterBit(PORT_D, PB2);  // Disable pull-up resistor on PB2

    // Initialize pin D11 (PB3) as input switch(Sw2) with no pull-up resistor
    Dio_SetPinDirection(DDR_B, PB3, DIO_DIR_INPUT);
    Dio_ResetRegisterBit(PORT_D, PB3);  // Disable pull-up resistor on PB3

    // Initialize pin D13 (PB5) as output for LED
    Dio_SetPinDirection(DDR_D, PB5, DIO_DIR_OUTPUT);    // Set PB5 as output
    Dio_ResetRegisterBit(PORT_B, PB5);  // Set PB5 low (LED off)

    // Initialize UART
    Uart_Init();
    Uart_SendString("Program Starts..!\n", 18);

    // Initialize ADC 
    Adc_Init();

    // Initialize and clear LCD
    LCD_Init();
    LCD_Clear();

    // display messgaes on LCD
    LCD_String_xy(0,  0, "POTN:");
    LCD_String_xy(0, 13, "OK");
    LCD_String_xy(1,  0, "LL:");
    LCD_String_xy(1, 9, "HL:");

    while(1)
    {
        // Read the current state of the switch on PB2 and PB3
        sw1 = Dio_GetPinState(PIN_B, PB2);      // read state of button PB2 
        sw2 = Dio_GetPinState(PIN_B, PB3);      // read state of button PB3

        if( sw1 == 0x01 && sw2 == 0x01)       // if both PB2, PB3 are pressed together
        {
            Uart_SendString("> Mode Changed: ", 16);

            // update buttons operating mode
            if(mode == INCREMENT){
                mode = DECREMENT;
                Uart_SendString("Dec \n", 5);
            }
            else{
                mode = INCREMENT;
                Uart_SendString("Inc \n", 5);
            }

            // wait until both are released to apply mode!
            while((Dio_GetPinState(PIN_B, PB2) && Dio_GetPinState(PIN_B, PB3)));
        }

        else if(sw1 == 0x01)     // if alone PB2 is pressed
        {
            Uart_SendString("SW1 Pressed!\n", 13);      // send UART message

            if (mode == INCREMENT)
                lowerLimit++;           // increment value by 1
            else
                lowerLimit--;           // decrement value by 1
        }

        else if(sw2 == 0x01)    // if alone PB2 is pressed
        {
            Uart_SendString("SW2 Pressed!\n", 13);

            if (mode == INCREMENT)
                higherLimit++;          // increment value by 1
            else
                higherLimit--;          // decrement value by 1
        }

        // Keep boths limits within Specifi Range [1-1023]
        if(lowerLimit < 1 )             // keep 1 as lower max limit
            lowerLimit = 1;
        if(lowerLimit > 1023)           // keep 1023 as upper max limit
            lowerLimit = 1023;
        if(higherLimit < 1 )
            higherLimit = 1;
        if(higherLimit > 1023)
            higherLimit = 1023;
        // Display Lower Limit on LCD
        sprintf(str, "%4d", lowerLimit);    // convert int value into string form
        LCD_String_xy(1,  3, str);          // send it to LCD

        // Display Higher Limit on LCD
        sprintf(str, "%4d", higherLimit);   // convert int value into string form
        LCD_String_xy(1,  12, str);         // send it to LCD

        // Display ADC Temp Value on LCD
        adc_value = Adc_ReadChannel(0);     // Obtain ADC value on Channel-0
        sprintf(str, "%4d", adc_value);     // convert adc int value into string form
        LCD_String_xy(0,  5, str);          // send it to LCD

        if(adc_value <= lowerLimit || adc_value >= higherLimit){
            Dio_SetRegisterBit(PORT_B, PB5);  // Set PB5 high (LED on)
            LCD_String_xy(0, 13, "NOK");
        }  
        else
        {
            Dio_ResetRegisterBit(PORT_B, PB5);  // Set PB5 low (LED off)
            LCD_String_xy(0, 13, "OK ");
        }

        _delay_ms(200);
    }
    return 0;
}
