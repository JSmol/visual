#include "app.h"
#include "raylib.h"
#include "visual.h"

#include <math.h>
#include <stdio.h>

int width = 1920;
int height = 1080;
bool pause = 0;

// TODO: Dynamically update (drag + drop?) files
const int n_files = 75;
int fileidx = 0;
char* filepaths[] = {
    "/home/josip/visual/music/047 - General Error [wUDfV628li0].wav",
    "/home/josip/visual/music/8-Bit Tunes： Evanescence - Bring me to Life [y5r3PY9nr4w].wav",
    "/home/josip/visual/music/8-bit Chiptune - Townmusic Chiptune version [FHFl1erOtBk].wav",
    "/home/josip/visual/music/Anamanaguchi -「ENDLESS FANTASY」(Official Music Video) [6fdr-Fiv92c].wav",
    "/home/josip/visual/music/Bach Air 8-bit cover [LK54Lt_ULwI].wav",
    "/home/josip/visual/music/Best Relaxing Keygen Song [gAMU3fbSAZQ].wav",
    "/home/josip/visual/music/Bossfight - The Maze Of Mayonnaise [57c94il3Eng].wav",
    "/home/josip/visual/music/British National Anthem (8-bit remix) [GCU4t-onRmg].wav",
    "/home/josip/visual/music/Caprice No. 24 - 8 Bit - Niccolò Paganini [o5P2oygZ9s0].wav",
    "/home/josip/visual/music/Chiptune David - Where Am I [GlfXRtVv_Jw].wav",
    "/home/josip/visual/music/Classical music 8 bit arrange medley [EaZZr7W92lc].wav",
    "/home/josip/visual/music/Coda - Dorito dust [vBK0bxuDfs8].wav",
    "/home/josip/visual/music/Darkman007 - Grass near the house [OQnJ9m94dbI].wav",
    "/home/josip/visual/music/Darkman007 - Mr. Droichen [eSWbhBm-4v0].wav",
    "/home/josip/visual/music/Darkman007 - Pill of sorrow [yrJU9E2s-Gk].wav",
    "/home/josip/visual/music/Darkman007 - Sad song [ugz0vr3Eeik].wav",
    "/home/josip/visual/music/Douchebag Rumble (Chiptune) [k2jQyVDbjNQ].wav",
    "/home/josip/visual/music/Drax - Promises [hoSG19-YOvw].wav",
    "/home/josip/visual/music/Dualtrax and Artfx! - Super RobCo Disco Battle [84aM-mNzagw].wav",
    "/home/josip/visual/music/Dubmood - 3D Galax [E-lPrWLzGSM].wav",
    "/home/josip/visual/music/Dubmood - Mario airlines [qubqBXWuLN4].wav",
    "/home/josip/visual/music/DuckTales Music (NES) - The Moon Theme [KF32DRg9opA].wav",
    "/home/josip/visual/music/Edzes - Fish and chips [oAA8C2nQqUA].wav",
    "/home/josip/visual/music/Evanescence - My Immortal ( 8 Bit Mix ) [p-anFCZLdb8].wav",
    "/home/josip/visual/music/Evolution of Video Games Epic Medley (Made in Mario Paint Composer) [AbO1YtoUqM8].wav",
    "/home/josip/visual/music/Fearofdark - Dancing 0n the m%n [vwKycWY4lV8].wav",
    "/home/josip/visual/music/Floppi and Zalza - Snowballs with attitude [zLdlRxdH5pE].wav",
    "/home/josip/visual/music/Gary Jules - Mad World(8bit) [B_xnkegXtXA].wav",
    "/home/josip/visual/music/Goto80 - Blox [KCjNzZZXep4].wav",
    "/home/josip/visual/music/Goto80 - Fantasy [6MIisq9Rs1g].wav",
    "/home/josip/visual/music/Ievan Polkka 8-Bit Chiptune [ugubU4DakOM].wav",
    "/home/josip/visual/music/Instant Remedy - Ocean Loader [UEst0w7JdT8].wav",
    "/home/josip/visual/music/Jayster -  Sunrise to sunset [CwQLxmqhuMA].wav",
    "/home/josip/visual/music/Karloz - I want sleep! [QMj9CVt227Y].wav",
    "/home/josip/visual/music/Keygen Songs Mix [Best Of] [j1yiPXHujDQ].wav",
    "/home/josip/visual/music/Kid Icarus (NES) Music - Underworld Theme [kUBsXUt5RQE].wav",
    "/home/josip/visual/music/Kubbi - Cascade [ECqoSyGnbAo].wav",
    "/home/josip/visual/music/Kubbi ⧸ Juggernaut [ByKCPbScgsU].wav",
    "/home/josip/visual/music/Laffe the Fox & Zalza - Cats Don'\''t Play Video Games [pWn8l4dVdtg].wav",
    "/home/josip/visual/music/Legion (Chiptune⧸Chiprock) [S9X1W0mrggc].wav",
    "/home/josip/visual/music/LoZ： The Wind Waker - 8-bit Outset Island on Famitracker [k1sBipGT6zY].wav",
    "/home/josip/visual/music/Loopability by MotionRide [bi5OZBZZ6eE].wav",
    "/home/josip/visual/music/Lukas Eriksson - Space delivery [8dz6frhQUbU].wav",
    "/home/josip/visual/music/Marx Marvelous - Boner [cIAKyN7e8j8].wav",
    "/home/josip/visual/music/Megaman Battle Network Internet Themes 1-6 (including 4.5) [IcWzzcibyHo].wav",
    "/home/josip/visual/music/Metallica One (8 Bit Remix) [jdtGtNZdk4I].wav",
    "/home/josip/visual/music/Mr. Gamer - Höstlov [mM01YcefI7w].wav",
    "/home/josip/visual/music/Mr. Gamer - Mr. Gamer'\''s zelda [Gkp4EhagOAA].wav",
    "/home/josip/visual/music/Naruto - Artificial intelligence bomb [gyQ9UHPwW4g].wav",
    "/home/josip/visual/music/OH MY DAYUM 8 Bit - Songify This Remix [nU8ZimUZVfA].wav",
    "/home/josip/visual/music/Original - Runnin'\'' Through Castles (FamiTracker) [EdYjZ0kf95w].wav",
    "/home/josip/visual/music/Pokemon Blue⧸Red - Pokemon Center [MjZIjHu0OfY].wav",
    "/home/josip/visual/music/Pokemon Gold Silver Crystal - National Park [0ftbje_15ck].wav",
    "/home/josip/visual/music/Pokemon Ruby⧸Sapphire⧸Emerald- Route 110 [dKW-reR_jUQ].wav",
    "/home/josip/visual/music/Pokémon RSE - Petalburg City (8-bit Remix) [xbXcBhpkY-U].wav",
    "/home/josip/visual/music/Pokémon R⧸B⧸Y - Viridian Forest on Famitracker [XkO4vYm4wfw].wav",
    "/home/josip/visual/music/Pokémon X⧸Y Bicycle Theme 8 Bit [hwfziTcScv8].wav",
    "/home/josip/visual/music/Random chiptune mix 11 [mK_qinhMAWI].wav",
    "/home/josip/visual/music/Random chiptune mix 13 [HIWVKe2YtUg].wav",
    "/home/josip/visual/music/Robert Miles - Children ( Dj CUTMAN Chiptune Trance Remix ) [XHUjWhuXaXw].wav",
    "/home/josip/visual/music/Runescape 8-bit music - Harmony [GeLasFiYRy0].wav",
    "/home/josip/visual/music/Rushjet1 - Prelude & Fugue in C Minor (Bach) [muaf1dBqDgI].wav",
    "/home/josip/visual/music/Slash - A ghost, dreaming [dFYEmG5mb64].wav",
    "/home/josip/visual/music/Super Mario Bros. 2 Music - Main Theme ⧸ Overworld [j9s4fuOL3FM].wav",
    "/home/josip/visual/music/Super Smash Bros. Brawl Theme 8 Bit Remix [EfzefeBpNY4].wav",
    "/home/josip/visual/music/The Entertainer 8 Bit Remix - Scott Joplin [hTZ-zQInMsk].wav",
    "/home/josip/visual/music/Trash80 - Icarus [8DA8CchVOn0].wav",
    "/home/josip/visual/music/Turkish March 8 Bit Remix - Mozart [vQhxA3M-AEc].wav",
    "/home/josip/visual/music/Various artists - The megatune [rGUtixaYw7w].wav",
    "/home/josip/visual/music/Vocaloid - Meltdown 8-bit [Lx7V9rtHyjw].wav",
    "/home/josip/visual/music/Zalza - Back to the chipland [RiP7l6XKrOc].wav",
    "/home/josip/visual/music/Zalza - The Original 2204355 Chicken Man Song (Free download) [AKxQvrrVFPU].wav",
    "/home/josip/visual/music/iPhone Marimba 8-bit ⧸chiptune⧸ remix [ISSuJHmcY0o].wav",
    "/home/josip/visual/music/nes collections - bionic commando - main theme [2hl5UCCBCXI].wav",
    "/home/josip/visual/music/＂Unreal Super Hero 3＂ by Kenet & Rez [9STiQ8cCIo0].wav",
};

