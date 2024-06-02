#include <iostream>
#include <sndfile.h>

static unsigned char wav_array[/*lenght of array*/] = /*byte array*/

void writeWAV(const unsigned char* buffer, int bufferSize) {
    SF_INFO sfinfo;
    sfinfo.channels = 2; // Mono audio
    sfinfo.samplerate = 22050; // Sample rate (adjust as needed)
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16; // WAV format, 16-bit PCM

    const char* path = "output.wav"; // Specify the full path to the output file
    SNDFILE* outfile = sf_open(path, SFM_WRITE, &sfinfo);

    if (outfile) {
        sf_count_t count = sf_write_short(outfile, reinterpret_cast<const short*>(buffer), bufferSize);
        sf_write_sync(outfile);
        sf_close(outfile);
        std::cout << "WAV file written successfully." << std::endl;
    } else {
        std::cerr << "Error opening the output WAV file." << std::endl;
    }
}

int main() {
    // Example usage:
    int dataSize = sizeof(wav_array) / sizeof(wav_array[0]);
    writeWAV(wav_array, dataSize);

    return 0;
}

