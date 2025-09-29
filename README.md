# TEXHOUM\_LINE

**This library for the Arduino IDE allows you to work with the TEXHOUM analog line sensor.**

**Данная библиотека для Arduino IDE позволяет работать с аналоговым датчиком линии TEXHOUM**

Библиотека выводит показания 5 оптопар аналогового датчика линии.

## Назначение функций:

```C++
#include <TEXHOUM_LINE> // Подключаем библиотеку
```

**Определение уровня освещённости** 

```C++
lum = IR1.get(); // Возвращает уровнень освещённости на 1 оптопаре в диапазоне от 0 до 1023
```