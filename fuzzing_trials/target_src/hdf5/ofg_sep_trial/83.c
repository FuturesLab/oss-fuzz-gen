#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the parameters
    if (size < 3) {
        return 0;
    }

    // Extract parameters from the input data
    hid_t loc_id = (hid_t)data[0];
    hid_t lapl_id = (hid_t)data[1];

    // Ensure null-terminated strings for name and attr_name
    size_t name_len = data[2] % (size - 2);
    size_t attr_name_len = (size - 3) - name_len;

    char *name = (char *)malloc(name_len + 1);
    char *attr_name = (char *)malloc(attr_name_len + 1);

    if (name == NULL || attr_name == NULL) {
        free(name);
        free(attr_name);
        return 0;
    }

    memcpy(name, &data[3], name_len);
    name[name_len] = '\0';

    memcpy(attr_name, &data[3 + name_len], attr_name_len);
    attr_name[attr_name_len] = '\0';

    // Call the function-under-test
    htri_t result = H5Aexists_by_name(loc_id, name, attr_name, lapl_id);

    // Clean up
    free(name);
    free(attr_name);

    return 0;
}