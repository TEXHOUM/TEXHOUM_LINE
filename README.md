# TEXHOUM\_LINE

## Данная библиотека для Arduino IDE позволяет работать с аналоговым датчиком линии TEXHOUM
Библиотека выводит показания 5 сенсоров аналогового датчика линии.
Также её можно использовать для калибровки датчика с выводом в монитор порта значений в реальном времени и рассчётом порога между чёрным и белым.

## Назначение функций:

```C++
#include <TEXHOUM_LINE> // Подключаем библиотеку
```

**Определение уровня освещённости** 

```C++
lum = IR1.get(); // Возвращает уровнень освещённости на 1 оптопаре в диапазоне от 0 до 1023
```

**Функция мониторинга**

Для правильной работы датчика нужно подстроить пороговое значение в вашей программе под показания в текущих условиях. Для вывода показаний датчика на ПК и рассчёта порога предусмотрена отдельная функция
```C++
monitoring();  // выводит в монитор порта текущие показания датчиков и пороговое значение
```

Пример вывода:
```C++
+-----+--------------+------------------+-------------------+-----------+
|  #  | Текущее      |   Минимальное    |   Максимальное    |   Порог   |
|     | Current Val  |   Min (black)    |   Max (white)     |   Border  |
+-----+--------------+------------------+-------------------+-----------+
| IR1 |239		     | 232		        | 	272			    | 	251		|
| IR2 |238		     | 230		        | 	274			    | 	251		|
| IR3 |236		     | 229		        | 	346			    | 	281		|
| IR4 |233		     | 226		        | 	326			    | 	271		|
| IR5 |232		     | 226		        | 	269			    | 	247		|
+-----+--------------+------------------+-------------------+-----------+
```
Для работы функции необходимо оставить контроллер подключенным к ПК и открыть монитор порта в Arduino IDE.

***Функция выполняется бесконечно! Никакой код ниже вызова функции не будет выполнен!***

После того как будут получены необходимые для калибровки значения, не забудьте после их добавления в код удалить или закомментировать функцию!

---

## This library for Arduino IDE allows working with the analog line sensor TEXHOUM

The library outputs readings of 5 sensors of the analog line sensor.
It can also be used to calibrate the sensor by displaying real-time values ​​on the port monitor and calculating the threshold between black and white.

## Function purpose:

```C++
#include <TEXHOUM_LINE> // Connect the library
```

**Light level detection** 

```C++
lum = IR1.get(); // Returns the light level on the 1st optocoupler in the range from 0 to 1023
```

**Monitoring function**

For correct sensor operation, you need to adjust the threshold value in your program according to the readings under current conditions. To output sensor readings to the PC and calculate the threshold, a separate function is provided
```C++
monitoring();  // outputs current sensor readings and threshold value to the serial monitor
```

Example output:
```C++
+-----+--------------+------------------+-------------------+-----------+
|  #  | Текущее      |   Минимальное    |   Максимальное    |   Порог   |
|     | Current Val  |   Min (black)    |   Max (white)     |   Border  |
+-----+--------------+------------------+-------------------+-----------+
| IR1 |239		     | 232		        | 	272			    | 	251		|
| IR2 |238		     | 230		        | 	274			    | 	251		|
| IR3 |236		     | 229		        | 	346			    | 	281		|
| IR4 |233		     | 226		        | 	326			    | 	271		|
| IR5 |232		     | 226		        | 	269			    | 	247		|
+-----+--------------+------------------+-------------------+-----------+
```
For this function to work, the controller must remain connected to the PC and the serial monitor in Arduino IDE must be opened.

***The function runs infinitely! No code below the function call will be executed!***

After obtaining the necessary calibration values, don’t forget to delete or comment out the function after adding them to the code!
