#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_281(const uint8_t *data, size_t size) {
    // Define and initialize variables for the function parameters
    const char *file_name = "test_file.h5";
    const char *dataset_name = "test_dataset";
    hid_t loc_id = H5P_DEFAULT; // Assuming default location ID
    hid_t dapl_id = H5P_DEFAULT; // Default dataset access property list
    hid_t es_id = H5ES_NONE; // Event set identifier

    // Call the function-under-test
    hid_t dataset_id = H5Dopen_async(file_name, dataset_name, dapl_id, es_id);

    // Close the dataset if it was successfully opened
    if (dataset_id >= 0) {
        H5Dclose(dataset_id);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif