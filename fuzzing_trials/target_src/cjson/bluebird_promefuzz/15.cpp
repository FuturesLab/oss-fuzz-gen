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

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == nullptr) return 0;

    // Add a string to the object
    const char *key1 = "key1";
    char *stringValue = new char[Size + 1];
    memcpy(stringValue, Data, Size);
    stringValue[Size] = '\0';
    cJSON *stringItem = cJSON_AddStringToObject(root, key1, stringValue);
    delete[] stringValue;
    if (stringItem == nullptr) {
        cJSON_Delete(root);
        return 0;
    }

    // Add an array to the object
    const char *arrayKey = "array";
    cJSON *array = cJSON_AddArrayToObject(root, arrayKey);
    if (array == nullptr) {
        cJSON_Delete(root);
        return 0;
    }

    // Create another JSON object
    cJSON *nestedObject = cJSON_CreateObject();
    if (nestedObject == nullptr) {
        cJSON_Delete(root);
        return 0;
    }

    // Add numbers to the nested object
    const char *numKey1 = "num1";
    const char *numKey2 = "num2";
    double num1 = static_cast<double>(Data[0]);
    double num2 = static_cast<double>(Size);
    if (cJSON_AddNumberToObject(nestedObject, numKey1, num1) == nullptr ||
        cJSON_AddNumberToObject(nestedObject, numKey2, num2) == nullptr) {
        cJSON_Delete(nestedObject);
        cJSON_Delete(root);
        return 0;
    }

    // Add the nested object to the array
    if (!cJSON_AddItemToArray(array, nestedObject)) {
        cJSON_Delete(nestedObject);
        cJSON_Delete(root);
        return 0;
    }

    // Print the JSON structure
    char *jsonString = cJSON_Print(root);
    if (jsonString != nullptr) {
        // Normally, you would do something with jsonString
        cJSON_free(jsonString);
    }

    // Cleanup
    cJSON_Delete(root);
    return 0;
}