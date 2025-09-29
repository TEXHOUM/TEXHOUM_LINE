#include <TEXHOUM_LINE.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(IR1.get());
}
