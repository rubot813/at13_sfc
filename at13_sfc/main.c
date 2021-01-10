#include "tea6330t.h"

int main(void) {
	
	soft_i2c_init( );
	
	DDRB |= _BV( PB4 );
	
    while(1) {
		PORTB |= _BV( PB4 );
		_delay_ms( 1000 );
		PORTB &= ~_BV( PB4 );
		_delay_ms( 1000 );
		soft_i2c_start( );
		soft_i2c_write( 0xF0 );
		soft_i2c_write( 0x1F );
		soft_i2c_write( 0x15 );
		soft_i2c_stop( );
    }
}