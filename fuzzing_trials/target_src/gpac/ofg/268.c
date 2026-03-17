#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <string.h>

int LLVMFuzzerTestOneInput_268(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated by copying it to a new buffer
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    GF_ISOFile *file = gf_isom_open(null_terminated_data, GF_ISOM_OPEN_READ, NULL);
    free(null_terminated_data);  // Free the buffer after use

    if (file == NULL) {
        return 0;
    }

    // Ensure root_meta is not NULL by setting it to a boolean value
    Bool root_meta = GF_TRUE;

    // Set track_num to a valid non-zero value
    u32 track_num = 1;

    // Call the function-under-test
    gf_isom_remove_meta_xml(file, root_meta, track_num);

    // Clean up
    gf_isom_close(file);

    return 0;
}