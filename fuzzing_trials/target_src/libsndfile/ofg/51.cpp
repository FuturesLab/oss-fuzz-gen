#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for write() and close()

extern "C" {
    #include <sndfile.h>
}

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Temporary file creation
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the file with libsndfile for reading
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(sfinfo));
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Prepare a buffer for short samples
    sf_count_t frame_count = size / sizeof(short);
    short *buffer = reinterpret_cast<short *>(malloc(frame_count * sizeof(short)));
    if (buffer == nullptr) {
        sf_close(sndfile);
        remove(tmpl);
        return 0;
    }

    // Read data from the file into the buffer
    sf_readf_short(sndfile, buffer, frame_count);

    // Clean up
    free(buffer);
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}