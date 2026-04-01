#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t from the input data
    hid_t file_id = *((hid_t *)data);

    // Initialize an unsigned int to store the intent
    unsigned int intent = 0;

    // Call the function-under-test
    herr_t result = H5Fget_intent(file_id, &intent);

    // Use the result and intent in some way to avoid compiler optimizations
    if (result >= 0) {
        // Normally, you might do something with the intent here
        // For fuzzing, just ensure the variables are used
        volatile unsigned int use_intent = intent;
        (void)use_intent;
    }

    return 0;
}