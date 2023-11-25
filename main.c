#include "MCAL/gpio/gpio_interface.h"
#include "HAL/button/button_interface.h"
#include "HAL/led/led_interface.h"
st_led_t redLed = {LED_PIN1,LED_PORTF,LED_OFF};
void routine()
{
    LED_on(&redLed);
    while (1)
    {
        /* code */
    }
    
}
int main()
{
	
    st_button_t sw1 = {
        .buttonPort = BUTTON_PORTF,
        .buttonPin = BUTTON_PIN4,
        .buttonMode = BUTTON_INTERRUPT_FALLING_EDGE_MODE,
        .buttonHandler = routine
    };
    LED_init(&redLed);
    LED_on(&redLed);
    BUTTON_init(&sw1);
    BUTTON_enable(&sw1);
    
    while (1)
    {
        /* code */
    }
    
    
}