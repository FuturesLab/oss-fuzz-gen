// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateFalse at cJSON.c:2468:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2533:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObjectReference at cJSON.c:2545:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    // Ensure there is enough data to work with
    if (Size < 1) {
        return 0;
    }

    // Create a cJSON false object
    cJSON *falseObj = cJSON_CreateFalse();
    if (falseObj == NULL) {
        return 0;
    }

    // Create a cJSON string object
    char *stringData = (char *)malloc(Size + 1);
    if (stringData == NULL) {
        cJSON_Delete(falseObj);
        return 0;
    }
    memcpy(stringData, Data, Size);
    stringData[Size] = '\0';

    cJSON *stringObj = cJSON_CreateString(stringData);
    if (stringObj == NULL) {
        free(stringData);
        cJSON_Delete(falseObj);
        return 0;
    }

    // Create a cJSON object
    cJSON *objectObj = cJSON_CreateObject();
    if (objectObj == NULL) {
        free(stringData);
        cJSON_Delete(stringObj);
        cJSON_Delete(falseObj);
        return 0;
    }

    // Create a cJSON string reference
    cJSON *stringRefObj = cJSON_CreateStringReference(stringData);
    if (stringRefObj == NULL) {
        free(stringData);
        cJSON_Delete(objectObj);
        cJSON_Delete(stringObj);
        cJSON_Delete(falseObj);
        return 0;
    }

    // Cleanup
    cJSON_Delete(falseObj);
    cJSON_Delete(stringObj);
    cJSON_Delete(stringRefObj);

    // Create an object reference
    cJSON *objectRefObj = cJSON_CreateObjectReference(objectObj);
    if (objectRefObj == NULL) {
        free(stringData);
        cJSON_Delete(objectObj);
        return 0;
    }

    // Cleanup
    cJSON_Delete(objectRefObj);
    cJSON_Delete(objectObj);

    // Free allocated string data
    free(stringData);

    return 0;
}