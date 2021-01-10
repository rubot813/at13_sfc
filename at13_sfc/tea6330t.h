#ifndef TEA6330T_H_
#define TEA6330T_H_

/*
	����� �������� ������ � ����������� ��� ������ � ����������� TEA6330T �� I2C
*/

#include "soft_i2c.h"

// ����� �� ���� I2C = 0b1000000x
#define TEA_SLAVE_ADDR	0x80

// �������� Volume left
#define TEA_SUBADDR_VL	0x00

// �������� Volume right
#define TEA_SUBADDR_VR	0x01

// �������� Bass
#define TEA_SUBADDR_BS	0x02

// �������� Treble
#define TEA_SUBADDR_TB	0x03

// �������� Fader
#define TEA_SUBADDR_FD	0x04

// �������� Audio switch
#define TEA_SUBADDR_AS	0x05

// ������������� I2C ��� ������ � TEA6330T,
void tea_init( void );

// ������� ������������� �������� ��������� ��� ������ ������
// �������� �� 36( -66db ) �� 63( +20db )
// �������� ���� � �� 0 - ���������� ����� �� ������
void tea_set_vl( unsigned char volume );

// ������� ������������� �������� ��������� ��� ������� ������
// �������� �� 36( -66db ) �� 63( +20db )
// �������� ���� � �� 0 - ���������� ����� �� ������
void tea_set_vr( unsigned char volume );

// ������� ����������� ������ ������
// ���� ���������� ������� �������� �� 0( -12db ) �� 15( +15db ),
// ���� ���������� ��������� �������� �� 8( 0db ) �� 15( +15db )
// �������� ���� 8 = 0db
void tea_set_bs( unsigned char bass );

// ������� ����������� ������� ������
// ���� ���������� ������� �������� �� 0( -12db ) �� 15( +12db ),
// ���� ���������� ��������� �������� ������������, ������ ����� 0db
void tea_set_tb( unsigned char treble );

// ������� ��������� ������ ������������������� ( ������� )
// level - ����� ������ �������
// mute - ���������� ������
// fader_ch - ����� ������
void tea_set_fd( unsigned char mute, unsigned char fader_ch, unsigned char level );

// ������� �������� ���������� ����� � �����������
// mute - ��������� ����
// eq - ������������ ����������� ( 0 - ������� )
void tea_set_as( unsigned char mute, unsigned char eq );

#endif /* TEA6330T_H_ */