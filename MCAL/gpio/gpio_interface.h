#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_ 
#include "../../LIB/std_types.h"


typedef enum __systemErrorState
{
    GPIO_SUCCESS    =   0,
    GPIO_NOT_SUCCESS     ,
    GPIO_INVALID_STATE   ,
    GPIO_UN_INITIALIZED_PIN 
}enu_systemErrorState_t;

typedef enum __gpioPin
{
    GPIO_PIN0    = 0 ,
    GPIO_PIN1        ,
    GPIO_PIN2        ,
    GPIO_PIN3        ,
    GPIO_PIN4        ,
    GPIO_PIN5        ,
    GPIO_PIN6        ,
    GPIO_PIN7        ,
    INVALID_PIN
}enu_pin_t;

typedef enum __gpioInterruptMode
{
	GPIO_PIN_NO_INTERRUPT = 0,
	GPIO_PIN_RISING_EDGE     ,
	GPIO_PIN_FALLING_EDGE    ,
	GPIO_PIN_BOTH_EDGES      ,
    INVALID_INTERRUPT_MODE
} enu_gpioPinInterruptMode_t;

typedef enum _gpioPullMode
{
    GPIO_PIN_NO_PULL = 0  ,
	GPIO_PIN_PULLUP       , 
	GPIO_PIN_PULLDOWN     ,
	INVALID_PULL_MODE
} enu_gpioPinPullMode_t;

typedef enum __gpioPinDirection
{
    GPIO_PIN_INPUT  =  0,
    GPIO_PIN_OUTPUT     ,
    INVALID_PIN_DIR
}enu_gpioPinDirection_t;

typedef enum __pinLogic
{
    GPIO_LOW   = 0 ,
    GPIO_HIGH      ,
    INVALID_PIN_LOGIC
}enu_pinLogic_t;

typedef enum __pinType
{
    GPIO_PIN_TYPE   =   0,
    ALTERNATIVE_PIN_TYPE ,
    INVALID_PIN_TYPE
}enu_pinType_t;

typedef enum __gpioPinDrive
{
	GPIO_PIN_DRIVE_2MA = 0, 
	GPIO_PIN_DRIVE_4MA    ,
	GPIO_PIN_DRIVE_8MA    ,
    INVALID_PIN_DRIVE
} enu_gpioPinDrive_t;

typedef enum __gpioPort
{
    GPIO_PORTA   =     0,
    GPIO_PORTB          ,
    GPIO_PORTC          ,
    GPIO_PORTD          ,
    GPIO_PORTE          ,
    GPIO_PORTF          ,
    INVALID_PORT
}enu_gpioPort_t;


typedef struct  __gpioPinConfig
{
    enu_gpioPort_t port;
    enu_pin_t pinNum;
    enu_gpioPinDirection_t pinDirection;
    enu_pinLogic_t pinLogic;
    enu_pinType_t  pinType;
    enu_gpioPinDrive_t pinDrive;
    enu_gpioPinPullMode_t pinPullMode;
    enu_gpioPinInterruptMode_t pinInterruptMode;
    void *pinInterruptHandler;
}st_gpioPinConfig_t;

typedef struct __gpioPortConfig
{
    enu_gpioPort_t portNum;
    st_gpioPinConfig_t portPins[PORT_PINS];
}st_gpioPortConfig_t;

typedef struct __gpioConfig
{
    st_gpioPortConfig_t gpioPorts[GPIO_PORTS];
}st_gpioConfig_t;

/*enable the clock for ports*/
enu_systemErrorState_t  GPIO_init();
enu_systemErrorState_t  GPIO_initPort(st_gpioPortConfig_t *st_a_port);
enu_systemErrorState_t  GPIO_initPin(st_gpioPinConfig_t *st_a_pin);
enu_systemErrorState_t  GPIO_setPinValue(st_gpioPinConfig_t *st_a_pin , enu_pinLogic_t enu_a_value);
enu_systemErrorState_t  GPIO_getPinValue(st_gpioPinConfig_t *st_a_pin , uint8_t *uint8_a_value);
enu_systemErrorState_t  GPIO_togglePin(st_gpioPinConfig_t *st_a_pin);


#endif // !GPIO_INTERFACE_H_