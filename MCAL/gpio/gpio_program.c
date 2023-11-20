#include "../../LIB/std_types.h"
#include "../../LIB/bit_math.h"
#include "gpio_private.h"
#include "gpio_config.h"
#include "gpio_interface.h"

#include "TM4C123.h"
#include "core_cm4.h" 
#define EN0_REG *((volatile uint32_t*)0xE000E100) 
const st_gpioConfig_t st_gl_cst_gpioConfig;

void *void_ptr_gl_portfHandler[GPIO_PORTS];
enu_systemErrorState_t  GPIO_init()
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    for(uint8_t uint8_a_portIterator = 0 ; uint8_a_portIterator < GPIO_PORTS ; uint8_a_portIterator++)
    {
        enu_a_functionRet = GPIO_initPort(&st_gl_cst_gpioConfig.gpioPorts[uint8_a_portIterator]);
        if (enu_a_functionRet != GPIO_SUCCESS)
        {
            break;
        }
        else
        {
            /*do nothing*/
        }
        
    }
    return enu_a_functionRet;
}




enu_systemErrorState_t  GPIO_initPort(st_gpioPortConfig_t *st_a_port)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if(st_a_port != NULL)
    {
        if (st_a_port->portNum < INVALID_PORT)
        {
            SET_BIT(RCGCGPIO_REG,st_a_port->portNum);

            for(uint8_t uint8_a_pinIterator = 0 ; uint8_a_pinIterator < PORT_PINS ; uint8_a_pinIterator++)
            {
                enu_a_functionRet = GPIO_initPin(&(st_a_port->portPins[uint8_a_pinIterator]));
                if (enu_a_functionRet != GPIO_SUCCESS)
                {
                    break;
                }
                else
                {
                    /*do nothing*/
                }

            }
            
        }
        else
        {
            enu_a_functionRet = GPIO_INVALID_STATE;
        }
    }
    else
    {
        enu_a_functionRet = GPIO_INVALID_STATE;
    }
        
    return enu_a_functionRet;
}


