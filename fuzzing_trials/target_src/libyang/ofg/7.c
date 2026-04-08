#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libyang.h"

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    if (size < sizeof(time_t) + 1) {
        return 0; // Not enough data to extract time_t and a format string
    }

    // Extract a time_t value from the data
    time_t time_value;
    memcpy(&time_value, data, sizeof(time_t));

    // Extract a format string from the remaining data
    const char *format = (const char *)(data + sizeof(time_t));

    // Ensure the format string is null-terminated
    char *null_terminated_format = (char *)malloc(size - sizeof(time_t) + 1);
    if (!null_terminated_format) {
        return 0;
    }
    memcpy(null_terminated_format, format, size - sizeof(time_t));
    null_terminated_format[size - sizeof(time_t)] = '\0';

    // Prepare the output string pointer
    char *output_str = NULL;

    // Call the function-under-test
    LY_ERR result = ly_time_time2str(time_value, null_terminated_format, &output_str);

    // Free allocated memory
    free(null_terminated_format);
    free(output_str);

    return 0;
}