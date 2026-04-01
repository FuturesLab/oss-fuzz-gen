#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring> // Include for memset

extern "C" {
    #include <sndfile.h>
}

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Temporary file creation
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    
    // Write data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) { // Cast size to match ssize_t
        close(fd);
        unlink(tmpl);
        return 0;
    }
    
    // Rewind the file descriptor to the beginning
    lseek(fd, 0, SEEK_SET);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open_fd(fd, SFM_READ, &sfinfo, 0);
    if (sndfile == NULL) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Initialize SF_CHUNK_INFO for testing
    SF_CHUNK_INFO chunk_info;
    memset(chunk_info.id, 0, sizeof(chunk_info.id));  // Correctly initialize the id
    chunk_info.datalen = 0;  // Example value, adjust as necessary
    chunk_info.data = NULL;  // Example value, adjust as necessary

    // Call the function-under-test
    SF_CHUNK_ITERATOR *iterator = sf_get_chunk_iterator(sndfile, &chunk_info);

    // Clean up
    if (iterator != NULL) {
        sf_next_chunk_iterator(iterator);
    }
    sf_close(sndfile);
    close(fd);
    unlink(tmpl);

    return 0;
}