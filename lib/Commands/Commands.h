#include <FastLED.h>

// trunk config
#define TRUNK_PIN_1 25
#define TRUNK_PIN_2 26
#define HW_TRUNK_PIXEL_COUNT 100
#define HW_TRUNK_STRIP_COUNT 2
#define TRUNK_PIXEL_COUNT 50
#define TRUNK_STRIP_COUNT 4

// branch config
#define BRANCH_PIN_1 4
#define BRANCH_PIN_2 12
#define BRANCH_PIN_3 13
#define BRANCH_PIN_4 14
#define BRANCH_PIN_5 15
#define BRANCH_PIN_6 21
#define BRANCH_PIXEL_COUNT 100
#define BRANCH_STRIP_COUNT 6
#define BRANCH_OFFSET 50

// strip index
#define STRIP_INDEX_ALL_TRUNKS 10
#define STRIP_INDEX_ALL_BRANCHES 11
#define STRIP_INDEX_ALL 12

// colors
#define HUE_RED 0
#define HUE_YELLOW 42
#define HUE_GREEN 85
#define HUE_BLUE  171
#define HUE_PINK 213
#define COLOR_BLACK CHSV(0, 0, 0)
#define COLOR_WHITE CRGB(255, 255, 255)

// commands
#define COMMAND_MAX_DATA 8
#define COMMAND_BUFFER_SIZE 16

// effect config
#define DEFAULT_SATURATION 255
#define DEFAULT_VALUE 255

#define MAX_GRAVITY_BALLS 50
#define GRAVITY_VALUE 50
#define GRAVITY_DAMPING 70
// #define GRAVITY_VALUE 18
// #define GRAVITY_DAMPING 100
#define MAX_SPARKLES 200

struct Command {
  uint8_t index;
  uint8_t type;
  char data[COMMAND_MAX_DATA];
};

// -- COMMANDS -----------------------------------------------------------------------
// All commands take a pointer to a buffer with its parameters.
// The comments indicate which data is expected at a certain byte index

#define DISABLE             0   
#define SINGLE_HUE          1   
#define SINGLE_COLOR        2   
#define COLOR_WIPE          3   
#define RAINBOW_SINE        4   
#define PING_PONG           5   
#define GRAVITY             6   
#define OFF                 7   
#define WHITE               8   
#define SPARKLE             9   

// -- EVENTS --------------------------------------------------------------------------

#define GRAVITY_EVENT       100

class Commands {
   public:
     Commands();
     void process(char* command);
     void init();
     void start_sequence();
     void run();

   private:
     // commands
     void single_hue(char* data);
     void single_color(char* data);
     void color_wipe(char* data);
     void rainbow_sine(char* data);
     void ping_pong(char* data);
     void gravity(char* data);
     void off(char* data);
     void white(char* data);
     void sparkle(char* data);

     // events
     void gravity_event();
};
