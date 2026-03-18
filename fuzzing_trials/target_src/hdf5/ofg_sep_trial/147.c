#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for our needs
    if (size < 6) {
        return 0;
    }

    // Initialize parameters for H5Dcreate_async
    const char *file_name = "fuzz_test_file.h5";
    const char *dataset_name = "fuzz_dataset";
    hid_t loc_id = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    hid_t type_id = H5T_NATIVE_INT;
    hid_t space_id = H5Screate(H5S_SCALAR);
    hid_t lcpl_id = H5P_DEFAULT;
    hid_t dcpl_id = H5P_DEFAULT;
    hid_t dapl_id = H5P_DEFAULT;
    hid_t es_id = H5EScreate();

    // Call the function-under-test
    hid_t dataset_id = H5Dcreate_async(loc_id, dataset_name, type_id, space_id, lcpl_id, dcpl_id, dapl_id, es_id);

    // Close the dataset and other resources if they were created successfully
    if (dataset_id >= 0) {
        H5Dclose(dataset_id);
    }
    H5Sclose(space_id);
    H5Fclose(loc_id);
    H5ESclose(es_id);

    return 0;
}