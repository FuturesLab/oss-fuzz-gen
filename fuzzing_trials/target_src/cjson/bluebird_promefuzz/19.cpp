#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include "../cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a parent cJSON object
    cJSON *parent = cJSON_CreateObject();
    if (!parent) return 0;

    // Create a cJSON item to reference
    cJSON *item = cJSON_CreateString("example");
    if (!item) {
        cJSON_Delete(parent);
        return 0;
    }

    // Create a key for cJSON_AddItemReferenceToObject
    char key[256];
    if (Size < sizeof(key)) {
        memcpy(key, Data, Size);
        key[Size] = '\0';
    } else {
        memcpy(key, Data, sizeof(key) - 1);
        key[sizeof(key) - 1] = '\0';
    }

    // Fuzz cJSON_AddItemReferenceToObject
    cJSON_bool result = cJSON_AddItemReferenceToObject(parent, key, item);
    
    // Fuzz cJSON_AddObjectToObject
    cJSON *child = cJSON_AddObjectToObject(parent, key);

    // Fuzz cJSON_IsString
    cJSON_bool isString = cJSON_IsString(item);

    // Fuzz cJSON_IsArray
    cJSON_bool isArray = cJSON_IsArray(item);

    // Fuzz cJSON_IsNull
    cJSON_bool isNull = cJSON_IsNull(item);

    // Fuzz cJSON_IsNumber
    cJSON_bool isNumber = cJSON_IsNumber(item);

    // Cleanup
    cJSON_Delete(parent);
    cJSON_Delete(item);

    return 0;
}