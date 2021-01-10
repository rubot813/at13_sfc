#ifndef SOFT_I2C_H_
#define SOFT_I2C_H_

/*
	Модуль реализует программную работу с шиной I2C.
	Реализован для ATTiny13 / ATTiny13A
	Работает на шине в режиме мастера.
*/

// Включает адреса служебных регистров и avr/io.h
#include <xc.h>

// 1.2Мгц - встроенный резонатор ATTiny13
#define F_CPU 1200000UL

// Для задержек
#include <util/delay.h>

// Названия регистров порта шины I2C
#define SOFT_I2C_PIN		PINB
#define SOFT_I2C_DDR		DDRB
#define SOFT_I2C_PORT		PORTB

// Названия битов PORTA для выходов SDA / SCL
#define SOFT_I2C_SCL		PORTB0
#define SOFT_I2C_SDA		PORTB1

// Коды подтверждений
#define SOFT_I2C_ACK	0	// Подтверждено
#define SOFT_I2C_NACK	1	// Не подтверждено

// Время задержек на шине I2C в миллисекундах
#define SOFT_I2C_DELAY_TIME_MS 1

// Макросы работы с шиной
#define SOFT_I2C_SET_SCL	SOFT_I2C_DDR	&= ~( 1 << SOFT_I2C_SCL ); \
							SOFT_I2C_PORT	|= ( 1 << SOFT_I2C_SCL )	// Установка единицы на линию SCL

#define SOFT_I2C_CLR_SCL	SOFT_I2C_DDR	|= ( 1 << SOFT_I2C_SCL ); \
							SOFT_I2C_PORT	&= ~( 1 << SOFT_I2C_SCL )	// Установка нуля на линию SCL

#define SOFT_I2C_SET_SDA	SOFT_I2C_DDR	&= ~( 1 << SOFT_I2C_SDA ); \
							SOFT_I2C_PORT	|= ( 1 << SOFT_I2C_SDA )	// Установка единицы на линию SDA

#define SOFT_I2C_CLR_SDA	SOFT_I2C_DDR	|= ( 1 << SOFT_I2C_SDA ); \
							SOFT_I2C_PORT	&= ~( 1 << SOFT_I2C_SDA )	// Установка нуля на линию SDA

// Прототипы функций

// Функция условия старт
void soft_i2c_start( void );

// Функция условия стоп
// Вернет 1 если ошибка на линии SDA, вернет 2 если ошибка на линии SCL, вернет 0 если успешно
unsigned char soft_i2c_stop( void );

// Функция сброса линий
void soft_i2c_reset( void );

// Функция инициализации шины
void soft_i2c_init( void );

// Функции передачи данных
// Возвращают SOFT_I2C_ACK если данные переданы, SOFT_I2C_NACK если возникла ошибка передачи
unsigned char soft_i2c_write( unsigned char data );

// Функции приема данных
// Если в аргумент передается ACK, значит будет читаться еще один байт, если NACK, значит принят последний байт
unsigned char soft_i2c_read( unsigned char ack );

#endif /* SOFT_I2C_H_ */