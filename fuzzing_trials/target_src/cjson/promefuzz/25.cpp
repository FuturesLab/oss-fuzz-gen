// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_PrintPreallocated at cJSON.c:1343:26 in cJSON.h
// cJSON_ParseWithLength at cJSON.c:1227:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_ParseWithOpts at cJSON.c:1126:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_ParseWithLengthOpts at cJSON.c:1142:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

static void fuzz_cJSON_PrintPreallocated(cJSON *item) {
    if (!item) return;
    int buffer_length = 1024;
    char *buffer = (char *)malloc(buffer_length);
    if (!buffer) return;

    cJSON_bool format = 1; // try both formatted and unformatted
    cJSON_PrintPreallocated(item, buffer, buffer_length, format);
    free(buffer);
}

static void fuzz_cJSON_ParseWithLength(const char *data, size_t size) {
    cJSON *json = cJSON_ParseWithLength(data, size);
    if (json) {
        fuzz_cJSON_PrintPreallocated(json);
        cJSON_Delete(json);
    }
}

static void fuzz_cJSON_PrintUnformatted(cJSON *item) {
    if (!item) return;
    char *unformatted = cJSON_PrintUnformatted(item);
    if (unformatted) {
        free(unformatted);
    }
}

static void fuzz_cJSON_ParseWithOpts(const char *data, size_t size) {
    const char *end = NULL;
    cJSON *json = cJSON_ParseWithOpts(data, &end, 1);
    if (json) {
        fuzz_cJSON_PrintUnformatted(json);
        cJSON_Delete(json);
    }
}

static void fuzz_cJSON_ParseWithLengthOpts(const char *data, size_t size) {
    const char *end = NULL;
    cJSON *json = cJSON_ParseWithLengthOpts(data, size, &end, 1);
    if (json) {
        fuzz_cJSON_PrintUnformatted(json);
        cJSON_Delete(json);
    }
}

static void fuzz_cJSON_Parse(const char *data) {
    cJSON *json = cJSON_Parse(data);
    if (json) {
        fuzz_cJSON_PrintUnformatted(json);
        cJSON_Delete(json);
    }
}

int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Ensure null-termination for string inputs
    char *input = (char *)malloc(Size + 1);
    if (!input) return 0;
    memcpy(input, Data, Size);
    input[Size] = '\0';

    // Fuzz different functions
    fuzz_cJSON_ParseWithLength(input, Size);
    fuzz_cJSON_ParseWithOpts(input, Size);
    fuzz_cJSON_ParseWithLengthOpts(input, Size);
    fuzz_cJSON_Parse(input);

    free(input);
    return 0;
}