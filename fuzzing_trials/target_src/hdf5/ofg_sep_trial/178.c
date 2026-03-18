#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a file and an attribute
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    hid_t dataspace_id = H5Screate(H5S_SCALAR);
    hid_t attribute_id = H5Acreate2(file_id, "fuzz_attribute", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT);

    // Ensure data is not NULL and has enough size
    if (size < sizeof(int)) {
        // Clean up and return if data is insufficient
        H5Aclose(attribute_id);
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        H5close();
        return 0;
    }

    // Write data to the attribute
    herr_t status = H5Awrite(attribute_id, H5T_NATIVE_INT, (const void *)data);

    // Clean up resources
    H5Aclose(attribute_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}