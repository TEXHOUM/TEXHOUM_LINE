//  Библиотека для работы с датчиками линии в составе программно-аппаратного окмплекса TEXHOUM
//  Автор библиотеки: Коркин Максим Валерьевич, Пятов Антон Витальевич

#ifndef TEXHOUM_LINE_h
#define TEXHOUM_LINE_h
#include <Arduino.h>

class LINE {
public:
	LINE(byte pin_INPUT);      //	Инициализация (analog pin)
	byte _pin_INPUT;           //	Номер вывода, подключённого к оптопаре
	int16_t get();             //	Определение уровня освещённости
	int16_t min_series_value;  // Значение серии устойчивых минимальных значений
	int16_t max_series_value;  // Значение серии устойчивых максимальных значений
	int16_t current_value;     // Текущее значение
	int16_t previous_value;    // Предыдущее значение
	uint16_t series_length;    // Длина текущей серии значений
	int16_t border;            // Пороговое значение между чёрным и белым
private:
};

void monitoring();  // выводит в монитор порта текущие показания датчиков, значение на черном, значение на белом, и пороговое значение

extern LINE IR1;
extern LINE IR2;
extern LINE IR3;
extern LINE IR4;
extern LINE IR5;

#endif