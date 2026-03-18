// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_CreateIntArray at cJSON.c:2606:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1926:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
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

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 3 + 2) {
        return 0;
    }

    // Prepare data for cJSON_CreateIntArray
    int numbers[3];
    memcpy(numbers, Data, sizeof(int) * 3);
    Data += sizeof(int) * 3;
    Size -= sizeof(int) * 3;

    // Prepare data for cJSON_CreateString
    char string1[Size / 2 + 1];
    char string2[Size / 2 + 1];
    memcpy(string1, Data, Size / 2);
    string1[Size / 2] = '\0';
    memcpy(string2, Data + Size / 2, Size / 2);
    string2[Size / 2] = '\0';

    // cJSON_CreateObject
    cJSON *object1 = cJSON_CreateObject();
    if (!object1) return 0;

    // cJSON_CreateIntArray
    cJSON *intArray = cJSON_CreateIntArray(numbers, 3);
    if (!intArray) {
        cJSON_Delete(object1);
        return 0;
    }

    // cJSON_GetArrayItem
    cJSON *arrayItem = cJSON_GetArrayItem(intArray, 1);

    // cJSON_AddItemToObject
    if (!cJSON_AddItemToObject(object1, "intArray", intArray)) {
        cJSON_Delete(object1);
        return 0;
    }

    // cJSON_CreateObject
    cJSON *object2 = cJSON_CreateObject();
    if (!object2) {
        cJSON_Delete(object1);
        return 0;
    }

    // cJSON_CreateString
    cJSON *stringItem1 = cJSON_CreateString(string1);
    if (!stringItem1) {
        cJSON_Delete(object1);
        cJSON_Delete(object2);
        return 0;
    }

    // cJSON_AddItemToObject
    if (!cJSON_AddItemToObject(object2, "string1", stringItem1)) {
        cJSON_Delete(object1);
        cJSON_Delete(object2);
        return 0;
    }

    // cJSON_CreateObject
    cJSON *object3 = cJSON_CreateObject();
    if (!object3) {
        cJSON_Delete(object1);
        cJSON_Delete(object2);
        return 0;
    }

    // cJSON_CreateString
    cJSON *stringItem2 = cJSON_CreateString(string2);
    if (!stringItem2) {
        cJSON_Delete(object1);
        cJSON_Delete(object2);
        cJSON_Delete(object3);
        return 0;
    }

    // cJSON_AddItemToObject
    if (!cJSON_AddItemToObject(object3, "string2", stringItem2)) {
        cJSON_Delete(object1);
        cJSON_Delete(object2);
        cJSON_Delete(object3);
        return 0;
    }

    // Cleanup
    cJSON_Delete(object1);
    cJSON_Delete(object2);
    cJSON_Delete(object3);

    return 0;
}