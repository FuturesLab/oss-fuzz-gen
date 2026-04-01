extern "C" {
#include <sndfile.h>
#include <unistd.h>  // For close() and unlink()
}

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Create a temporary file to use with SNDFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Define the SF_INFO structure
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));

    // Set some default values for the SF_INFO structure
    sfinfo.samplerate = 44100;
    sfinfo.channels = 2;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    // Open the temporary file with sf_open_fd
    SNDFILE *sndfile = sf_open_fd(fd, SFM_WRITE, &sfinfo, 1);
    if (!sndfile) {
        close(fd);
        return 0;
    }

    // Ensure the data size is a multiple of sizeof(float)
    size_t float_count = size / sizeof(float);
    float *float_data = reinterpret_cast<float *>(const_cast<uint8_t *>(data));

    // Call the function-under-test
    sf_count_t written = sf_write_float(sndfile, float_data, static_cast<sf_count_t>(float_count));

    // Clean up
    sf_close(sndfile);
    close(fd);
    unlink(tmpl);

    return 0;
}