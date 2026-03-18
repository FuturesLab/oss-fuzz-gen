#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract both hid_t and a string
    if (size < sizeof(hid_t) + 1) {
        return 0;
    }

    // Extract hid_t from the input data
    hid_t attribute_id;
    memcpy(&attribute_id, data, sizeof(hid_t));

    // Extract a string from the remaining input data
    const char *attr_name = (const char *)(data + sizeof(hid_t));

    // Ensure the string is null-terminated
    size_t remaining_size = size - sizeof(hid_t);
    char *null_terminated_attr_name = (char *)malloc(remaining_size + 1);
    if (null_terminated_attr_name == NULL) {
        return 0;
    }
    memcpy(null_terminated_attr_name, attr_name, remaining_size);
    null_terminated_attr_name[remaining_size] = '\0';

    // Call the function-under-test
    herr_t result = H5Adelete(attribute_id, null_terminated_attr_name);

    // Free allocated memory
    free(null_terminated_attr_name);

    return 0;
}