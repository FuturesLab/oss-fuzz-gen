#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "../cJSON.h"
}

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    // Ensure data is null-terminated
    char *jsonStr = (char *)malloc(Size + 1);
    if (!jsonStr) {
        return 0;
    }
    memcpy(jsonStr, Data, Size);
    jsonStr[Size] = '\0';

    // Parse the JSON input
    cJSON *root = cJSON_Parse(jsonStr);
    if (!root) {
        free(jsonStr);
        return 0;
    }

    // Create a string item

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cJSON_CreateString with cJSON_CreateStringReference
    cJSON *stringItem = cJSON_CreateStringReference("example");
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (!stringItem) {
        cJSON_Delete(root);
        free(jsonStr);
        return 0;
    }

    // Create a string reference item
    cJSON *stringRefItem = cJSON_CreateStringReference("exampleRef");
    if (!stringRefItem) {
        cJSON_Delete(root);
        cJSON_Delete(stringItem);
        free(jsonStr);
        return 0;
    }

    // Add items to the root object
    cJSON_AddItemToObject(root, "stringItem", stringItem);
    cJSON_AddItemToObject(root, "stringRefItem", stringRefItem);

    // Modify the string value
    cJSON_SetValuestring(stringItem, "modifiedString");

    // Retrieve the items
    cJSON *retrievedItem1 = cJSON_GetObjectItem(root, "stringItem");
    cJSON *retrievedItem2 = cJSON_GetObjectItem(root, "stringRefItem");

    // Modify the string value again
    if (retrievedItem1) {
        cJSON_SetValuestring(retrievedItem1, "secondModification");
    }

    // Retrieve the items again
    cJSON *retrievedItem3 = cJSON_GetObjectItem(root, "stringItem");
    cJSON *retrievedItem4 = cJSON_GetObjectItem(root, "stringRefItem");

    // Modify the string value one more time
    if (retrievedItem3) {
        cJSON_SetValuestring(retrievedItem3, "thirdModification");
    }

    // Retrieve the items one last time
    cJSON *retrievedItem5 = cJSON_GetObjectItem(root, "stringItem");
    cJSON *retrievedItem6 = cJSON_GetObjectItem(root, "stringRefItem");

    // Clean up
    cJSON_Delete(root);
    free(jsonStr);

    return 0;
}