Music music;

void init_music() {
    music = LoadMusicStream(filepaths[0]);
    PlayMusicStream(music);
}

#include <stddef.h>
#include <dlfcn.h>
const char* fn = "include/visual.so";
void* lib = NULL;
draw_t vis_draw = NULL;
init_t vis_init = NULL;
deinit_t vis_deinit = NULL;
void reload() {
    if (lib) dlclose(lib);

    lib = dlopen(fn, RTLD_NOW);
    if (lib == NULL) {
        printf("err %s", dlerror());
        return;
    }

    vis_draw = dlsym(lib, "draw_visualizer");
    vis_init = dlsym(lib, "init_visualizer");
    vis_deinit = dlsym(lib, "deinit_visualizer");
    if (!(vis_draw && vis_init && vis_deinit)) {
        printf("ERR LOADING FUNCTIONS");
        return;
    }
}

void init() {
    TraceLog(LOG_INFO, "init started");
    reload();

    InitWindow(width, height, "visual");
    SetWindowPosition(400, 1200);
    SetTargetFPS(60);
    InitAudioDevice();
    init_music();
    vis_init();

    SetExitKey(KEY_NULL);
}

void deinit() {
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
    vis_deinit();
}

void change_music() {
    StopMusicStream(music);
    UnloadMusicStream(music);
    music = LoadMusicStream(filepaths[fileidx]);
    PlayMusicStream(music);
}

