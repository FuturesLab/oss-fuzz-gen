#include <stdint.h>
#include <stdlib.h>
#include "sndfile.h"
#include <unistd.h>  // Include this for the 'close' function

extern "C" {
    #include "sndfile.h"  // Ensure all C headers are wrapped in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to split into meaningful parts
    if (size < 5) {
        return 0;
    }

    // Open a temporary file to use with SNDFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Close the file descriptor as we will use the filename
    close(fd);

    // Create a fake SF_INFO structure
    SF_INFO sfinfo;
    sfinfo.frames = 0;
    sfinfo.samplerate = 44100;
    sfinfo.channels = 2;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    sfinfo.sections = 1;
    sfinfo.seekable = 1;

    // Open the file with sf_open for reading and writing
    SNDFILE *sndfile = sf_open(tmpl, SFM_RDWR, &sfinfo);
    if (sndfile == NULL) {
        // Clean up the temporary file
        remove(tmpl);
        return 0;
    }

    // Use the first byte of data to determine the command
    int command = data[0];

    // Use the rest of the data as a string for the function
    const char *str = (const char *)(data + 1);

    // Call the function-under-test
    sf_set_string(sndfile, command, str);

    // Clean up
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}