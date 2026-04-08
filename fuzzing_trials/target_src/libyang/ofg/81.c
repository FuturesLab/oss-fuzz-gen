#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    // Declare and initialize the timespec structure
    struct timespec ts;
    char *result_str = NULL;

    // Ensure that the size is sufficient to fill the timespec structure
    if (size < sizeof(struct timespec)) {
        return 0;
    }

    // Copy data into the timespec structure
    memcpy(&ts, data, sizeof(struct timespec));

    // Call the function-under-test
    LY_ERR err = ly_time_ts2str(&ts, &result_str);

    // Free the allocated string if it was successfully created
    if (err == LY_SUCCESS && result_str != NULL) {
        free(result_str);
    }

    return 0;
}