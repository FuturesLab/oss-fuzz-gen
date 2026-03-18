#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *the_file = NULL;
    u32 trackNumber = 1; // Using 1 as a non-zero default value
    u32 StreamDescriptionIndex = 1; // Using 1 as a non-zero default value

    // Create a temporary file to simulate the ISO file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Exit if unable to create a temporary file
    }
    close(fd);

    // Write the fuzz data to the temporary file
    FILE *file = fopen(tmpl, "wb");
    if (file == NULL) {
        return 0; // Exit if unable to open the temporary file
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the ISO file using the GPAC library
    the_file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (the_file == NULL) {
        remove(tmpl); // Clean up the temporary file
        return 0; // Exit if unable to open the ISO file
    }

    // Call the function-under-test
    gf_isom_check_data_reference(the_file, trackNumber, StreamDescriptionIndex);

    // Clean up
    gf_isom_close(the_file);
    remove(tmpl); // Remove the temporary file

    return 0;
}