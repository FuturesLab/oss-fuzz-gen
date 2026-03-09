// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_IsInvalid at cJSON.c:2957:26 in cJSON.h
// cJSON_IsNumber at cJSON.c:3007:26 in cJSON.h
// cJSON_IsString at cJSON.c:3017:26 in cJSON.h
// cJSON_IsObject at cJSON.c:3037:26 in cJSON.h
// cJSON_IsNull at cJSON.c:2997:26 in cJSON.h
// cJSON_IsFalse at cJSON.c:2967:26 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cJSON.h"

static void fuzz_cJSON_IsInvalid(const cJSON *item) {
    cJSON_IsInvalid(item);
}

static void fuzz_cJSON_IsNumber(const cJSON *item) {
    cJSON_IsNumber(item);
}

static void fuzz_cJSON_IsString(const cJSON *item) {
    cJSON_IsString(item);
}

static void fuzz_cJSON_IsObject(const cJSON *item) {
    cJSON_IsObject(item);
}

static void fuzz_cJSON_IsNull(const cJSON *item) {
    cJSON_IsNull(item);
}

static void fuzz_cJSON_IsFalse(const cJSON *item) {
    cJSON_IsFalse(item);
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cJSON)) {
        return 0;
    }

    cJSON *item = (cJSON *)malloc(sizeof(cJSON));
    if (item == NULL) {
        return 0;
    }

    // Initialize the cJSON item with data from the fuzzer
    item->type = Data[0];
    item->valuestring = (char *)Data;
    item->valueint = (int)Data[1];
    item->valuedouble = (double)Data[2];
    item->string = (char *)Data;

    // Fuzz the target functions
    fuzz_cJSON_IsInvalid(item);
    fuzz_cJSON_IsNumber(item);
    fuzz_cJSON_IsString(item);
    fuzz_cJSON_IsObject(item);
    fuzz_cJSON_IsNull(item);
    fuzz_cJSON_IsFalse(item);

    // Cleanup
    free(item);

    return 0;
}