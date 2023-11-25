#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_ 
void APP_sequence(void);
st_button_t st_g_sw1 = {
    .buttonPort = BUTTON_PORTF,
    .buttonPin  = BUTTON_PIN4,
    .buttonMode = BUTTON_INTERRUPT_FALLING_EDGE_MODE,
    .buttonHandler = APP_sequence
};
st_led_t st_g_redLed = {
    .ledPort = LED_PORTF,
    .ledPin  = LED_PIN1,
    .ledState= LED_OFF
};
st_led_t st_g_blueLed = {
    .ledPort = LED_PORTF,
    .ledPin  = LED_PIN2,
    .ledState= LED_OFF
};
st_led_t st_g_greenLed = {
    .ledPort = LED_PORTF,
    .ledPin  = LED_PIN3,
    .ledState= LED_OFF
};
#endif