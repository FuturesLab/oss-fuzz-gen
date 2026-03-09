#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include "../cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    // Convert the input data to a string
    char *inputStr = (char *)malloc(Size + 1);
    if (!inputStr) return 0; // Exit if memory allocation fails
    memcpy(inputStr, Data, Size);
    inputStr[Size] = '\0';

    // Test cJSON_Parse
    cJSON *parsedJson = cJSON_Parse(inputStr);
    if (parsedJson) {
        // Test cJSON_PrintUnformatted
        char *unformattedStr = cJSON_PrintUnformatted(parsedJson);
        if (unformattedStr) {
            free(unformattedStr);
        }

        // Test cJSON_GetStringValue
        cJSON_GetStringValue(parsedJson);

        cJSON_Delete(parsedJson);
    }

    // Test cJSON_CreateRaw
    cJSON *rawJson = cJSON_CreateRaw(inputStr);
    if (rawJson) {
        cJSON_Delete(rawJson);
    }

    // Test cJSON_CreateStringReference
    cJSON *stringRef = cJSON_CreateStringReference(inputStr);
    if (stringRef) {
        cJSON_Delete(stringRef);
    }

    // Create a dummy cJSON object
    cJSON *dummyObject = cJSON_CreateObject();
    if (dummyObject) {
        // Test cJSON_AddStringToObject
        cJSON *addedString = cJSON_AddStringToObject(dummyObject, "key", inputStr);
        if (addedString) {
            // Successfully added, no action needed
        }
        cJSON_Delete(dummyObject);
    }

    free(inputStr);
    return 0;
}