#include <stdint.h>
#include <stdlib.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for extracting test parameters
    if (size < 5) return 0; // Adjusted to ensure enough data for es_id

    // Extracting parameters from the data
    const char *loc_name = "location_name";
    const char *attr_name = "attribute_name";
    unsigned int idx_type = (unsigned int)data[0];
    hid_t loc_id = (hid_t)data[1];
    const char *old_name = "old_name";
    const char *new_name = "new_name";
    hid_t lapl_id = (hid_t)data[2];
    hid_t dxpl_id = (hid_t)data[3];
    hid_t es_id = (hid_t)data[4];

    // Call the function under test with the correct number of arguments
    herr_t result = H5Arename_by_name_async(loc_id, loc_name, old_name, new_name, lapl_id, es_id);

    // Return 0 to indicate the fuzzer can continue
    return 0;
}