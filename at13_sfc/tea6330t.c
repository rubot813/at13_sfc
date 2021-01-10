#include "tea6330t.h"

void tea_init( void ) {
	soft_i2c_init( );
	soft_i2c_reset( );
}

void tea_set_vl( unsigned char volume ) {
	soft_i2c_start( );
	soft_i2c_write( TEA_SLAVE_ADDR );
	soft_i2c_write( TEA_SUBADDR_VL );
	soft_i2c_write( volume );
	soft_i2c_stop( );
}

void tea_set_vr( unsigned char volume ) {
	soft_i2c_start( );
	soft_i2c_write( TEA_SLAVE_ADDR );
	soft_i2c_write( TEA_SUBADDR_VR );
	soft_i2c_write( volume );
	soft_i2c_stop( );
}

void tea_set_bs( unsigned char bass ) {
	soft_i2c_start( );
	soft_i2c_write( TEA_SLAVE_ADDR );
	soft_i2c_write( TEA_SUBADDR_BS );
	soft_i2c_write( bass );
	soft_i2c_stop( );
}

void tea_set_tb( unsigned char treble ) {
	soft_i2c_start( );
	soft_i2c_write( TEA_SLAVE_ADDR );
	soft_i2c_write( TEA_SUBADDR_TB );
	soft_i2c_write( treble );
	soft_i2c_stop( );
}

void tea_set_fd( unsigned char mute, unsigned char fader_ch, unsigned char level ) {
	unsigned char value = 0;
	value = level & 0x0F;
	if ( fader_ch )
		value |= ( 1 << 4 );
	if ( mute )
		value |= ( 1 << 5 );
	soft_i2c_start( );
	soft_i2c_write( TEA_SLAVE_ADDR );
	soft_i2c_write( TEA_SUBADDR_FD );
	soft_i2c_write( value );
	soft_i2c_stop( );
}

void tea_set_as( unsigned char mute, unsigned char eq ) {
	unsigned char value = 0;
	if ( eq )
		value |= ( 1 << 6 );
	if ( mute )
		value |= ( 1 << 7 );
	soft_i2c_start( );
	soft_i2c_write( TEA_SLAVE_ADDR );
	soft_i2c_write( TEA_SUBADDR_FD );
	soft_i2c_write( value );
	soft_i2c_stop( );
}
