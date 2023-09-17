#include "visual.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "raylib.h"
#include "helpers.h"

#include <rlgl.h>

#define N_WINDOW 1024
#define NAVG 6
#define NFFT N_WINDOW
#define NHIST 4

float window[2*N_WINDOW];
float fft_buffer[2*NFFT];
float spectrum[NAVG][2*NFFT];
float hist[NHIST][2*NFFT];
float wfn[N_WINDOW];

int sidx = 0, hidx = 0;
float pi = 3.14159265359;

Shader shader;

void log_int(int x) {
    int digits = 8;
    char* str = calloc(digits + 1, sizeof(char));

    if (x < 0) { x = -x; str[0] = '-'; }
    else str[0] = '+';

    for (int i = 0, b = 1; i < digits; i++) {
        str[digits - i] = (x % 10) + '0';
        x /= 10;
    }
    TraceLog(LOG_INFO, str);
    free(str);
}

void audio_processor(void* buffer, unsigned int buffer_sz) {
    float* samples = (float*) buffer;
    int n_samples = buffer_sz;

    // shift samples i + 2n < N 
    for (int i = 0; i < N_WINDOW - n_samples; i++) {
        window[i] = window[n_samples + i];
        window[N_WINDOW + i] = window[N_WINDOW + n_samples + i];
    }

    // enter new samples
    for (int i = 0; i < n_samples; i++) {
        if (2*N_WINDOW - 2*n_samples + 2*i < 0)
            continue;

        float* left = &samples[i * 2 + 0];
        float* right = &samples[i * 2 + 1];
        window[N_WINDOW - n_samples + i] = *left;
        window[2*N_WINDOW - n_samples + i] = *right;
    }

    // real_fft(window, spectrum, n_window);
    // real_fft(window + n_window, spectrum + n_window, n_window);
}

void init_visualizer() {
    TraceLog(LOG_INFO, "initializing visualizer");
    AttachAudioMixedProcessor(audio_processor);
    for (int i = 0; i < N_WINDOW; i++)
        wfn[i] = sin((float)i * pi / (float)N_WINDOW);

    shader = LoadShader(0, "glow.fs");

// RenderTexture2D target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
}

void deinit_visualizer() {
    TraceLog(LOG_INFO, "deinitializing visualizer");
    DetachAudioMixedProcessor(audio_processor);
    UnloadShader(shader);
}

void upd() {
    // TraceLog(LOG_INFO, "upd");

    // TODO: RIGHT CHANNEL
    for (int i = 0; i < NFFT; i++)
        fft_buffer[i] = wfn[i % N_WINDOW] * window[i % N_WINDOW];

    // fft....
    sidx = (sidx + 1) % NAVG;
    real_fft(fft_buffer, spectrum[sidx], NFFT);

    // normalize
    for (int i = 0; i < NFFT; i++) {
        spectrum[sidx][i] = spectrum[sidx][i] * powf(1 + i / (float)(NFFT / 2.f), 2.f);
        spectrum[sidx][i] = logf(1 + spectrum[sidx][i]);
        spectrum[sidx][i] = 1 / (1 + expf(-spectrum[sidx][i])) - 0.45;
    }

    // fix da bass notes
    for (int i = 0; i < NFFT; i++) {
        // spectrum[sidx][i] = sq
    }
}

void draw_visualizer(float time_played, int width, int height) {
    upd();

    hidx = (hidx + 1) % NHIST;
    // int width = GetScreenWidth();
    // int height = GetScreenHeight();

    int N = NFFT / 4;

    // float time_played = 0; // GetMusicTimePlayed(music) / GetMusicTimeLength(music);
    Vector2 c = { width / 2., height / 2. };
    int d1 = 880;

    BeginShaderMode(shader);
    Texture2D texture = { rlGetTextureIdDefault(), 1, 1, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };

    for (int i = 0; i < N; i++) {
        float avg = 0.;
        for (int j = 0; j < NAVG; j++)
            avg += spectrum[j][i];
        avg = (avg / (float)NAVG);

        float p = 1 + 1. / (12. + i);
        avg = powf(avg, p);

        float ang = (1.8*pi) * i / (float)N + time_played * 20;

        float strength = 1.4 * avg * d1;

        float prev = hist[(hidx + NHIST - 1) % NHIST][i];
        float pstrength = 0.5 * avg * d1;
        Vector2 s = { c.x + pstrength*cos(ang), c.y + pstrength*sin(ang) };
        // Vector2 s = { c.x + cos(ang), c.y + sin(ang) };
        float eps = 0.01;
        Vector2 t1 = { c.x + strength*cos(ang+eps), c.y + strength*sin(ang+eps) };
        Vector2 t2 = { c.x + strength*cos(ang-eps), c.y + strength*sin(ang-eps) };

        DrawTriangle(s, t1, t2, 
            ColorFromHSV((float) 2000*time_played + 35 * i / (float) N * 4, 0.6, 1)
        );
    }

    for (int i = 0; i < N; i++) {
        float avg = 0.;
        for (int j = 0; j < NAVG; j++)
            avg += spectrum[j][i];
        avg = (avg / (float)NAVG);

        float p = 1 + 1. / (12. + i);
        avg = powf(avg, p);

        hist[hidx][i] = avg;

        float ang = (1.8*pi) * i / (float)N + time_played * 20;

        float strength = 1.4 * avg * d1;

        Vector2 e = { strength*cos(ang), strength*sin(ang) };
        Vector2 pos = { c.x + e.x, c.y + e.y };

        float sz = fmax(200 / powf((float)(1+i / (float)30), 3/3.f), 1) + 2;
        // sz *= 2 / (1 + expf(-avg));

        Vector2 corner = { pos.x - sz/2, pos.y - sz/2};

        Rectangle r = (Rectangle) {
            .x = corner.x,
            .y = corner.y,
            .width = sz,
            .height = sz
        };

        // Rectangle tail = (Rectangle) {
        //     .x = corner.x,
        //     .y = corner.y,
        // };

        DrawTextureEx(texture, corner, 0, sz,
            ColorFromHSV((float) 2000*time_played + 35 * i / (float) N * 4, 0.6, 1)
        );


    }
    EndShaderMode();

}

