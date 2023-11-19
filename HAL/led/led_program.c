#include "../../LIB/std_types.h"
#include "../../MCAL/gpio/gpio_interface.h"
#include "led_interface.h"


enu_ledErrorState_t LED_init(st_led_t *st_a_led)
{
    enu_ledErrorState_t enu_a_functionRet = LED_SUCCES;
    if (st_a_led != NULL)
    {
       st_gpioPinConfig_t st_a_ledPin = 
        {
        st_a_led->ledPort,
        st_a_led->ledPin,
        GPIO_PIN_OUTPUT,
        st_a_led->ledState,
        GPIO_PIN_TYPE,
        GPIO_PIN_DRIVE_8MA,
        GPIO_PIN_NO_PULL,
        GPIO_NO_INTERRUPT
        };
        if (GPIO_init(&st_a_ledPin) != GPIO_SUCCESS)
        {
           enu_a_functionRet = LED_NOT_SUCCES;
        }
        else
        {
            /*do nothing*/
        }
    }
    else
    {
        enu_a_functionRet = LED_INVALID_STATE;
    }
    return enu_a_functionRet;
}
enu_ledErrorState_t LED_on(st_led_t *st_a_led)
{
    enu_ledErrorState_t enu_a_functionRet = LED_SUCCES;
    if (st_a_led != NULL)
    {
       st_gpioPinConfig_t st_a_ledPin = 
        {
        st_a_led->ledPort,
        st_a_led->ledPin,
        GPIO_PIN_OUTPUT,
        st_a_led->ledState,
        GPIO_PIN_TYPE,
        GPIO_PIN_DRIVE_8MA,
        GPIO_PIN_NO_PULL,
        GPIO_NO_INTERRUPT
        };
        if (GPIO_setPinValue(&st_a_ledPin,GPIO_HIGH) != GPIO_SUCCESS)
        {
           enu_a_functionRet = LED_NOT_SUCCES;
        }
        else
        {
            /*do nothing*/
        }
        
        
    }
    else
    {
        enu_a_functionRet = LED_INVALID_STATE;
    }
    return enu_a_functionRet;
}
enu_ledErrorState_t LED_off(st_led_t *st_a_led)
{
     enu_ledErrorState_t enu_a_functionRet = LED_SUCCES;
    if (st_a_led != NULL)
    {
       st_gpioPinConfig_t st_a_ledPin = 
        {
        st_a_led->ledPort,
        st_a_led->ledPin,
        GPIO_PIN_OUTPUT,
        st_a_led->ledState,
        GPIO_PIN_TYPE,
        GPIO_PIN_DRIVE_8MA,
        GPIO_PIN_NO_PULL,
        GPIO_NO_INTERRUPT
        };
        if (GPIO_setPinValue(&st_a_ledPin,GPIO_LOW) != GPIO_SUCCESS)
        {
           enu_a_functionRet = LED_NOT_SUCCES;
        }
        else
        {
            /*do nothing*/
        }
        
        
    }
    else
    {
        enu_a_functionRet = LED_INVALID_STATE;
    }
    return enu_a_functionRet;
}
enu_ledErrorState_t LED_toggle(st_led_t *st_a_led)
{
     enu_ledErrorState_t enu_a_functionRet = LED_SUCCES;
    if (st_a_led != NULL)
    {
       st_gpioPinConfig_t st_a_ledPin = 
        {
        st_a_led->ledPort,
        st_a_led->ledPin,
        GPIO_PIN_OUTPUT,
        st_a_led->ledState,
        GPIO_PIN_TYPE,
        GPIO_PIN_DRIVE_8MA,
        GPIO_PIN_NO_PULL,
        GPIO_NO_INTERRUPT
        };
        if (GPIO_togglePin(&st_a_ledPin) != GPIO_SUCCESS)
        {
           enu_a_functionRet = LED_NOT_SUCCES;
        }
        else
        {
            /*do nothing*/
        }
        
        
    }
    else
    {
        enu_a_functionRet = LED_INVALID_STATE;
    }
    return enu_a_functionRet;
}