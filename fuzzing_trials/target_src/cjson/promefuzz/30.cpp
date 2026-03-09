// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_AddRawToObject at cJSON.c:2207:22 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_AddObjectToObject at cJSON.c:2219:22 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2183:22 in cJSON.h
// cJSON_AddNullToObject at cJSON.c:2135:22 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cJSON.h"

static void fuzz_cJSON_AddRawToObject(cJSON* object, const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    size_t name_len = Data[0] % (Size - 1) + 1;
    char *name = strndup((const char*)Data + 1, name_len);
    char *raw = strndup((const char*)Data + 1 + name_len, Size - 1 - name_len);
    cJSON *item = cJSON_AddRawToObject(object, name, raw);
    free(name);
    free(raw);
    // Do not delete the item here, as it is part of the object
}

static void fuzz_cJSON_AddStringToObject(cJSON* object, const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    size_t name_len = Data[0] % (Size - 1) + 1;
    char *name = strndup((const char*)Data + 1, name_len);
    char *string = strndup((const char*)Data + 1 + name_len, Size - 1 - name_len);
    cJSON *item = cJSON_AddStringToObject(object, name, string);
    free(name);
    free(string);
    // Do not delete the item here, as it is part of the object
}

static void fuzz_cJSON_AddObjectToObject(cJSON* object, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    char *name = strndup((const char*)Data, Size);
    cJSON *child = cJSON_AddObjectToObject(object, name);
    free(name);
    // Do not delete the child here, as it is part of the object
}

static void fuzz_cJSON_AddNumberToObject(cJSON* object, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) + 2) return;
    size_t name_len = Data[0] % (Size - sizeof(double) - 1) + 1;
    char *name = strndup((const char*)Data + 1, name_len);
    double number;
    memcpy(&number, Data + 1 + name_len, sizeof(double));
    cJSON *item = cJSON_AddNumberToObject(object, name, number);
    free(name);
    // Do not delete the item here, as it is part of the object
}

static void fuzz_cJSON_AddNullToObject(cJSON* object, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    char *name = strndup((const char*)Data, Size);
    cJSON *item = cJSON_AddNullToObject(object, name);
    free(name);
    // Do not delete the item here, as it is part of the object
}

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    cJSON *object = cJSON_CreateObject();
    if (!object) return 0;

    fuzz_cJSON_AddRawToObject(object, Data, Size);
    fuzz_cJSON_AddStringToObject(object, Data, Size);
    fuzz_cJSON_AddObjectToObject(object, Data, Size);
    fuzz_cJSON_AddNumberToObject(object, Data, Size);
    fuzz_cJSON_AddNullToObject(object, Data, Size);

    cJSON_Delete(object);
    return 0;
}