/*this project use TivaWare API functions to set up the clock, and to configure and write to the GPIO port to blink LEDs on the evaluation board.
the two GPIO pins PN0 and PN1 are connected to the D1 and D2 LEDs on the board 
*/



#include <stdint.h>
#include <stdbool.h>

// Macros defining the memory map of the Tiva C Series device. This includes defines such as peripheral base address locations such as GPIO_PORTN_BASE. 
#include "inc/hw_memmap.h"

#include "inc/hw_types.h"   // Defines common types and macros 

// Defines and macros for System Control API of DriverLib. This includes API functions such as SysCtlClockSet and SysCtlClockGet
#include "driverlib/sysctl.h"

//Defines and macros for GPIO API of DriverLib. This includes API functions such as GPIOPinTypeGPIOOutput and GPIOPinWrite. 
#include "driverlib/gpio.h"

// Creates an integer variable called ui8PinData and initializes it to 1. This will be used to light the two user LEDs one at a time. 
uint8_t ui8PinData=1;     

int main(void)
{
// Configure the system clock to run using a 25MHz crystal on the main oscillator, driving the PLL at 480MHz. the system clock we use will be 120MHz
	SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

// enable the clock for the GPION peripheral. 
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	
// configure the two GPIO pins connected to the D1 and D2 LEDs as outputs
	GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0|GPIO_PIN_1);
// write zero to GPIO pins PN0 and PN1
	GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0|GPIO_PIN_1, 0x00);

	while(1)
	{
		GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, ui8PinData);
		SysCtlDelay(10000000); // delay function .the count parameter is the loop count, Each loop is 3 CPU cycles. 
		if(ui8PinData==4) {ui8PinData=1;} else {ui8PinData=ui8PinData*2;}
	}
}