enu_systemErrorState_t  GPIO_initPin(st_gpioPinConfig_t *st_a_pin)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (st_a_pin != NULL)
    {
        if (st_a_pin->pinNum < INVALID_PIN)
        {
            if (st_a_pin->port < INVALID_PORT)
            {
    
                SET_BIT(RCGCGPIO_REG,st_a_pin->port);
                SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);
                //set pin type GPIO pin or alternative pin
                if (st_a_pin->pinType == GPIO_PIN_TYPE)
                {
                    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum);
                }
                else if (st_a_pin->pinType == ALTERNATIVE_PIN_TYPE)
                {
                    SET_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum);
                }
                else 
                {
                    enu_a_functionRet = GPIO_INVALID_STATE;
                }
                //set pin direction
                if (st_a_pin->pinDirection == GPIO_PIN_INPUT)
                {
                    CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);
                    //set pin PULL_MODE
                    if (st_a_pin->pinPullMode == GPIO_PIN_NO_PULL )
                    {
                        /*do nothing*/
                    }
                    else if (st_a_pin->pinPullMode == GPIO_PIN_PULLUP)
                    {
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIOPUR),st_a_pin->pinNum);
                    }
                    else if (st_a_pin->pinPullMode == GPIO_PIN_PULLDOWN)
                    {
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIOPDR),st_a_pin->pinNum);
                    }
                    else 
                    {
                        enu_a_functionRet = GPIO_INVALID_STATE;
                    }

                }
                else if (st_a_pin->pinDirection == GPIO_PIN_OUTPUT)
                {
                    SET_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);
                    //set pin Value
                    if (st_a_pin->pinLogic == GPIO_LOW)
                    {
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODATA),st_a_pin->pinNum);
                    }
                    else if (st_a_pin->pinLogic  == GPIO_HIGH)
                    {
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODATA),st_a_pin->pinNum);
                    }
                    else 
                    {
                        enu_a_functionRet = GPIO_INVALID_STATE;
                    }
                        //set pin drive mode 2ma or 4ma or 8ma
                    if (st_a_pin->pinDrive == GPIO_PIN_DRIVE_2MA)
                    {
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODR2R),st_a_pin->pinNum);
                    }
                    else if (st_a_pin->pinDrive == GPIO_PIN_DRIVE_4MA)
                    {
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODR4R),st_a_pin->pinNum);
                    }
                    else if (st_a_pin->pinDrive == GPIO_PIN_DRIVE_8MA)
                    {
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODR8R),st_a_pin->pinNum);
                    }
                    else 
                    {
                        enu_a_functionRet = GPIO_INVALID_STATE;
                    }

                }
                else 
                {
                    enu_a_functionRet = GPIO_INVALID_STATE;
                }

                if (st_a_pin->pinInterruptMode != GPIO_PIN_NO_INTERRUPT)
                {
                    if (st_a_pin->pinNum <INVALID_PIN)
                    {
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIS),st_a_pin->pinNum);
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIORIS),st_a_pin->pinNum);
                        //SET_BIT(EN0_REG,14);
                        if (st_a_pin->pinInterruptMode == GPIO_PIN_BOTH_EDGES)
                        {
                            SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIBE),st_a_pin->pinNum);
                            SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);
                            NVIC_EnableIRQ(GPIOF_IRQn);
                            __enable_irq();
                        }
                        else
                        {
                            CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIBE),st_a_pin->pinNum);
                            if (st_a_pin->pinInterruptMode == GPIO_PIN_RISING_EDGE)
                            {
                                SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIEV),st_a_pin->pinNum);
                                SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);
                                NVIC_EnableIRQ(GPIOF_IRQn);
                                __enable_irq();
                            }
                            else if (st_a_pin->pinInterruptMode == GPIO_PIN_FALLING_EDGE)
                            {
                                CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIEV),st_a_pin->pinNum);
                                SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);
                                NVIC_EnableIRQ(GPIOF_IRQn);
                                __enable_irq();
                            }
                            else
                            {
                                enu_a_functionRet = GPIO_INVALID_STATE;
                            }
                            
                        }
                        if (st_a_pin->pinInterruptHandler != NULL)
                        {
                            void_ptr_gl_portfHandler[st_a_pin->port] = st_a_pin->pinInterruptHandler;
                        }
                        else
                        {
                            enu_a_functionRet = GPIO_INVALID_STATE;
                        }
                        
                        
                    }
                    else
                    {
                        enu_a_functionRet = GPIO_INVALID_STATE;
                    }
                    
                }
                else
                {
                    enu_a_functionRet = GPIO_INVALID_STATE;
                }
                
            }
            
            else
            {
                enu_a_functionRet = GPIO_INVALID_STATE;
            }   
        }
        else
        {
            enu_a_functionRet = GPIO_INVALID_STATE;
        }  
    }
    else
    {
        enu_a_functionRet = GPIO_INVALID_STATE;
    }
   // SET_BIT(ACCESS_REG(st_a_pin->port,GPIORIS),st_a_pin->pinNum);
    return enu_a_functionRet;
}



