#include <stdint.h>
#include <stdlib.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract parameters
    if (size < 10) {
        return 0;
    }

    // Extract parameters from the input data
    hid_t loc_id = (hid_t)data[0];
    const char *old_name = (const char *)(data + 1);
    const char *new_name = (const char *)(data + 2);
    hid_t es_id = (hid_t)data[3];

    // Ensure strings are null-terminated
    char old_name_buf[2];
    char new_name_buf[2];

    old_name_buf[0] = old_name[0];
    old_name_buf[1] = '\0';

    new_name_buf[0] = new_name[0];
    new_name_buf[1] = '\0';

    // Call the function under test
    herr_t result = H5Arename_async(loc_id, old_name_buf, new_name_buf, es_id);

    return 0;
}