#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
    // Alternative approach: Write data to a temporary file and open it
    char temp_filename[] = "/tmp/fuzz_temp_file.XXXXXX";
    int fd = mkstemp(temp_filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(temp_filename);
        return 0;
    }
    close(fd);

    // Open the ISO file from the temporary file
    GF_ISOFile *file = gf_isom_open(temp_filename, GF_ISOM_OPEN_READ, NULL);
    if (file == NULL) {
        unlink(temp_filename);
        return 0;
    }

    // Initialize parameters
    Bool root_meta = GF_TRUE; // or GF_FALSE, try both
    u32 track_num = 1; // Assuming at least one track, adjust as needed

    // Call the function-under-test
    gf_isom_remove_meta_xml(file, root_meta, track_num);

    // Clean up
    gf_isom_close(file);
    unlink(temp_filename);

    return 0;
}