enu_systemErrorState_t  GPIO_setPinValue(st_gpioPinConfig_t *st_a_pin , enu_pinLogic_t enu_a_value)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (st_a_pin != NULL)
    {
        if (st_a_pin->port < INVALID_PORT)
        {
            if (GET_BIT(RCGCGPIO_REG,st_a_pin->port))
            {
                if (GET_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum) == GPIO_PIN_OUTPUT)
                {
                    if (enu_a_value < INVALID_PIN_LOGIC)
                    {
                        if (enu_a_value == GPIO_LOW)
                        {
                            CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODATA),st_a_pin->pinNum);
                        }
                        else
                        {
                            SET_BIT(ACCESS_REG(st_a_pin->port,GPIODATA),st_a_pin->pinNum);
                        }
                        
                    }
                    else
                    {
                        enu_a_functionRet = GPIO_INVALID_STATE; 
                    }
                    
                }
                else
                {
                    enu_a_functionRet = GPIO_NOT_SUCCESS;
                }
                
            }
            else
            {
                enu_a_functionRet = GPIO_UN_INITIALIZED_PIN;
            }
            
        }
        else
        {
            enu_a_functionRet = GPIO_INVALID_STATE; 
        }
        
    }
    else
    {
       enu_a_functionRet = GPIO_INVALID_STATE; 
    }
    return enu_a_functionRet;
}
enu_systemErrorState_t  GPIO_getPinValue(st_gpioPinConfig_t *st_a_pin , uint8_t *uint8_a_value)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (st_a_pin != NULL)
    {
        if (st_a_pin->port < INVALID_PORT)
        {
            if (GET_BIT(RCGCGPIO_REG,st_a_pin->port))
            {
                if (uint8_a_value != NULL)
                {
                    if (GET_BIT(ACCESS_REG(st_a_pin->port,GPIODATA),st_a_pin->pinNum) == GPIO_LOW)
                    {
                        *uint8_a_value = GPIO_LOW;
                    }
                    else
                    {
                        *uint8_a_value = GPIO_HIGH;
                    }
                    
                }
                else
                {
                    enu_a_functionRet = GPIO_NOT_SUCCESS;
                }
                
            }
            else
            {
                enu_a_functionRet = GPIO_UN_INITIALIZED_PIN;
            }
            
        }
        else
        {
            enu_a_functionRet = GPIO_INVALID_STATE; 
        }
        
    }
    else
    {
       enu_a_functionRet = GPIO_INVALID_STATE; 
    }
    return enu_a_functionRet;
}

enu_systemErrorState_t  GPIO_togglePin(st_gpioPinConfig_t *st_a_pin)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (st_a_pin != NULL)
    {
        if (st_a_pin->port < INVALID_PORT)
        {
            if (GET_BIT(RCGCGPIO_REG,st_a_pin->port))
            {
                if (st_a_pin->pinNum < INVALID_PIN)
                {
                    TOG_BIT(ACCESS_REG(st_a_pin->port,GPIODATA),st_a_pin->pinNum);
                }
                else
                {
                    enu_a_functionRet = GPIO_INVALID_STATE; 
                }
                
            }
            else
            {
                enu_a_functionRet = GPIO_UN_INITIALIZED_PIN;
            }
            
        }
        else
        {
            enu_a_functionRet = GPIO_INVALID_STATE; 
        }
        
    }
    else
    {
       enu_a_functionRet = GPIO_INVALID_STATE; 
    }
    return enu_a_functionRet;
}

