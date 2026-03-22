#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sndfile.h>

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Initialize variables
    SNDFILE *sndfile = nullptr;
    SF_INFO sfinfo;
    SF_CHUNK_INFO chunk_info;
    SF_VIRTUAL_IO sf_virtual_io;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    memset(&chunk_info, 0, sizeof(SF_CHUNK_INFO));
    memset(&sf_virtual_io, 0, sizeof(SF_VIRTUAL_IO));

    // Create a temporary file in memory
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Rewind the file descriptor to the beginning
    lseek(fd, 0, SEEK_SET);

    // Open the temporary file as a sound file
    sndfile = sf_open_fd(fd, SFM_READ, &sfinfo, 0);
    if (sndfile == nullptr) {
        close(fd);
        return 0;
    }

    // Set up the chunk_info with some dummy data
    strncpy(chunk_info.id, "title", sizeof(chunk_info.id) - 1); // Use a valid chunk ID
    chunk_info.id[sizeof(chunk_info.id) - 1] = '\0'; // Ensure null termination
    chunk_info.datalen = size;
    chunk_info.data = (void *)data;

    // Call the function-under-test
    sf_set_chunk(sndfile, &chunk_info);

    // Clean up
    sf_close(sndfile);
    close(fd);
    unlink(tmpl);

    return 0;
}