#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    Bool root_meta = 1; // Initialize with a non-zero value
    u32 track_num = 1; // Initialize with a non-zero value
    char outName[] = "output.xml"; // Output file name
    Bool is_binary = 0; // Initialize with a zero value

    // Create a temporary file to simulate an ISO media file
    char tempFileName[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tempFileName);
    if (fd == -1) {
        return 0;
    }
    write(fd, data, size);
    close(fd);

    // Open the ISO media file
    file = gf_isom_open(tempFileName, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        remove(tempFileName);
        return 0;
    }

    // Call the function-under-test
    gf_isom_extract_meta_xml(file, root_meta, track_num, outName, &is_binary);

    // Clean up
    gf_isom_close(file);
    remove(tempFileName);

    return 0;
}