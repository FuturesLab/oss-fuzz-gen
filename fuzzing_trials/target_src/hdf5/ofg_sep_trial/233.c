#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <string.h>

int LLVMFuzzerTestOneInput_233(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid string
    if (size < 2) {
        return 0;
    }

    // Create a valid HDF5 file identifier
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Allocate memory for the attribute name and ensure it's null-terminated
    char attr_name[256];
    size_t name_length = size < 255 ? size : 255;
    memcpy(attr_name, data, name_length);
    attr_name[name_length] = '\0';

    // Call the function-under-test
    htri_t exists = H5Aexists(file_id, attr_name);

    // Close the HDF5 file
    H5Fclose(file_id);

    return 0;
}