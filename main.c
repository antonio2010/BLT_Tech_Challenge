#include <avr/io.h>

#include <avr/interrupt.h>

#include <util/delay.h>



#define LED1_PIN PB0 // Pin for the first LED

#define LED2_PIN PB1 // Pin for the second LED



volatile uint16_t timer_count = 0;



void setup_timer1() {

    // Configure Timer1 in normal mode

    TCCR1A = 0x00; // Normal mode

    TCCR1B = (1 << CS11); // Prescaler = 8

    TIMSK1 = (1 << TOIE1); // Enable Timer1 overflow interrupt

}



void setup_pins() {

    // Set LED pins as outputs

    DDRB |= (1 << LED1_PIN) | (1 << LED2_PIN);

    // Turn off LEDs initially

    PORTB &= ~((1 << LED1_PIN) | (1 << LED2_PIN));

}



ISR(TIMER1_OVF_vect) {

    timer_count++;

}



void toggle_led1(uint16_t count) {

    if (count >= 65000) {

        PORTB ^= (1 << LED1_PIN); // Toggle LED1

    }

}



void blink_led2(uint32_t current_time) {

    static uint32_t last_blink_time = 0;
    uint8_t i;

    if (current_time - last_blink_time >= 3000) {

        for (i = 0; i < 5; i++) {

            PORTB |= (1 << LED2_PIN);  // Turn on LED2

            _delay_ms(200);           // Delay 200ms

            PORTB &= ~(1 << LED2_PIN); // Turn off LED2

            _delay_ms(200);           // Delay 200ms

        }

        last_blink_time = current_time;

    }

}



int main() {

    setup_pins();

    setup_timer1();

    sei(); // Enable global interrupts



    while (1) {

        uint32_t current_time = (timer_count * 65536UL) + TCNT1;

        toggle_led1(TCNT1);

        blink_led2(current_time / 1000); // Convert to milliseconds

    }



    return 0;
}