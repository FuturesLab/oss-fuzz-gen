#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    if (size < sizeof(time_t) + 1) {
        return 0;
    }

    time_t time_value;
    const char *format;
    char *result = NULL;

    // Extract time_t value from the input data
    time_value = *(const time_t *)data;

    // Ensure the format string is null-terminated
    format = (const char *)(data + sizeof(time_t));

    // Call the function-under-test
    LY_ERR err = ly_time_time2str(time_value, format, &result);

    // Free the result if it was allocated
    if (result != NULL) {
        free(result);
    }

    return 0;
}