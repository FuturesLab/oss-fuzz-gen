#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    // Check if the input data size is sufficient to proceed
    if (size < sizeof(int)) {
        return 0;
    }

    // Define and initialize parameters for H5Dcreate_async
    const char *file_name = "test_file.h5";
    const char *dataset_name = "test_dataset";
    unsigned int flags = 0;
    hid_t loc_id = H5P_DEFAULT;
    const char *app_file = "app_file";
    hid_t type_id = H5T_NATIVE_INT;
    hid_t space_id = H5S_SCALAR;
    hid_t lcpl_id = H5P_DEFAULT;
    hid_t dcpl_id = H5P_DEFAULT;
    hid_t dapl_id = H5P_DEFAULT;
    hid_t es_id = H5ES_NONE;

    // Call the function-under-test
    hid_t dataset_id = H5Dcreate_async(file_name, dataset_name, type_id, space_id, lcpl_id, dcpl_id, dapl_id, es_id);

    // Close the dataset if it was successfully created
    if (dataset_id >= 0) {
        H5Dclose(dataset_id);
    }

    return 0;
}