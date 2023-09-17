#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "raylib.h"

#include "app.h"

int main(void) {
    init();
    while (!WindowShouldClose())
        update(), draw();
    deinit();
    return 0;
}
