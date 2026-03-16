#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for creating non-empty strings
    if (size < 16) {
        return 0;
    }

    // Create strings from the input data
    char name1[4];
    char name2[4];
    char name3[4];
    
    // Copy data into the strings, ensuring null-termination
    for (int i = 0; i < 3; ++i) {
        name1[i] = data[i];
        name2[i] = data[i + 3];
        name3[i] = data[i + 6];
    }
    name1[3] = '\0';
    name2[3] = '\0';
    name3[3] = '\0';

    // Initialize other parameters
    unsigned int flags = (unsigned int)data[9];
    hid_t loc_id = (hid_t)data[10];
    hid_t lcpl_id = (hid_t)data[11];
    hid_t dcpl_id = (hid_t)data[12];
    hid_t dapl_id = (hid_t)data[13];
    hid_t dxpl_id = (hid_t)data[14];
    hid_t es_id = (hid_t)data[15];

    // Call the function-under-test
    hid_t result = H5Dcreate_async(loc_id, name1, flags, lcpl_id, dcpl_id, dapl_id, dxpl_id, es_id);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result > 0) {
        H5Dclose(result);
    }

    return 0;
}