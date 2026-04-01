#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    // Allocate memory for input data and ensure it is null-terminated
    char *input = (char *)malloc(size + 1);
    if (input == NULL) return 0;

    memcpy(input, data, size);
    input[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    cJSON_Minify(input);

    // Free the allocated memory
    free(input);

    return 0;
}

#ifdef __cplusplus
}
#endif