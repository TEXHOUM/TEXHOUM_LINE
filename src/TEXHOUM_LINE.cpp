#include "Arduino.h"
#include "TEXHOUM_LINE.h"
#define IR1_pin A0
#define IR2_pin A1
#define IR3_pin A2
#define IR4_pin A3
#define IR5_pin A4
#define NUM_SENSORS 5  // количество сенсоров в массиве объектов
#define ERROR 2       // погрешность измерения +-n из-за которой серия не прерывается
#define MIN_SERIES 5   // минимальная длина, при которой набор близких чисел считается серией


// инициализация модуля
LINE::LINE(byte pin_INPUT) {
  _pin_INPUT = pin_INPUT;  // инициализация аналогового входа
}

// определение уровня освещённости
int16_t LINE::get() {
  return analogRead(_pin_INPUT);  // считываем уровень напряжения на входном пине
}

void monitoring() {  // выводит в монитор порта текущие показания датчиков, значение на черном, значение на белом, и пороговое значение
  Serial.begin(9600);

  LINE IRSS[] = { IR1, IR2, IR3, IR4, IR5 };  // создаём массив объектов чтобы не прописывать одни команды для каждого

  for (int i = 0; i < NUM_SENSORS; ++i) {                    // NUM_SENSORS указано в define сверху
    IRSS[i].current_value = analogRead(IRSS[i]._pin_INPUT);  // записываем текущий уровень напряжения на входных пинах
    IRSS[i].previous_value = IRSS[i].current_value;          // приравниваем предыдущее к текущему
    IRSS[i].series_length = 1;                               // обновляем длину текущей серии значений
    // для каждого датчика устанавливаем минимальное значение на максимум и максимальное - на минимум
    IRSS[i].min_series_value = 1023;
    IRSS[i].max_series_value = 0;
  }

  while (true) {
    for (int i = 0; i < NUM_SENSORS; ++i) {                                                                   // NUM_SENSORS указано в define сверху
      IRSS[i].current_value = analogRead(IRSS[i]._pin_INPUT);                                                 // записываем текущий уровень напряжения на входных пинах
      if (abs(IRSS[i].previous_value - IRSS[i].current_value) <= ERROR) {                                     // проверка, что текущее значение не отличается от предыдущего в пределах погрешности
        IRSS[i].series_length++;                                                                              // увеличиваем длину текущей серии значений на 1
      } else {                                                                                                // если текущее значение отличается от предыдущего сильнее погрешности, то есть серия прервана
        if ((IRSS[i].previous_value > IRSS[i].max_series_value) and (IRSS[i].series_length >= MIN_SERIES)) {  // если число, с которого началась серия, больше значения серии устойчивых максимальных значений и длина текущей серии больше пороговой
          IRSS[i].max_series_value = IRSS[i].previous_value;                                                  // число, с которого началась серия, становится новым значением серии устойчивых максимальных значений
          // рассчитываем пороговое значение для датчика с учётом логарифмической зависимости
          if ((IRSS[i].min_series_value < 1023) and (IRSS[i].max_series_value > 0)) {  // если обе серии были обновлены
            uint32_t result1 = (uint32_t)IRSS[i].min_series_value * (uint32_t)IRSS[i].max_series_value;
            float result = sqrt(result1);
            IRSS[i].border = (int)round(result);  // округляем до целых и записываем порог
          }
        }
        if ((IRSS[i].previous_value < IRSS[i].min_series_value) and (IRSS[i].series_length >= MIN_SERIES)) {  // если число, с которого началась серия, меньше значения серии устойчивых минимальных значений и длина текущей серии больше пороговой
          IRSS[i].min_series_value = IRSS[i].previous_value;                                                  // число, с которого началась серия, становится новым значением серии устойчивых минимальных значений
          if ((IRSS[i].min_series_value < 1023) and (IRSS[i].max_series_value > 0)) {                         // если обе серии были обновлены
            // рассчитываем пороговое значение для датчика с учётом логарифмической зависимости
            uint32_t result1 = (uint32_t)IRSS[i].min_series_value * (uint32_t)IRSS[i].max_series_value;
            float result = sqrt(result1);
            IRSS[i].border = (int)round(result);  // округляем до целых и записываем порог
          }
        }
        IRSS[i].series_length = 1;                       // обновляем длину текущей серии значений
        IRSS[i].previous_value = IRSS[i].current_value;  // обновляем предыдущее значение
      }
    }
    Serial.println(F("+-----+--------------+------------------+-------------------+-----------+"));
    Serial.println(F("|  #  | Текущее      |   Минимальное    |   Максимальное    |   Порог   |"));
    Serial.println(F("|     | Current Val  |   Min (black)    |   Max (white)     |   Border  |"));
    Serial.println(F("+-----+--------------+------------------+-------------------+-----------+"));

    for (int i = 0; i < NUM_SENSORS; ++i) {
      Serial.print(F("| "));
      Serial.print("IR");
      Serial.print(i+1);
      Serial.print(F("  |"));

      Serial.print(IRSS[i].current_value);
      Serial.print(F("\t     | "));

      Serial.print(IRSS[i].min_series_value);
      Serial.print(F("\t        | \t"));

      Serial.print(IRSS[i].max_series_value);
      Serial.print(F("\t    | \t"));

      Serial.print(IRSS[i].border);
      Serial.println(F("\t|"));
    }

    Serial.println(F("+-----+--------------+------------------+-------------------+-----------+"));
    Serial.println();

    /*for (int i = 0; i < NUM_SENSORS; ++i) {
      Serial.print(IRSS[i].current_value);
      Serial.print(" ");
      Serial.print(IRSS[i].min_series_value);
      Serial.print(" ");
      Serial.print(IRSS[i].max_series_value);
      Serial.print(" ");
      Serial.print(IRSS[i].border);
      Serial.println(" ");
    }
    Serial.println("---------------");*/ // минимальный вывод | minimal output
  }
}

// датчики, согласно схеме
LINE IR1(IR1_pin);
LINE IR2(IR2_pin);
LINE IR3(IR3_pin);
LINE IR4(IR4_pin);
LINE IR5(IR5_pin);