#include "tea6330t.h"
#include "rotary_encoder.h"
/*
	Задействованные ножки МК: 
	PB0 - I2C SDA
	PB1 - I2C SCL
	PB2 - энкодер ножка A
	PB3 - энкодер ножка B
*/

int main( void ) {

	// Значение громкости на левом канале	
	unsigned char volume_left = 50;
	// Тут можно дополнить другими параметрами
	
	// Инициализация I2C для TEA6330T и энкодера
	tea_init( );
	re_init( );
	
	// Основной цикл программы
    while( 1 ) {
		// Если покрутили энкодер
		if ( encoder_value ) {
			
			// Подстройка громкости
			if ( encoder_value > 0 ) {
				volume_left++;
			} else {
				volume_left--;
			}
			// Запись громокости в TEA6330T
			tea_set_vl( volume_left );
			
			// Сбрасываем значение энкодера
			encoder_value = 0;
		}
    }
}