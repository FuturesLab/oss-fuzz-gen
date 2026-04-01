#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <string.h>

int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a valid string
    if (size < 1) {
        return 0;
    }

    // Create a dummy HDF5 file and dataset to work with
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    hid_t dataspace_id = H5Screate(H5S_SCALAR);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, dataspace_id,
                                  H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Create an attribute with a known name
    hid_t attr_id = H5Acreate2(dataset_id, "known_attr", H5T_NATIVE_INT, dataspace_id,
                               H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }

    // Create a null-terminated string from the input data
    char attr_name[256];
    size_t copy_size = size < 255 ? size : 255;
    memcpy(attr_name, data, copy_size);
    attr_name[copy_size] = '\0';

    // Call the function-under-test
    H5Adelete(dataset_id, attr_name);

    // Clean up
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    return 0;
}