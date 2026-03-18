#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate opening from memory
    char tmp_filename[] = "tempfileXXXXXX";
    int fd = mkstemp(tmp_filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        remove(tmp_filename);
        return 0;
    }
    close(fd);

    // Open the ISO file using the temporary file
    GF_ISOFile *file = gf_isom_open(tmp_filename, GF_ISOM_OPEN_READ, NULL);
    remove(tmp_filename); // Remove the temporary file

    if (!file) {
        return 0;
    }

    u32 track = 1; // Assuming track 1 for testing purposes
    Bool use_negative_offsets = GF_TRUE; // Use negative offsets as a test case

    // Call the function under test
    gf_isom_set_composition_offset_mode(file, track, use_negative_offsets);

    // Clean up
    gf_isom_close(file);

    return 0;
}