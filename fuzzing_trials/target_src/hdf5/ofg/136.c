#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for our needs
    if (size < 10) return 0;

    // Initialize the parameters for the function
    const char *location = "location_name";
    const char *attr_name = "attribute_name";
    unsigned int lapl_id = 0; // Link Access Property List Identifier
    hid_t loc_id = 0; // Location Identifier
    const char *obj_name = "object_name";
    const char *attr_name2 = "attribute_name2";
    bool exists; // Changed _Bool to bool
    hid_t dxpl_id = 0; // Data Transfer Property List Identifier
    hid_t es_id = 0; // Event Stack Identifier

    // Call the function-under-test with the correct number of arguments
    herr_t result = H5Aexists_by_name_async(loc_id, obj_name, attr_name2, &exists, lapl_id, es_id);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}