enu_systemErrorState_t  GPIO_enableInterrupt(st_gpioPinConfig_t *st_a_pin)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (st_a_pin != NULL)
    {
      if (st_a_pin->pinInterruptMode != GPIO_PIN_NO_INTERRUPT)
                {
                    if (st_a_pin->pinNum <INVALID_PIN)
                    {
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIS),st_a_pin->pinNum);
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIORIS),st_a_pin->pinNum);
                        if (st_a_pin->pinInterruptMode == GPIO_PIN_BOTH_EDGES)
                        {
                            SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIBE),st_a_pin->pinNum);
                            SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);
                            NVIC_EnableIRQ(GPIOF_IRQn);
                            __enable_irq();
                        }
                        else
                        {
                            CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIBE),st_a_pin->pinNum);
                            if (st_a_pin->pinInterruptMode == GPIO_PIN_RISING_EDGE)
                            {
                                SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIEV),st_a_pin->pinNum);
                                SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);
                                NVIC_EnableIRQ(GPIOF_IRQn);
                                __enable_irq();
                            }
                            else if (st_a_pin->pinInterruptMode == GPIO_PIN_FALLING_EDGE)
                            {
                                CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIEV),st_a_pin->pinNum);
                                SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);
                                NVIC_EnableIRQ(GPIOF_IRQn);
                                __enable_irq();
                            }
                            else
                            {
                                enu_a_functionRet = GPIO_INVALID_STATE;
                            }
                            
                        }
                        if (st_a_pin->pinInterruptHandler != NULL)
                        {
                            void_ptr_gl_portfHandler[st_a_pin->port] = st_a_pin->pinInterruptHandler;
                        }
                        else
                        {
                            enu_a_functionRet = GPIO_INVALID_STATE;
                        }
                        
                        
                    }
                    else
                    {
                        enu_a_functionRet = GPIO_INVALID_STATE;
                    }
                    
                }
                else
                {
                    enu_a_functionRet = GPIO_INVALID_STATE;
                }   
    }
    else
    {
         enu_a_functionRet = GPIO_INVALID_STATE;
    }
    return enu_a_functionRet;
}
enu_systemErrorState_t  GPIO_configureInterrupt(st_gpioPinConfig_t *st_a_pin)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (st_a_pin != NULL)
    {
         if (st_a_pin->pinInterruptMode != GPIO_PIN_NO_INTERRUPT)
                {
                    if (st_a_pin->pinNum <INVALID_PIN)
                    {
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIS),st_a_pin->pinNum);
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIORIS),st_a_pin->pinNum);
                        //SET_BIT(EN0_REG,14);
                        if (st_a_pin->pinInterruptMode == GPIO_PIN_BOTH_EDGES)
                        {
                            SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIBE),st_a_pin->pinNum);
                            SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);
                            NVIC_EnableIRQ(GPIOF_IRQn);
                            __enable_irq();
                        }
                        else
                        {
                            CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIBE),st_a_pin->pinNum);
                            if (st_a_pin->pinInterruptMode == GPIO_PIN_RISING_EDGE)
                            {
                                SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIEV),st_a_pin->pinNum);
                                SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);
                                NVIC_EnableIRQ(GPIOF_IRQn);
                                __enable_irq();
                            }
                            else if (st_a_pin->pinInterruptMode == GPIO_PIN_FALLING_EDGE)
                            {
                                CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIEV),st_a_pin->pinNum);
                                SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);
                                NVIC_EnableIRQ(GPIOF_IRQn);
                                __enable_irq();
                            }
                            else
                            {
                                enu_a_functionRet = GPIO_INVALID_STATE;
                            }
                            
                        }
                        if (st_a_pin->pinInterruptHandler != NULL)
                        {
                            void_ptr_gl_portfHandler[st_a_pin->port] = st_a_pin->pinInterruptHandler;
                        }
                        else
                        {
                            enu_a_functionRet = GPIO_INVALID_STATE;
                        }
                        
                        
                    }
                    else
                    {
                        enu_a_functionRet = GPIO_INVALID_STATE;
                    }
                    
                }
                else
                {
                    enu_a_functionRet = GPIO_INVALID_STATE;
                }
    }
    else
    {
        enu_a_functionRet = GPIO_INVALID_STATE;
    }
    return enu_a_functionRet;
}
enu_systemErrorState_t  GPIO_disableInterrupt(st_gpioPinConfig_t *st_a_pin);




void GPIOA_Handler(void)
{
    if (void_ptr_gl_portfHandler != NULL)
    {
        ((void(*)(void))void_ptr_gl_portfHandler[0])();
    }
    
}
void GPIOB_Handler(void)
{
    if (void_ptr_gl_portfHandler != NULL)
    {
        ((void(*)(void))void_ptr_gl_portfHandler[1])();
    }
    
}
void GPIOC_Handler(void)
{
    if (void_ptr_gl_portfHandler != NULL)
    {
        ((void(*)(void))void_ptr_gl_portfHandler[2])();
    }
    
}
void GPIOD_Handler(void)
{
    if (void_ptr_gl_portfHandler != NULL)
    {
        ((void(*)(void))void_ptr_gl_portfHandler[3])();
    }
    
}
void GPIOE_Handler(void)
{
    if (void_ptr_gl_portfHandler != NULL)
    {
        ((void(*)(void))void_ptr_gl_portfHandler[4])();
    }
    
}

void GPIOF_Handler(void)
{
    if (void_ptr_gl_portfHandler != NULL)
    {
        ((void(*)(void))void_ptr_gl_portfHandler[5])();
    }
    
}