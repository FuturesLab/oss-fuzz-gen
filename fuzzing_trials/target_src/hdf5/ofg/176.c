#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_176(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    hid_t loc_id = H5Fopen("testfile.h5", H5F_ACC_RDONLY, H5P_DEFAULT);
    if (loc_id < 0) {
        return 0; // Unable to open file, exit early
    }

    // Ensure data is large enough to extract meaningful strings
    if (size < 2) {
        H5Fclose(loc_id);
        return 0;
    }

    // Extract strings from the input data
    size_t name_len = data[0] % (size - 1) + 1;
    size_t attr_name_len = data[1] % (size - name_len - 1) + 1;

    char *name = (char *)malloc(name_len + 1);
    char *attr_name = (char *)malloc(attr_name_len + 1);

    if (name == NULL || attr_name == NULL) {
        free(name);
        free(attr_name);
        H5Fclose(loc_id);
        return 0;
    }

    memcpy(name, data + 2, name_len);
    name[name_len] = '\0';

    memcpy(attr_name, data + 2 + name_len, attr_name_len);
    attr_name[attr_name_len] = '\0';

    H5A_info_t ainfo;
    hid_t lapl_id = H5P_DEFAULT;

    // Call the function-under-test
    herr_t result = H5Aget_info_by_name(loc_id, name, attr_name, &ainfo, lapl_id);

    // Clean up
    free(name);
    free(attr_name);
    H5Fclose(loc_id);

    return 0;
}