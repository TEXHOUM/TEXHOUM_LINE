//  Библиотека для работы с датчиками линии в составе программно-аппаратного окмплекса TEXHOUM
//  Автор библиотеки: Коркин Максим Валерьевич, Пятов Антон Витальевич

#ifndef TEXHOUM_LINE_h
#define TEXHOUM_LINE_h
#include <Arduino.h>

class LINE {
public:
	LINE(byte pin_INPUT);  //	Инициализация (analog pin)
	uint16_t get();  //	Определение уровня освещённости
private:
	byte _pin_INPUT;       //	Номер вывода подключённого к оптопаре
};

extern LINE IR1;
extern LINE IR2;
extern LINE IR3;
extern LINE IR4;
extern LINE IR5;

#endif
