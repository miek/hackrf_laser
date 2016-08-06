#include <stdint.h>

#define DAC_ADDR_A   0b000
#define DAC_ADDR_B   0b001
#define DAC_ADDR_C   0b010
#define DAC_ADDR_D   0b011
#define DAC_ADDR_ALL 0b100

#define DAC_RANGE_POS_5    0
#define DAC_RANGE_POS_10   1
#define DAC_RANGE_POS_10_8 2
#define DAC_RANGE_5        3
#define DAC_RANGE_10       4
#define DAC_RANGE_10_8     5

int ad5724_init(void);
int ad5724_set_xy(int16_t x, int16_t y);
