// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2435:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Print at cJSON.c:1302:22 in cJSON.h
// cJSON_GetArraySize at cJSON.c:1884:19 in cJSON.h
// cJSON_DeleteItemFromArray at cJSON.c:2289:20 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2313:20 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2308:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cJSON.h"

static void fuzz_cJSON_ReplaceItemInObject(cJSON *object, const uint8_t *Data, size_t Size) {
    if (Size < 2) return;

    // Split data into key and new item
    size_t key_length = Data[0] % (Size - 1) + 1;
    if (key_length >= Size) return;
    char *key = (char *)malloc(key_length + 1);
    if (!key) return;
    memcpy(key, Data + 1, key_length);
    key[key_length] = '\0';

    cJSON *new_item = cJSON_CreateString("new_value");
    if (!new_item) {
        free(key);
        return;
    }

    if (!cJSON_ReplaceItemInObject(object, key, new_item)) {
        cJSON_Delete(new_item); // Clean up if replacement fails
    }

    free(key);
}

static void fuzz_cJSON_Print(cJSON *item) {
    char *printed = cJSON_Print(item);
    if (printed) {
        free(printed);
    }
}

static void fuzz_cJSON_DeleteItemFromArray(cJSON *array, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    int array_size = cJSON_GetArraySize(array);
    if (array_size > 0) {
        int index = Data[0] % array_size;
        cJSON_DeleteItemFromArray(array, index);
    }
}

static void fuzz_cJSON_PrintUnformatted(cJSON *item) {
    char *printed = cJSON_PrintUnformatted(item);
    if (printed) {
        free(printed);
    }
}

static void fuzz_cJSON_DeleteItemFromObjectCaseSensitive(cJSON *object, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    size_t key_length = Data[0] % Size;
    if (key_length >= Size) return;
    char *key = (char *)malloc(key_length + 1);
    if (!key) return;
    memcpy(key, Data + 1, key_length);
    key[key_length] = '\0';

    cJSON_DeleteItemFromObjectCaseSensitive(object, key);

    free(key);
}

static void fuzz_cJSON_DeleteItemFromObject(cJSON *object, const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    size_t key_length = Data[0] % Size;
    if (key_length >= Size) return;
    char *key = (char *)malloc(key_length + 1);
    if (!key) return;
    memcpy(key, Data + 1, key_length);
    key[key_length] = '\0';

    cJSON_DeleteItemFromObject(object, key);

    free(key);
}

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size == 0 || !Data) return 0;

    char *input_data = (char *)malloc(Size + 1);
    if (!input_data) return 0;
    memcpy(input_data, Data, Size);
    input_data[Size] = '\0';

    cJSON *json = cJSON_Parse(input_data);
    free(input_data);

    if (!json) return 0;

    fuzz_cJSON_ReplaceItemInObject(json, Data, Size);
    fuzz_cJSON_Print(json);
    fuzz_cJSON_DeleteItemFromArray(json, Data, Size);
    fuzz_cJSON_PrintUnformatted(json);
    fuzz_cJSON_DeleteItemFromObjectCaseSensitive(json, Data, Size);
    fuzz_cJSON_DeleteItemFromObject(json, Data, Size);

    cJSON_Delete(json);
    return 0;
}