#include "tea6330t.h"
#include "rotary_encoder.h"
/*
	��������������� ����� ��: 
	PB0 - I2C SDA
	PB1 - I2C SCL
	PB2 - ������� ����� A
	PB3 - ������� ����� B
*/

int main( void ) {

	// �������� ��������� �� ����� ������	
	unsigned char volume_left = 50;
	// ��� ����� ��������� ������� �����������
	
	// ������������� I2C ��� TEA6330T � ��������
	tea_init( );
	re_init( );
	
	// �������� ���� ���������
    while( 1 ) {
		// ���� ��������� �������
		if ( encoder_value ) {
			
			// ���������� ���������
			if ( encoder_value > 0 ) {
				volume_left++;
			} else {
				volume_left--;
			}
			// ������ ���������� � TEA6330T
			tea_set_vl( volume_left );
			
			// ���������� �������� ��������
			encoder_value = 0;
		}
    }
}