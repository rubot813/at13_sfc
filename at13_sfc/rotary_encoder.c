#include "rotary_encoder.h"

void re_init( void ) {
	// Включение прерываний по изменению уровня на порту
	GIMSK	|= ( 1 << PCIE );
	
	// Настройка маски для прерываний по линиям
	PCMSK	|= ( 1 << RE_LINE_A );
	PCMSK	|= ( 1 << RE_LINE_B );
	
	// Глобальное разрешение прерываний
	sei( );
}

// Обработчик прерывания по изменению уровней на ножках энкодера
ISR( PCINT0_vect ) {
	static unsigned char last_value_a = 1;
	
	// Считывание значений с ножек
	unsigned char value_a = ( PINB & ( 1 << RE_LINE_A ) );
	unsigned char value_b = ( PINB & ( 1 << RE_LINE_B ) );
	
	// Если значение выхода A изменилось с + на -
	if ( !value_a && last_value_a ) {
		// Если в этот момент линия B в плюсе, значит крутим по часовой стрелке
		if ( value_b ) {
			encoder_value++;
		} else {
			// Иначе против часовой
			encoder_value--;
		}
	}
	last_value_a = value_a;
}