// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateTrue at cJSON.c:2457:23 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
// cJSON_IsBool at cJSON.c:2988:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateBool at cJSON.c:2479:23 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
// cJSON_IsBool at cJSON.c:2988:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateBool at cJSON.c:2479:23 in cJSON.h
// cJSON_IsFalse at cJSON.c:2967:26 in cJSON.h
// cJSON_IsBool at cJSON.c:2988:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddBoolToObject at cJSON.c:2171:22 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
// cJSON_IsBool at cJSON.c:2988:26 in cJSON.h
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
#include "cJSON.h"

static void explore_cJSON_CreateTrue() {
    cJSON *trueItem = cJSON_CreateTrue();
    if (trueItem) {
        cJSON_bool isTrue = cJSON_IsTrue(trueItem);
        cJSON_bool isBool = cJSON_IsBool(trueItem);
        cJSON_Delete(trueItem);
    }
}

static void explore_cJSON_CreateBool() {
    cJSON *boolItemTrue = cJSON_CreateBool(1); // true
    if (boolItemTrue) {
        cJSON_bool isTrue = cJSON_IsTrue(boolItemTrue);
        cJSON_bool isBool = cJSON_IsBool(boolItemTrue);
        cJSON_Delete(boolItemTrue);
    }

    cJSON *boolItemFalse = cJSON_CreateBool(0); // false
    if (boolItemFalse) {
        cJSON_bool isFalse = cJSON_IsFalse(boolItemFalse);
        cJSON_bool isBool = cJSON_IsBool(boolItemFalse);
        cJSON_Delete(boolItemFalse);
    }
}

static void explore_cJSON_AddBoolToObject() {
    cJSON *object = cJSON_CreateObject();
    if (object) {
        cJSON *boolItem = cJSON_AddBoolToObject(object, "key", 1); // Add true
        if (boolItem) {
            cJSON_bool isTrue = cJSON_IsTrue(boolItem);
            cJSON_bool isBool = cJSON_IsBool(boolItem);
        }
        cJSON_Delete(object);
    }
}

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    // Fuzzing logic
    explore_cJSON_CreateTrue();
    explore_cJSON_CreateBool();
    explore_cJSON_AddBoolToObject();
    return 0;
}