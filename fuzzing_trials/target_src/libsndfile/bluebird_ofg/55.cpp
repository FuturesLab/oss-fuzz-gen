#include "sndfile.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern "C" {
    #include <unistd.h> // For close() and unlink()
}

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_perror to sf_read_raw
    int ret_sf_current_byterate_tlnwv = sf_current_byterate(sndfile);
    if (ret_sf_current_byterate_tlnwv < 0){
    	return 0;
    }
    int ret_sf_current_byterate_twtee = sf_current_byterate(sndfile);
    if (ret_sf_current_byterate_twtee < 0){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_current_byterate to sf_readf_int
    int ret_sf_error_egufy = sf_error(sndfile);
    if (ret_sf_error_egufy < 0){
    	return 0;
    }

    sf_count_t ret_sf_readf_int_qnthk = sf_readf_int(sndfile, NULL, (int64_t )ret_sf_current_byterate_twtee);
    if (ret_sf_readf_int_qnthk < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t ret_sf_read_raw_xclrc = sf_read_raw(sndfile, (void *)sndfile, (int64_t )ret_sf_current_byterate_twtee);
    if (ret_sf_read_raw_xclrc < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_sf_perror_iecbu = sf_perror(sndfile);
    if (ret_sf_perror_iecbu < 0){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_perror to sf_write_float
    int ret_sf_close_gkziu = sf_close(NULL);
    if (ret_sf_close_gkziu < 0){
    	return 0;
    }

    sf_count_t ret_sf_write_float_cwzfd = sf_write_float(sndfile, NULL, (int64_t )ret_sf_close_gkziu);
    if (ret_sf_write_float_cwzfd < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

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