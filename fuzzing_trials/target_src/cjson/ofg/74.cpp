#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    if (size < sizeof(size_t)) {
        return 0;
    }

    // Extract a size_t value from the input data
    size_t alloc_size;
    memcpy(&alloc_size, data, sizeof(size_t));

    // Call the function-under-test
    void *allocated_memory = cJSON_malloc(alloc_size);

    // If memory was successfully allocated, free it
    if (allocated_memory != NULL) {
        free(allocated_memory);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif