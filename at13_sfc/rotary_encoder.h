#ifndef ROTARY_ENCODER_H_
#define ROTARY_ENCODER_H_

/*
	����� �������� ������ ������ � ��������� ����� ����������, � ����� ��� ����������
*/

#include "avr/interrupt.h"

// ������ ����� �� �������
#define RE_LINE_A PB2	// A == 2
#define RE_LINE_B PB3	// B == 3

// ������� �������� ��������
// �������� ������ ���� - ��������� �� ������� �������
// �������� ������ ���� - ��������� ������ ������� �������
volatile signed char encoder_value;

// ������� ������������� ����� � ����������
void re_init( void );

#endif /* ROTARY_ENCODER_H_ */