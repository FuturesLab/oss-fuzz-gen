#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_277(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to extract parameters
    if (size < 3) return 0;

    // Extract parameters from the input data
    const char *file_name = (const char *)data;
    const char *dataset_name = (const char *)(data + 1);
    unsigned int flags = (unsigned int)data[2];

    // Use some valid default values for the hid_t parameters
    hid_t dapl_id = H5P_DEFAULT;
    hid_t dxpl_id = H5P_DEFAULT;
    hid_t es_id = H5ES_NONE;

    // Call the function-under-test with the correct number of arguments
    hid_t dataset_id = H5Dopen_async(file_name, dataset_name, dapl_id, es_id);

    // If a valid dataset_id is returned, close it
    if (dataset_id >= 0) {
        H5Dclose(dataset_id);
    }

    return 0;
}