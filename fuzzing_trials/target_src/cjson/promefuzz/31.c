// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateTrue at cJSON.c:2457:23 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateFalse at cJSON.c:2468:23 in cJSON.h
// cJSON_IsFalse at cJSON.c:2967:26 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateBool at cJSON.c:2479:23 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "cJSON.h"

int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test cJSON_CreateTrue and cJSON_IsTrue
    cJSON *trueItem = cJSON_CreateTrue();
    if (trueItem) {
        cJSON_bool isTrue = cJSON_IsTrue(trueItem);
        char *trueStr = cJSON_PrintUnformatted(trueItem);
        if (trueStr) {
            free(trueStr);
        }
        cJSON_Delete(trueItem);
    }

    // Test cJSON_CreateFalse and cJSON_IsFalse
    cJSON *falseItem = cJSON_CreateFalse();
    if (falseItem) {
        cJSON_bool isFalse = cJSON_IsFalse(falseItem);
        char *falseStr = cJSON_PrintUnformatted(falseItem);
        if (falseStr) {
            free(falseStr);
        }
        cJSON_Delete(falseItem);
    }

    // Test cJSON_CreateBool with dynamic input
    cJSON_bool boolValue = Data[0] % 2; // Use first byte to determine true or false
    cJSON *boolItem = cJSON_CreateBool(boolValue);
    if (boolItem) {
        char *boolStr = cJSON_PrintUnformatted(boolItem);
        if (boolStr) {
            free(boolStr);
        }
        cJSON_Delete(boolItem);
    }

    return 0;
}