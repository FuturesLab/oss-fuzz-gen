#include <stdint.h>
#include <hdf5.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t loc_id = H5I_INVALID_HID;
    const char *name = NULL;
    bool follow_link = true;
    H5O_info_t statbuf;

    // Ensure size is sufficient to extract a valid string
    if (size < 1) {
        return 0;
    }

    // Create a copy of the data to ensure it is null-terminated
    char *data_copy = (char *)malloc(size + 1);
    if (data_copy == NULL) {
        return 0;
    }
    memcpy(data_copy, data, size);
    data_copy[size] = '\0';

    // Use the copied data as the name
    name = data_copy;

    // Call the function-under-test
    herr_t result = H5Oget_info_by_name(loc_id, name, &statbuf, follow_link ? H5P_DEFAULT : H5O_INFO_BASIC, H5P_DEFAULT);

    // Clean up
    free(data_copy);

    return 0;
}