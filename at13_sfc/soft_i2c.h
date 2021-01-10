#ifndef SOFT_I2C_H_
#define SOFT_I2C_H_

/*
	������ ��������� ����������� ������ � ����� I2C.
	���������� ��� ATTiny13 / ATTiny13A
	�������� �� ���� � ������ �������.
*/

// �������� ������ ��������� ��������� � avr/io.h
#include <xc.h>

// 1.2��� - ���������� ��������� ATTiny13
#define F_CPU 1200000UL

// ��� ��������
#include <util/delay.h>

// �������� ��������� ����� ���� I2C
#define SOFT_I2C_PIN		PINB
#define SOFT_I2C_DDR		DDRB
#define SOFT_I2C_PORT		PORTB

// �������� ����� PORTA ��� ������� SDA / SCL
#define SOFT_I2C_SCL		PORTB0
#define SOFT_I2C_SDA		PORTB1

// ���� �������������
#define SOFT_I2C_ACK	0	// ������������
#define SOFT_I2C_NACK	1	// �� ������������

// ����� �������� �� ���� I2C � �������������
#define SOFT_I2C_DELAY_TIME_MS 1

// ������� ������ � �����
#define SOFT_I2C_SET_SCL	SOFT_I2C_DDR	&= ~( 1 << SOFT_I2C_SCL ); \
							SOFT_I2C_PORT	|= ( 1 << SOFT_I2C_SCL )	// ��������� ������� �� ����� SCL

#define SOFT_I2C_CLR_SCL	SOFT_I2C_DDR	|= ( 1 << SOFT_I2C_SCL ); \
							SOFT_I2C_PORT	&= ~( 1 << SOFT_I2C_SCL )	// ��������� ���� �� ����� SCL

#define SOFT_I2C_SET_SDA	SOFT_I2C_DDR	&= ~( 1 << SOFT_I2C_SDA ); \
							SOFT_I2C_PORT	|= ( 1 << SOFT_I2C_SDA )	// ��������� ������� �� ����� SDA

#define SOFT_I2C_CLR_SDA	SOFT_I2C_DDR	|= ( 1 << SOFT_I2C_SDA ); \
							SOFT_I2C_PORT	&= ~( 1 << SOFT_I2C_SDA )	// ��������� ���� �� ����� SDA

// ��������� �������

// ������� ������� �����
void soft_i2c_start( void );

// ������� ������� ����
// ������ 1 ���� ������ �� ����� SDA, ������ 2 ���� ������ �� ����� SCL, ������ 0 ���� �������
unsigned char soft_i2c_stop( void );

// ������� ������ �����
void soft_i2c_reset( void );

// ������� ������������� ����
void soft_i2c_init( void );

// ������� �������� ������
// ���������� SOFT_I2C_ACK ���� ������ ��������, SOFT_I2C_NACK ���� �������� ������ ��������
unsigned char soft_i2c_write( unsigned char data );

// ������� ������ ������
// ���� � �������� ���������� ACK, ������ ����� �������� ��� ���� ����, ���� NACK, ������ ������ ��������� ����
unsigned char soft_i2c_read( unsigned char ack );

#endif /* SOFT_I2C_H_ */