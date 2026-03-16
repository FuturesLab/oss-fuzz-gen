#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    hid_t loc_id = 1;  // Assuming a valid location ID for testing
    hid_t lapl_id = H5P_DEFAULT;  // Use the default link access property list

    // Ensure size is sufficient for creating strings
    if (size < 2) return 0;

    // Create strings from the input data
    size_t name_len = size / 2;
    size_t attr_name_len = size - name_len;

    char *name = (char *)malloc(name_len + 1);
    char *attr_name = (char *)malloc(attr_name_len + 1);

    // Copy data into strings and null-terminate them
    memcpy(name, data, name_len);
    name[name_len] = '\0';

    memcpy(attr_name, data + name_len, attr_name_len);
    attr_name[attr_name_len] = '\0';

    // Call the function-under-test
    htri_t result = H5Aexists_by_name(loc_id, name, attr_name, lapl_id);

    // Clean up
    free(name);
    free(attr_name);

    return 0;
}