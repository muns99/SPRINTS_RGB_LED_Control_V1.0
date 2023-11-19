#include "MCAL/gpio/gpio_interface.h"
st_gpioPinConfig_t sw1 = {
            GPIO_PORTF,
            GPIO_PIN4,
            GPIO_PIN_INPUT,
            GPIO_LOW,
            GPIO_PIN_TYPE,
            GPIO_PIN_DRIVE_8MA,
            GPIO_PIN_PULLUP,
            GPIO_NO_INTERRUPT
    };
	  
st_gpioPinConfig_t red = {
        GPIO_PORTF,
        GPIO_PIN1,
        GPIO_PIN_OUTPUT,
        GPIO_LOW,
        GPIO_PIN_TYPE,
        GPIO_PIN_DRIVE_2MA,
        GPIO_PIN_NO_PULL,
        GPIO_NO_INTERRUPT
};

st_gpioPinConfig_t blue = {
        GPIO_PORTF,
        GPIO_PIN2,
        GPIO_PIN_OUTPUT,
        GPIO_LOW,
        GPIO_PIN_TYPE,
        GPIO_PIN_DRIVE_2MA,
        GPIO_PIN_NO_PULL,
        GPIO_NO_INTERRUPT
};
st_gpioPinConfig_t green = {
        GPIO_PORTF,
        GPIO_PIN3,
        GPIO_PIN_OUTPUT,
        GPIO_LOW,
        GPIO_PIN_TYPE,
        GPIO_PIN_DRIVE_2MA,
        GPIO_PIN_NO_PULL,
        GPIO_NO_INTERRUPT
};
void firstPress()
{
    GPIO_setPinValue(&red,GPIO_HIGH);
}

void secondPress()
{
    GPIO_setPinValue(&red,GPIO_LOW);
    GPIO_setPinValue(&green,GPIO_HIGH);
}

void thirdPress()
{
    GPIO_setPinValue(&green,GPIO_LOW);
    GPIO_setPinValue(&blue,GPIO_HIGH);
}

void fourthPress()
{
    GPIO_setPinValue(&red,GPIO_HIGH);
    GPIO_setPinValue(&green,GPIO_HIGH);
}

void fifthPress()
{
     GPIO_setPinValue(&red,GPIO_LOW);
    GPIO_setPinValue(&green,GPIO_LOW);
    GPIO_setPinValue(&blue,GPIO_LOW);
}

void sixthPress()
{

}
int main()
{
	 
    void(*funcPtr[])(void) = {firstPress,secondPress,thirdPress,fourthPress,fifthPress};
    GPIO_initPin(&red);
    GPIO_initPin(&blue);
    GPIO_initPin(&green);
		GPIO_initPin(&sw1);

    uint8_t sw1Value = GPIO_HIGH ;
    uint8_t counter = 0;
    
    
    while (1)
    {
        GPIO_getPinValue(&sw1,&sw1Value);
        if (sw1Value == GPIO_LOW)
        {
            counter++;
           if (counter == 6)
           {
            counter = 0;
           }
           else
           {
            funcPtr[counter - 1]();
           }
        do
        {
            for (uint32_t i = 0; i < 1000; i++)
            for (uint32_t i = 0; i < 1000; i++)
            for (uint32_t i = 0; i < 2; i++);
            GPIO_getPinValue(&sw1,&sw1Value);
        } while (sw1Value == GPIO_LOW);
        
          
           
        }

        
        
    }
    
}