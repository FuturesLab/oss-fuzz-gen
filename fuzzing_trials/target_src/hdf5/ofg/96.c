#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for our needs
    if (size < 10) return 0;

    // Initialize variables for the function call
    hid_t dxpl_id = H5P_DEFAULT;
    hid_t dset_id = H5I_INVALID_HID;
    hid_t mem_type_id = H5T_NATIVE_INT;
    hid_t mem_space_id = H5S_ALL;
    hid_t file_space_id = H5S_ALL;
    hid_t es_id = H5I_INVALID_HID;

    // Use the provided data as the buffer for the write operation
    const void *buf = (const void *)data;

    // Call the function-under-test
    herr_t result = H5Dwrite_async(
        dset_id,
        mem_type_id,
        mem_space_id,
        file_space_id,
        dxpl_id,
        buf,
        es_id
    );

    // Return 0 for success
    return 0;
}