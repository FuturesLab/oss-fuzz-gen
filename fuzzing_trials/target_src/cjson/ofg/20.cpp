#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    if (size < sizeof(size_t) * 2) {
        return 0;
    }

    cJSON_Hooks hooks;
    size_t malloc_offset = *((size_t *)data) % (size - sizeof(size_t));
    size_t free_offset = *((size_t *)(data + sizeof(size_t))) % (size - sizeof(size_t));

    hooks.malloc_fn = (void *(*)(size_t))(data + malloc_offset);
    hooks.free_fn = (void (*)(void *))(data + free_offset);

    cJSON_InitHooks(&hooks);

    return 0;
}

#ifdef __cplusplus
}
#endif