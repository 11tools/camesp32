#ifndef _TVP5150_SETTINGS_H_
#define _TVP5150_SETTINGS_H_

#include <stdint.h>
#include <stdbool.h>
#include "esp_attr.h"
#include "tvp5150_regs.h"

typedef enum {
    TVP5150_MODE_UXGA, TVP5150_MODE_SVGA, TVP5150_MODE_CIF, TVP5150_MODE_MAX
} tvp5150_sensor_mode_t;


#endif //_TVP5150_SETTINGS_H_
