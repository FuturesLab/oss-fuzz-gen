#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Declare variables
    hid_t file_id;
    char *attr_name;

    // Initialize the HDF5 library
    H5open();

    // Create a temporary file to work with
    file_id = H5Fcreate("temp.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Allocate memory for the attribute name and ensure it's null-terminated
    attr_name = (char *)malloc(size + 1);
    if (attr_name == NULL) {
        H5Fclose(file_id);
        return 0;
    }
    memcpy(attr_name, data, size);
    attr_name[size] = '\0';

    // Call the function-under-test
    htri_t exists = H5Aexists(file_id, attr_name);

    // Clean up
    free(attr_name);
    H5Fclose(file_id);

    // Close the HDF5 library
    H5close();

    return 0;
}