#ifndef VISUAL_H_INCLUDED
#define VISUAL_H_INCLUDED

// void audio_processor(void* buffer, unsigned int buffer_sz);

void draw_visualizer(float, int, int);
void init_visualizer();
void deinit_visualizer();

typedef void (*hello_t)(void);

typedef void (*draw_t)(float, int, int);
typedef void (*init_t)(void);
typedef void (*deinit_t)(void);

#endif
