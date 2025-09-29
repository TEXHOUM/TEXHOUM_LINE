#include "TEXHOUM_LINE.h"
// инициализация модуля
LINE::LINE(byte pin_INPUT) {
  _pin_INPUT=pin_INPUT;                           // инициализация аналогового входа
}

// определение уровня освещённости
uint16_t LINE::get(){					
  return analogRead(_pin_INPUT);                  // считываем уровень напряжения на входном пине
}

// датчики, согласно схеме
LINE IR1(A0);
LINE IR2(A1);
LINE IR3(A2);
LINE IR4(A3);
LINE IR5(A4);
