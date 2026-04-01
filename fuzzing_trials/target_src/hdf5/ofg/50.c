#include <stdint.h>
#include <stdbool.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Declare and initialize parameters for H5Aexists_async
    const char *attr_name = "attr_name_example";
    hid_t obj_id = H5I_INVALID_HID; // Use an invalid object ID for fuzzing
    hid_t es_id = H5EScreate(); // Create an event set identifier
    bool status = false;
    hid_t dxpl_id = H5P_DEFAULT; // Default data transfer property list

    // Ensure the event set identifier is valid
    if (es_id < 0) {
        return 0; // Exit if unable to create a valid event set identifier
    }

    // Call the function-under-test
    herr_t result = H5Aexists_async(obj_id, attr_name, &status, es_id);

    // Close the event set identifier
    H5ESclose(es_id);

    return 0;
}