#include <stdint.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t from the input data
    hid_t file_id = *((hid_t*)data);

    // Attempt to reset the metadata cache hit rate stats for the file
    herr_t status = H5Freset_mdc_hit_rate_stats(file_id);

    // Check the status (though in a fuzzing context, this is mainly for completeness)
    if (status < 0) {
        // Handle error if needed, for now, just return
        return 0;
    }

    return 0;
}