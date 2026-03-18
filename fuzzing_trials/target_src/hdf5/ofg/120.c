#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function-under-test
    hid_t dset_id = H5I_INVALID_HID; // Dataset identifier
    hid_t dxpl_id = H5P_DEFAULT;     // Data transfer property list identifier
    uint32_t filters = 0;            // Filter mask
    hsize_t offset[1] = {0};         // Offset array
    size_t data_size = size;         // Size of the data

    // Ensure data is not NULL and has a valid size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Call the function-under-test
    herr_t result = H5Dwrite_chunk(dset_id, dxpl_id, filters, offset, data_size, (const void *)data);

    // Return 0 to indicate success in the fuzzing harness
    return 0;
}