void handle_input() {
    if (IsKeyPressed(KEY_SPACE)) pause = !pause;
    if (IsKeyPressed(KEY_RIGHT)) {
        fileidx = (fileidx + 1) % n_files;
        change_music();
    }
    if (IsKeyPressed(KEY_LEFT)) {
        fileidx = (fileidx + n_files - 1) % n_files;
        change_music();
    }
    if (IsKeyPressed(KEY_R)) {
        vis_deinit();
        reload();
        vis_init();
    }
    if (IsKeyPressed(KEY_F11)) {
        ToggleFullscreen();
    }
}

void update_audio() {
    if (pause) PauseMusicStream(music);
    else ResumeMusicStream(music);
}

void update() {
    UpdateMusicStream(music);
    handle_input();
    update_audio();
}

void draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    int width = GetScreenWidth();
    int height = GetScreenHeight();
    float time_played = GetMusicTimePlayed(music) / GetMusicTimeLength(music);
    vis_draw(time_played, width, height);

    DrawText(filepaths[fileidx], 10, 10, 24, LIGHTGRAY);
    DrawRectangle(20, height - 20 - 12, width - 40, 12, LIGHTGRAY);
    DrawRectangle(20, height - 20 - 12, (int)((width - 40) * time_played), 12, MAROON);
    DrawRectangleLines(20, height - 20 - 12, width - 40, 12, GRAY);

    EndDrawing();
}
