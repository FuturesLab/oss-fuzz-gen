#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = NULL;
    u32 trackNumber = 1; // Initialize with a valid track number
    u32 sampleNumber = 1; // Initialize with a valid sample number

    // Ensure size is sufficient to create a valid ISOFile
    if (size < 8) return 0;

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;

    // Write the data to the temporary file
    write(fd, data, size);
    close(fd);

    // Open the ISO file from the temporary file
    movie = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Call the function under test
    gf_isom_remove_sample(movie, trackNumber, sampleNumber);

    // Cleanup
    gf_isom_close(movie);
    unlink(tmpl);
    
    return 0;
}