#include "sndfile.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Temporary file creation for SNDFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Minimal WAV header for a simple mono PCM file
    const uint8_t wav_header[44] = {
        0x52, 0x49, 0x46, 0x46, // "RIFF"
        0x24, 0x08, 0x00, 0x00, // ChunkSize (placeholder)
        0x57, 0x41, 0x56, 0x45, // "WAVE"
        0x66, 0x6D, 0x74, 0x20, // "fmt "
        0x10, 0x00, 0x00, 0x00, // Subchunk1Size (16 for PCM)
        0x01, 0x00,             // AudioFormat (1 for PCM)
        0x01, 0x00,             // NumChannels (1 for mono)
        0x44, 0xAC, 0x00, 0x00, // SampleRate (44100 Hz)
        0x88, 0x58, 0x01, 0x00, // ByteRate (SampleRate * NumChannels * BitsPerSample/8)
        0x02, 0x00,             // BlockAlign (NumChannels * BitsPerSample/8)
        0x10, 0x00,             // BitsPerSample (16 bits)
        0x64, 0x61, 0x74, 0x61, // "data"
        0x00, 0x08, 0x00, 0x00  // Subchunk2Size (placeholder)
    };

    // Write the WAV header to the temporary file
    if (write(fd, wav_header, sizeof(wav_header)) != sizeof(wav_header)) {
        close(fd);
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(sfinfo));
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Prepare a short buffer to read
    sf_count_t frames = size / sizeof(short);
    short *buffer = (short *)malloc(frames * sizeof(short));
    if (buffer == NULL) {
        sf_close(sndfile);
        unlink(tmpl);
        return 0;
    }

    // Call the function under test
    sf_count_t read_frames = sf_read_short(sndfile, buffer, frames);

    // Clean up
    free(buffer);
    sf_close(sndfile);
    unlink(tmpl);

    return 0;
}