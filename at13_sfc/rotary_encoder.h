#ifndef ROTARY_ENCODER_H_
#define ROTARY_ENCODER_H_

/*
	Хэдер содержит методы работы с энкодером через прерывания, а также его обработчик
*/

#include "avr/interrupt.h"

// Номера ножек на энкодер
#define RE_LINE_A PB2	// A == 2
#define RE_LINE_B PB3	// B == 3

// Текущее значение энкодера
// Значение больше нуля - повернули по часовой стрелке
// Значение меньше нуля - повернули против часовой стрелки
volatile signed char encoder_value;

// Функция инициализация ножек и прерываний
void re_init( void );

#endif /* ROTARY_ENCODER_H_ */