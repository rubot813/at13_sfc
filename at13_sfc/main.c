#include "soft_i2c.h"

int main(void) {
	
	DDRB |= _BV( PB4 );
	
    while(1) {
		PORTB |= _BV( PB4 );
		_delay_ms( 1000 );
		PORTB &= ~_BV( PB4 );
		_delay_ms( 1000 );
    }
}