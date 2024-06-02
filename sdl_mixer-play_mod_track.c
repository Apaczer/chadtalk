#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>

// Function to play a music MOD file
int play_music(const char *filename) {
    Mix_Music *music = Mix_LoadMUS(filename);
    if (!music) {
        fprintf(stderr, "Mix_LoadMUS(\"%s\"): %s\n", filename, Mix_GetError());
        return 1;
    }
    if (Mix_PlayMusic(music, 1) == -1) {
        fprintf(stderr, "Mix_PlayMusic: %s\n", Mix_GetError());
        Mix_FreeMusic(music);
        return 1;
    }
    printf("Playing: %s\n", filename);
    SDL_Delay(5000); // Delay to allow music to play for 5 seconds
    Mix_FreeMusic(music);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <music-file>\n", argv[0]);
        return 1;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        fprintf(stderr, "Mix_OpenAudio: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }

    // Check if the given file can be played
    for (int i = 1; i < argc; i++) {
        if (play_music(argv[i]) != 0) {
            fprintf(stderr, "Failed to play %s\n", argv[i]);
        }
    }

    // Clean up
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}

