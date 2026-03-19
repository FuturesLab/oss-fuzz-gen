#include "sndfile.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern "C" {
    #include <unistd.h> // For close() and unlink()
}

extern "C" int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    SNDFILE *sndfile;
    SF_INFO sfinfo;
    sf_count_t frames_written;
    double *buffer;
    sf_count_t frames;

    // Initialize SF_INFO structure
    memset(&sfinfo, 0, sizeof(SF_INFO));
    sfinfo.samplerate = 44100; // Standard sample rate
    sfinfo.channels = 2;       // Stereo
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16; // WAV format

    // Create a temporary file to write the audio data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb+");
    if (!file) {
        close(fd);
        return 0;
    }

    // Open the temporary file as a sound file
    sndfile = sf_open_fd(fd, SFM_WRITE, &sfinfo, SF_TRUE);
    if (!sndfile) {
        fclose(file);
        return 0;
    }

    // Calculate the number of frames
    frames = size / (sfinfo.channels * sizeof(double)); // Adjust for number of channels
    buffer = (double *)malloc(frames * sfinfo.channels * sizeof(double));
    if (!buffer) {
        sf_close(sndfile);
        fclose(file);
        return 0;
    }

    // Copy data to the buffer
    memcpy(buffer, data, frames * sfinfo.channels * sizeof(double));

    // Call the function-under-test
    frames_written = sf_writef_double(sndfile, buffer, frames);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_writef_double to sf_command
    int ret_sf_perror_wqhmh = sf_perror(sndfile);
    if (ret_sf_perror_wqhmh < 0){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_perror to sf_error_str
    int ret_sf_current_byterate_jvrjz = sf_current_byterate(sndfile);
    if (ret_sf_current_byterate_jvrjz < 0){
    	return 0;
    }

    int ret_sf_error_str_vbrof = sf_error_str(sndfile, NULL, (size_t )ret_sf_current_byterate_jvrjz);
    if (ret_sf_error_str_vbrof < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_sf_perror_iecbu = sf_perror(sndfile);
    if (ret_sf_perror_iecbu < 0){
    	return 0;
    }

    int ret_sf_command_qozyf = sf_command(sndfile, (int )frames_written, (void *)sndfile, ret_sf_perror_iecbu);
    if (ret_sf_command_qozyf < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(buffer);
    sf_close(sndfile);
    fclose(file);
    unlink(tmpl);

    return 0;
}