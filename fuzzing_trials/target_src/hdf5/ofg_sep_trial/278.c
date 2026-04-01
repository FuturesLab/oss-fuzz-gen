#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_278(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for our needs
    if (size < 4) return 0;

    // Initialize parameters for H5Dopen_async
    const char *file_name = "testfile.h5";
    const char *dataset_name = "testdataset";
    hid_t loc_id = (hid_t)data[0]; // Use the first byte for loc_id
    hid_t dapl_id = (hid_t)data[1]; // Use the second byte for dapl_id
    hid_t es_id = (hid_t)data[2]; // Use the third byte for es_id

    // Call the function-under-test with the correct number of arguments
    hid_t dataset_id = H5Dopen_async(loc_id, dataset_name, dapl_id, es_id);

    // Close the dataset if it was successfully opened
    if (dataset_id >= 0) {
        H5Dclose(dataset_id);
    }

    return 0;
}