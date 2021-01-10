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

	// Провка ошибок на линиях
	if ( ( SOFT_I2C_PIN & ( 1 << SOFT_I2C_SDA ) ) == 0 )
		error = 2;
	if ( ( SOFT_I2C_PIN & ( 1 << SOFT_I2C_SCL ) ) == 0 )
		error |= 1;

	// todo: Уточнить длительность задержки после условия стоп
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );

	return error;
}

void soft_i2c_reset( void ) {
	// Поднятие в 1 всех ног шины
	SOFT_I2C_SET_SDA;
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );
	SOFT_I2C_SET_SCL;
	_delay_ms( SOFT_I2C_DELAY_TIME_MS );

	// Опускание в 0 всех ног шины
	soft_i2c_start( );
}

void soft_i2c_init( void ) {
	SOFT_I2C_SET_SDA;
	SOFT_I2C_SET_SCL;
	soft_i2c_stop( );	// Игнорирование ack/nack = мы мастер
}

unsigned char soft_i2c_write( unsigned char data ) {
	unsigned char ack = SOFT_I2C_ACK;
	unsigned char i;

	// Проход по битам
	for ( i = 0; i < 8; i++ ) {
		// Выдаем на линию текущий бит
		if ( ( data & 0x80 ) == 0 ) {
			SOFT_I2C_CLR_SDA;
		} else {
			SOFT_I2C_SET_SDA;
		}

		// Импульс по тактовой линии
		_delay_ms( SOFT_I2C_DELAY_TIME_MS );
		SOFT_I2C_SET_SCL;
		_delay_ms( SOFT_I2C_DELAY_TIME_MS );
		SOFT_I2C_CLR_SCL;

		// Смещение в данных
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

	// Отпускание тактовой линии
	SOFT_I2C_CLR_SCL;

	return ack;
}

unsigned char soft_i2c_read( unsigned char ack ) {
	unsigned char data = 0;
	unsigned char i;

	SOFT_I2C_SET_SDA;

	// Проход по битам
	for ( i = 0; i < 8; i++ ) {
		data = ( data << 1 );
		SOFT_I2C_SET_SCL;
		_delay_ms( SOFT_I2C_DELAY_TIME_MS );

		// Сохраняем бит
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
