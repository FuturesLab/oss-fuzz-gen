#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Use the first byte of data to determine the size for cJSON_malloc
    size_t malloc_size = (size_t)data[0];

    // Call cJSON_malloc with the determined size
    void *allocated_memory = cJSON_malloc(malloc_size);

    // If memory was allocated, free it
    if (allocated_memory != NULL) {
        free(allocated_memory);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif