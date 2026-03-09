#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this header for memcpy
#include "/src/cjson/cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    cJSON_Hooks hooks;
    void *(*malloc_fn)(size_t) = malloc;
    void (*free_fn)(void *) = free;

    // Initialize hooks with default malloc and free functions
    hooks.malloc_fn = malloc_fn;
    hooks.free_fn = free_fn;

    // Call the function-under-test
    cJSON_InitHooks(&hooks);

    // Feed the input data to a cJSON function to maximize fuzzing
    if (size > 0) {
        char *input = (char *)malloc(size + 1);
        if (input) {
            memcpy(input, data, size);
            input[size] = '\0'; // Null-terminate the input
            cJSON *json = cJSON_Parse(input);
            if (json) {
                cJSON_Delete(json);
            }
            free(input);
        }
    }

    return 0;
}

#ifdef __cplusplus
}
#endif