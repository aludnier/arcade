# pragma once
#include <stddef.h>

#define SCREEN_H 800
#define SCREEN_W 800
#define FRAMELIMITS 60

struct screen {
    size_t h = 1;
    size_t w = 1;
    int ratio = 1;
};
