#ifndef TEA6330T_H_
#define TEA6330T_H_

/*
	Хэдер содержит методы и определения для работы с микросхемой TEA6330T по I2C
*/

#include "soft_i2c.h"

// Адрес на шине I2C = 0b1000000x
#define TEA_SLAVE_ADDR	0x80

// Подадрес Volume left
#define TEA_SUBADDR_VL	0x00

// Подадрес Volume right
#define TEA_SUBADDR_VR	0x01

// Подадрес Bass
#define TEA_SUBADDR_BS	0x02

// Подадрес Treble
#define TEA_SUBADDR_TB	0x03

// Подадрес Fader
#define TEA_SUBADDR_FD	0x04

// Подадрес Audio switch
#define TEA_SUBADDR_AS	0x05

// Инициализация I2C для работы с TEA6330T,
void tea_init( void );

// Функция устанавливает значение громкости для левого канала
// Значения от 36( -66db ) до 63( +20db )
// Значения ниже и до 0 - отключение звука на канале
void tea_set_vl( unsigned char volume );

// Функция устанавливает значение громкости для правого канала
// Значения от 36( -66db ) до 63( +20db )
// Значения ниже и до 0 - отключение звука на канале
void tea_set_vr( unsigned char volume );

// Функция регулировки нижних частот
// Если эквалайзер активен диапазон от 0( -12db ) до 15( +15db ),
// Если эквалайзер неактивен диапазон от 8( 0db ) до 15( +15db )
// значения ниже 8 = 0db
void tea_set_bs( unsigned char bass );

// Функция регулировки высоких частот
// Если эквалайзер активен диапазон от 0( -12db ) до 15( +12db ),
// Если эквалайзер неактивен значения игнорируются, всегда будет 0db
void tea_set_tb( unsigned char treble );

// Функция установки уровня псевдоквадросигнала ( фейдера )
// level - выбор уровня сигнала
// mute - отключение канала
// fader_ch - выбор выхода
void tea_set_fd( unsigned char mute, unsigned char fader_ch, unsigned char level );

// Функция настроек отключения звука и эквалайзера
// mute - отключить звук
// eq - переключение эквалайзера ( 0 - включен )
void tea_set_as( unsigned char mute, unsigned char eq );

#endif /* TEA6330T_H_ */