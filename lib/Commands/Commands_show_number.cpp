#include <Commands.h>

void Commands::show_number(char * data) {
  uint8_t strip_index = data[0];
  uint8_t number = data[1];

  uint8_t hundrets = number / 100;
  uint8_t tens = (number % 100) / 10;
  uint8_t ones = (number % 10);

  // hundrets - red
  for (int i=0; i<hundrets; i++) {
    set_led(strip_index, i, CRGB(255, 0, 0));
  }
  
  // tens - green
  for (int i=hundrets; i<hundrets+tens; i++) {
    set_led(strip_index, i, CRGB(0, 255, 0));
  }
  
  // ones - blue
  for (int i=hundrets+tens; i<hundrets+tens+ones; i++) {
    set_led(strip_index, i, CRGB(0, 0, 255));
  }
}