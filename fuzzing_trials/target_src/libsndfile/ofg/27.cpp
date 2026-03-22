extern "C" {
    #include <sndfile.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>  // Include unistd.h for the close() function
    #include <string.h>  // Include string.h for the memcpy() function
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Define and initialize variables before goto
    SNDFILE *sndfile = NULL;
    SF_INFO sfinfo;
    float *float_data = NULL;
    sf_count_t frames_written = 0;

    // Ensure we have enough data to work with
    if (size < sizeof(float)) {
        return 0;
    }

    // Initialize SF_INFO structure
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    sfinfo.channels = 1;
    sfinfo.samplerate = 44100;

    // Create a temporary file to use with the SNDFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Open the sound file
    sndfile = sf_open_fd(fd, SFM_WRITE, &sfinfo, 1);
    if (sndfile == NULL) {
        close(fd);
        return 0;
    }

    // Allocate memory for float data
    float_data = (float *)malloc(size);
    if (float_data == NULL) {
        sf_close(sndfile);
        close(fd);
        return 0;
    }

    // Copy the input data to the float array
    for (size_t i = 0; i < size / sizeof(float); ++i) {
        // Use memcpy to avoid alignment issues and const cast
        memcpy(&float_data[i], &data[i * sizeof(float)], sizeof(float));
    }

    // Call the function-under-test
    frames_written = sf_writef_float(sndfile, float_data, size / sizeof(float));

    // Clean up resources
    free(float_data);
    sf_close(sndfile);
    close(fd);

    return 0;
}