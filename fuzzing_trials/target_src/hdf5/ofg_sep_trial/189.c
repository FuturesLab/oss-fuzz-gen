#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_189(const uint8_t *data, size_t size) {
    // Create a new HDF5 file
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a dataspace for the attribute
    hid_t dataspace_id = H5Screate(H5S_SCALAR);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create an attribute attached to the file
    hid_t attribute_id = H5Acreate2(file_id, "attribute", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attribute_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Define a buffer size for the attribute name
    size_t buf_size = 256;
    char name_buffer[256];

    // Get the name of the attribute
    ssize_t name_length = H5Aget_name(attribute_id, buf_size, name_buffer);

    // Clean up
    H5Aclose(attribute_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    return 0;
}