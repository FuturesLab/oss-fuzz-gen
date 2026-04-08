#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    struct timespec ts;
    char *str = NULL;
    LY_ERR err;

    // Ensure the data size is sufficient for initializing the timespec structure
    if (size < sizeof(struct timespec)) {
        return 0;
    }

    // Copy data into the timespec structure
    memcpy(&ts, data, sizeof(struct timespec));

    // Call the function-under-test
    err = ly_time_ts2str(&ts, &str);

    // Free the allocated string if it was successfully created
    if (err == LY_SUCCESS && str != NULL) {
        free(str);
    }

    return 0;
}