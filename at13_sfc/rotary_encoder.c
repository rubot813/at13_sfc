#include "rotary_encoder.h"

void re_init( void ) {
	// ��������� ���������� �� ��������� ������ �� �����
	GIMSK	= 0x20;
	//GIMSK	|= ( 1 << PCIE );
	
	// ��������� ����� ��� ���������� �� ������
	PCMSK	= 0b00001100;
	//PCMSK	|= ( 1 << RE_LINE_A );
	//PCMSK	|= ( 1 << RE_LINE_B );
	
	// ���������� ���������� ����������
	sei( );
}

// ���������� ���������� �� ��������� ������� �� ������ ��������
ISR( PCINT0_vect ) {
	static unsigned char last_value_a = 1;
	
	// ���������� �������� � �����
	unsigned char value_a = ( PINB & ( 1 << RE_LINE_A ) );
	unsigned char value_b = ( PINB & ( 1 << RE_LINE_B ) );
	
	// ���� �������� ������ A ���������� � + �� -
	if ( !value_a && last_value_a ) {
		// ���� � ���� ������ ����� B � �����, ������ ������ �� ������� �������
		if ( value_b ) {
			encoder_value++;
		} else {
			// ����� ������ �������
			encoder_value--;
		}
	}
	last_value_a = value_a;
}