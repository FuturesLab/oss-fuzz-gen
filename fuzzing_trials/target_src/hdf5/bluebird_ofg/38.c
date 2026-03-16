#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    hid_t file_id, space_id, attr_id;
    hsize_t dims[1] = {1};
    int dummy_data[1] = {0};
    size_t buf_size;
    char *name_buf;

    // Ensure the size is sufficient for our needs
    if (size < sizeof(size_t)) {
        return 0;
    }

    // Initialize buf_size from data
    buf_size = *((size_t *)data);

    // Validate buf_size to prevent excessive memory allocation
    if (buf_size > size - sizeof(size_t) || buf_size > 1024) {
        return 0;
    }

    // Allocate memory for the name buffer
    name_buf = (char *)malloc(buf_size + 1);
    if (name_buf == NULL) {
        return 0;
    }

    // Ensure the name buffer is null-terminated
    name_buf[buf_size] = '\0';

    // Initialize HDF5 library
    H5open();

    // Create a temporary file and dataset to attach an attribute
    file_id = H5Fcreate("temp.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    space_id = H5Screate_simple(1, dims, NULL);
    hid_t dataset_id = H5Dcreate(file_id, "dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Create an attribute
    attr_id = H5Acreate(dataset_id, "attribute", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT);

    // Call the function-under-test
    ssize_t result = H5Aget_name(attr_id, buf_size, name_buf);

    // Clean up
    free(name_buf);
    H5Aclose(attr_id);
    H5Dclose(dataset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);
    H5close();

    return 0;
}