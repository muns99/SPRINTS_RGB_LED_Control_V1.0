#include "../../LIB/std_types.h"
#include "../../MCAL/gpio/gpio_interface.h"
#include "button_config.h"
#include "button_private.h"
#include "button_interface.h"

void getButtonGpioPinStruct(st_button_t *st_a_button,st_gpioPinConfig_t *st_a_buttonPin,enu_buttonErrorState_t *enu_a_functionRet)
{
    st_gpioPinConfig_t st_a_buttonPin = 
        {
            .port =  st_a_button->buttonPort,
            .pinNum = st_a_button->buttonPin,
            .pinDirection = GPIO_PIN_INPUT,
            .pinType =  GPIO_PIN_TYPE
        };
        switch (st_a_button->buttonMode)
        {
            case BUTTON_PULLUP_MODE:
            {
                st_a_buttonPin.pinPullMode = GPIO_PIN_PULLUP;
                st_a_buttonPin.pinInterruptMode = GPIO_NO_INTERRUPT;
                break;
            }
            case BUTTON_PULLDOWN_MODE:
            {
                st_a_buttonPin.pinPullMode = GPIO_PIN_PULLDOWN;
                st_a_buttonPin.pinInterruptMode = GPIO_NO_INTERRUPT;
                break;
            }
            case BUTTON_INTERRUPT_RISING_EDGE_MODE:
            {
                st_a_buttonPin.pinPullMode = GPIO_PIN_NO_PULL;
                st_a_buttonPin.pinInterruptMode = GPIO_RISING_EDGE;
                break;
            }
            case BUTTON_INTERRUPT_FALLING_EDGE_MODE:
            {
                st_a_buttonPin.pinPullMode = GPIO_PIN_NO_PULL;
                st_a_buttonPin.pinInterruptMode = GPIO_FALLING_EDGE;
                break;
            }
            case BUTTON_INTERRUPT_BOTH_EDGES_MODE:
            {
                st_a_buttonPin.pinPullMode = GPIO_PIN_NO_PULL;
                st_a_buttonPin.pinInterruptMode = GPIO_BOTH_EDGES;
                break;
            }
            default:
            {
                enu_a_functionRet = BUTTON_INVALID_STATE;
                break;
            }
        }
        
}

enu_buttonErrorState_t BUTTON_init(st_button_t *st_a_button)
{
    enu_buttonErrorState_t enu_a_functionRet = BUTTON_SUCCESS;
    if (st_a_button != NULL)
    {
        st_gpioPinConfig_t st_a_buttonPin;
        getButtonGpioPinStruct(&st_a_button,&st_a_buttonPin,&enu_a_functionRet);
        if (enu_a_functionRet == BUTTON_SUCCESS)
        {
            if (st_a_button ->buttonHandler != NULL)
            {
                enu_a_functionRet = GPIO_initPin(&st_a_buttonPin);
            }
            else
            {
                enu_a_functionRet = BUTTON_INVALID_STATE;
            }
            
            
        }
        else
        {
            enu_a_functionRet = BUTTON_INVALID_STATE;
        }
        
    }
    else
    {
        enu_a_functionRet = BUTTON_INVALID_STATE;
    }
    return enu_a_functionRet;
}


enu_buttonErrorState_t BUTTON_getButtonState(st_button_t *st_a_button,uint8_t *uint8_a_buttonState)
{
    enu_buttonErrorState_t enu_a_functionRet = BUTTON_SUCCESS;
    if (st_a_button != NULL)
    {
        if (uint8_a_buttonState != NULL)
        {
            st_gpioPinConfig_t st_a_buttonPin ;
            getButtonGpioPinStruct(st_a_button,&st_a_buttonPin,&enu_a_functionRet);
            if (enu_a_functionRet == BUTTON_SUCCESS)
            {
                enu_a_functionRet = GPIO_getPinValue(&st_a_buttonPin,uint8_a_buttonState); 
            }
            else
            {
                enu_a_functionRet = BUTTON_INVALID_STATE;
            }
            
        }
        else
        {
            enu_a_functionRet = BUTTON_INVALID_STATE;
        }     
    }
    else
    {
        enu_a_functionRet = BUTTON_INVALID_STATE;
    }
    return enu_a_functionRet;
}
enu_buttonErrorState_t BUTTON_enable(st_button_t *st_a_button)
{
    enu_buttonErrorState_t 
}
enu_buttonErrorState_t BUTTON_disable(st_button_t *st_a_button)
{

}
enu_buttonErrorState_t BUTTON_deInit(st_button_t *st_a_button)
{

}