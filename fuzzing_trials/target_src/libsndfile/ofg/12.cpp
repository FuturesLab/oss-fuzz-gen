#include <sndfile.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h> // Include for close()

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Temporary file setup
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

    // Write the input data to the temporary file
    fwrite(data, 1, size, file);
    fflush(file);
    rewind(file);

    // Initialize SF_INFO structure
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));

    // Open the file with libsndfile
    SNDFILE *sndfile = sf_open_fd(fd, SFM_WRITE, &sfinfo, 0);
    if (!sndfile) {
        fclose(file);
        return 0;
    }

    // Prepare double array
    double buffer[1024];
    size_t count = size / sizeof(double);
    if (count > 1024) {
        count = 1024;
    }

    // Copy data into the double buffer
    memcpy(buffer, data, count * sizeof(double));

    // Call the function-under-test
    sf_count_t written = sf_write_double(sndfile, buffer, (sf_count_t)count);

    // Cleanup
    sf_close(sndfile);
    fclose(file);
    remove(tmpl);

    return 0;
}