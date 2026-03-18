#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    u32 track = 0;
    FILE *temp_file = NULL;
    char temp_filename[] = "/tmp/fuzz_input_XXXXXX";

    // Ensure that the size is sufficient to extract a track number
    if (size < sizeof(u32)) {
        return 0;
    }

    // Create a temporary file to write the input data
    int fd = mkstemp(temp_filename);
    if (fd == -1) {
        return 0; // Exit if the temporary file could not be created
    }

    // Write the input data to the temporary file
    temp_file = fdopen(fd, "wb");
    if (!temp_file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, temp_file);
    fclose(temp_file);

    // Initialize the GF_ISOFile structure using the temporary file
    file = gf_isom_open(temp_filename, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        remove(temp_filename); // Clean up the temporary file
        return 0; // Exit if the file could not be opened
    }

    // Extract a track number from the data
    track = *((u32 *)data);

    // Call the function-under-test
    gf_isom_find_od_id_for_track(file, track);

    // Clean up
    gf_isom_close(file);
    remove(temp_filename); // Clean up the temporary file

    return 0;
}