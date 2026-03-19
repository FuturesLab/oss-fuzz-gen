#include <sndfile.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for close()

extern "C" {
    int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
        // Create a temporary file to write the input data
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd < 0) {
            return 0;
        }

        // Write the input data to the temporary file
        FILE *file = fdopen(fd, "wb");
        if (!file) {
            close(fd);
            return 0;
        }
        fwrite(data, 1, size, file);
        fclose(file);

        // Open the temporary file with libsndfile
        SF_INFO sfinfo;
        memset(&sfinfo, 0, sizeof(SF_INFO));
        SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
        if (!sndfile) {
            remove(tmpl);
            return 0;
        }

        // Prepare a buffer to read samples into
        sf_count_t frames_to_read = 1024; // Arbitrary number of frames to read
        short *buffer = new short[frames_to_read * sfinfo.channels]; // Allocate buffer for samples

        // Call the function-under-test
        sf_count_t frames_read = sf_read_short(sndfile, buffer, frames_to_read);

        // Clean up
        delete[] buffer;
        sf_close(sndfile);
        remove(tmpl);

        return 0;
    }
}