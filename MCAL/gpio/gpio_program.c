#include "../../LIB/std_types.h"
#include "../../LIB/bit_math.h"
#include "gpio_private.h"
#include "gpio_config.h"
#include "gpio_interface.h"

#include "TM4C123.h"
#include "core_cm4.h" 
#define EN0_REG *((volatile uint32_t*)0xE000E100) 


IRQn_Type enu_gl_gpioPortsIrq[]={GPIOA_IRQn,GPIOB_IRQn,GPIOC_IRQn,GPIOD_IRQn,GPIOE_IRQn,GPIOF_IRQn};
const st_gpioConfig_t st_gl_cst_gpioConfig;
void (*ptr_func_gl_gpioPortsHandlers[GPIO_PORTS])(void)={NULL};


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
        if (st_a_pin->port < INVALID_PORT)
        {
            if (st_a_pin->pin < INVALID_PIN)
            {
                switch (st_a_pin->pinMode)
                {
                    case DIGITAL_INPUT:
                    {
                        SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
                        break;
                    }
                    case DIGITAL_OUTPUT_2MA:
                    {
                        SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODR2R),st_a_pin->pinNum);   //set pin drive
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
                        break;
                    }
                    case DIGITAL_OUTPUT_4MA:
                    {
                        SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODR4R),st_a_pin->pinNum);   //set pin drive
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
                        break;
                    }
                    case DIGITAL_OUTPUT_8MA:
                    {
                        SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODR8R),st_a_pin->pinNum);   //set pin drive
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
                        break;
                    }
                    case ANALOG_INPUT:
                    {
                        SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
                        ACCESS_REG(st_a_pin->port,GPIODEN) = ANALOG_PIN_MASK            //set pin as analog
                        break;
                    }
                    case INPUT_PULL_UP:
                    {
                        SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIOPUR),st_a_pin->pinNum);   //enable pull-up
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
                        break;
                    }
                    case INPUT_PULL_DOWN:
                    {
                        SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);   //set pin direction
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum); //set pin type GPIO or alternative
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIOPDR),st_a_pin->pinNum);   //enable pull-down
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);   //set pin as a digital pin
                        break;
                    }
                    case INTERRUPT_RISING_EDGE:
                    {
                        SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);    //set pin direction
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum);  //set pin type GPIO or alternative
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);     //mask the port interrupt
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIS),st_a_pin->pinNum);     //configure port for edge or level detection
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIORIS),st_a_pin->pinNum);    //configure the port for edge detection
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIEV),st_a_pin->pinNum);    //configure the pin for rising edge
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);    //set pin as a digital pin
                        break;
                    }
                    case INTERRUPT_FALLING_EDGE:
                    {
                        SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);    //set pin direction
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum);  //set pin type GPIO or alternative
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);     //mask the port interrupt
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIS),st_a_pin->pinNum);     //configure port for edge or level detection
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIORIS),st_a_pin->pinNum);    //clear the condition
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIBE),st_a_pin->pinNum);    //configure the port for one edge detection
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIEV),st_a_pin->pinNum);    //configure the pin for falling edge
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);    //set pin as a digital pin
                        break;
                    }
                    case INTERRUPT_BOTH_EDGES:
                    {
                        SET_BIT(RCGCGPIO_REG,st_a_pin->port);                           //enable clock
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIODIR),st_a_pin->pinNum);    //set pin direction
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOAFSEL),st_a_pin->pinNum);  //set pin type GPIO or alternative
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIM),st_a_pin->pinNum);     //mask the port interrupt
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIOIS),st_a_pin->pinNum);     //configure port for edge or level detection
                        CLR_BIT(ACCESS_REG(st_a_pin->port,GPIORIS),st_a_pin->pinNum);    //clear the condition
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIOIBE),st_a_pin->pinNum);    //configure the pin for both edges detection
                        SET_BIT(ACCESS_REG(st_a_pin->port,GPIODEN),st_a_pin->pinNum);    //set pin as a digital pin
                        break;
                    }
                    case INTERRUPT_HIGH_LEVEL:
                    {
                        break;
                    }
                    case INTERRUPT_LOW_LEVEL:
                    {
                        break;
                    }

                    default:
                        enu_a_functionRet = GPIO_INVALID_STATE;
                        break;
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



enu_systemErrorState_t  GPIO_setPinValue(enu_gpioPort_t enu_a_port,enu_pin_t enu_a_pin ,enu_pinLogic_t enu_a_value)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    
    if (enu_a_port < INVALID_PORT)
    {
        if (GET_BIT(RCGCGPIO_REG,enu_a_port))   //check if the port was init 
        {
            if (enu_a_pin < INVALID_PIN)
            {
                if (GET_BIT(ACCESS_REG(enu_a_port,GPIODIR),enu_a_pin) == GPIO_PIN_OUTPUT) //check if the is output or not
                {
                    if (enu_a_value < INVALID_PIN_LOGIC)    
                    {
                        if (enu_a_value == GPIO_LOW)
                        {
                            CLR_BIT(ACCESS_REG(enu_a_port,GPIODATA),enu_a_pin);
                        }
                        else
                        {
                            SET_BIT(ACCESS_REG(enu_a_port,GPIODATA),enu_a_pin);
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
        enu_a_functionRet = GPIO_UN_INITIALIZED_PIN;
    }

    return enu_a_functionRet;
}
enu_systemErrorState_t  GPIO_getPinValue(enu_gpioPort_t enu_a_port, enu_pin_t enu_a_pin , uint8_t *uint8_a_value)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (enu_a_port < INVALID_PORT)
    {
        if (enu_a_pin < INVALID_PIN)
        {
            if (GET_BIT(RCGCGPIO_REG,enu_a_port))   //check for port init
            {
                if (uint8_a_value != NULL)
                {
                    if (GET_BIT(ACCESS_REG(enu_a_port,GPIODATA),enu_a_pin) == GPIO_LOW)
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

enu_systemErrorState_t  GPIO_togglePin(enu_gpioPort_t enu_a_port, enu_pin_t enu_a_pin)
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (enu_a_port < INVALID_PORT)
    {
        if (GET_BIT(RCGCGPIO_REG,enu_a_port))
        {
            if (enu_a_pin < INVALID_PIN)
            {
                TOG_BIT(ACCESS_REG(enu_a_port,GPIODATA),enu_a_pin);  
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

enu_systemErrorState_t  GPIO_enableInterrupt(enu_gpioPort_t enu_a_port, enu_pin_t enu_a_pin,void(*ptr_func_pinInterruptCallack)(void))
{
    enu_systemErrorState_t enu_a_functionRet = GPIO_SUCCESS;
    if (enu_a_port < INVALID_PORT>)
    {
      if (enu_a_pin <INVALID_PIN)
        {
            if (ptr_func_pinInterruptCallack != NULL)
            {
                ptr_func_gl_gpioPortsHandlers[enu_a_port] = ptr_func_pinInterruptCallack;
                SET_BIT(ACCESS_REG(enu_a_port,GPIOIM),enu_a_pin);
                NVIC_EnableIRQ(enu_gl_gpioPortsIrq[enu_a_port]);
                __enable_irq();
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