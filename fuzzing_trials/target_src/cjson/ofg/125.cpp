#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read at least one double and an integer
    if (size < sizeof(double) + sizeof(int)) {
        return 0;
    }

    // Calculate the number of doubles we can read from the data
    int num_doubles = (size - sizeof(int)) / sizeof(double);

    // Extract the integer value from the data
    int count = *((int *)(data + num_doubles * sizeof(double)));

    // Ensure count is not negative and does not exceed num_doubles
    if (count < 0 || count > num_doubles) {
        return 0;
    }

    // Create an array of doubles from the data
    const double *double_array = (const double *)data;

    // Call the function under test
    cJSON *json_array = cJSON_CreateDoubleArray(double_array, count);

    // Clean up
    if (json_array != NULL) {
        cJSON_Delete(json_array);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif