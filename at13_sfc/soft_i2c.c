#include "soft_i2c.h"

void soft_i2c_start( void ) {
	SOFT_I2C_CLR_SDA;
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );
	SOFT_I2C_CLR_SCL;
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );

}

unsigned char soft_i2c_stop( void ) {
	unsigned char error = SOFT_I2C_NACK;

	// SCL/SDA => 0
	SOFT_I2C_CLR_SCL;
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );
	SOFT_I2C_CLR_SDA;
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );

	// SCL/SDA => 1
	SOFT_I2C_SET_SCL;
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );
	SOFT_I2C_SET_SDA;
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );

	// ������ ������ �� ������
	if ( ( SOFT_I2C_PIN & ( 1 << SOFT_I2C_SDA ) ) == 0 )
		error = 2;
	if ( ( SOFT_I2C_PIN & ( 1 << SOFT_I2C_SCL ) ) == 0 )
		error |= 1;

	// todo: �������� ������������ �������� ����� ������� ����
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );

	return error;
}

void soft_i2c_reset( void ) {
	// �������� � 1 ���� ��� ����
	SOFT_I2C_SET_SDA;
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );
	SOFT_I2C_SET_SCL;
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );

	// ��������� � 0 ���� ��� ����
	soft_i2c_start( );
}

void soft_i2c_init( void ) {
	SOFT_I2C_SET_SDA;
	SOFT_I2C_SET_SCL;
	soft_i2c_stop( );	// ������������� ack/nack = �� ������
}

unsigned char soft_i2c_write( unsigned char data ) {
	unsigned char ack = SOFT_I2C_ACK;
	unsigned char i;

	// ������ �� �����
	for ( i = 0; i < 8; i++ ) {
		// ������ �� ����� ������� ���
		if ( ( data & 0x80 ) == 0 ) {
			SOFT_I2C_CLR_SDA;
		} else {
			SOFT_I2C_SET_SDA;
		}

		// ������� �� �������� �����
		_delay_ms( SOFT_I2C_DELAY_TIME_MS );
		SOFT_I2C_SET_SCL;
		_delay_ms( SOFT_I2C_DELAY_TIME_MS );
		SOFT_I2C_CLR_SCL;

		// �������� � ������
		data = ( data << 1 );
	}

	SOFT_I2C_SET_SDA;
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );
	SOFT_I2C_CLR_SDA;
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );

	if ( ( SOFT_I2C_PIN & ( 1 << SOFT_I2C_SDA ) ) == ( 1 << SOFT_I2C_SDA ) ) {
		ack = SOFT_I2C_NACK;
	} else {
		ack = SOFT_I2C_ACK;
	}

	// ���������� �������� �����
	SOFT_I2C_CLR_SCL;

	return ack;
}

unsigned char soft_i2c_read( unsigned char ack ) {
	unsigned char data = 0;
	unsigned char i;

	SOFT_I2C_SET_SDA;

	// ������ �� �����
	for ( i = 0; i < 8; i++ ) {
		data = ( data << 1 );
		SOFT_I2C_SET_SCL;
		_delay_ms( SOFT_I2C_DELAY_TIME_MS );

		// ��������� ���
		if ( ( SOFT_I2C_PIN & ( 1 << SOFT_I2C_SDA ) ) == ( 1 << SOFT_I2C_SDA ) )
			data |= 0x01;
		
		SOFT_I2C_CLR_SCL;
		_delay_ms( SOFT_I2C_DELAY_TIME_MS );
	}

	if ( ack == SOFT_I2C_NACK ) {
		SOFT_I2C_SET_SDA;
	} else {
		SOFT_I2C_CLR_SDA;
	}

	return data;
}
