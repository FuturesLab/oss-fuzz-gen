#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_190(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a new file using the default properties.
    hid_t file_id = H5Fcreate("temp.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Create a dataspace for the attribute.
    hsize_t dims[1] = {1};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);

    // Create an attribute.
    hid_t attr_id = H5Acreate2(file_id, "attr", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT);

    // Prepare a buffer to store the attribute name.
    size_t name_size = 256;
    char *name_buffer = (char *)malloc(name_size);
    if (name_buffer == NULL) {
        // Clean up and exit if memory allocation fails.
        H5Aclose(attr_id);
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        H5close();
        return 0;
    }

    // Ensure the buffer is not NULL and call the function-under-test.
    ssize_t name_len = H5Aget_name(attr_id, name_size, name_buffer);

    // Clean up
    free(name_buffer);
    H5Aclose(attr_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);
    H5close();

    return 0;
}