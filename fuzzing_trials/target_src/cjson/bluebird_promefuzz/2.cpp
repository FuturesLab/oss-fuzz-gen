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

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a root JSON object
    cJSON *root = cJSON_CreateObject();
    if (!root) {
        return 0;
    }

    // Create some sample cJSON items
    cJSON *item1 = cJSON_CreateNumber(1);

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of cJSON_CreateString
    cJSON *item2 = cJSON_CreateString(NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    cJSON *item3 = cJSON_CreateBool(cJSON_True);

    // Add items to the root object
    cJSON_AddItemToObject(root, "key1", item1);
    cJSON_AddItemToObject(root, "key2", item2);

    // Add items using constant strings

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cJSON_AddItemToObjectCS with cJSON_ReplaceItemInObjectCaseSensitive
    cJSON_ReplaceItemInObjectCaseSensitive(root, "constKey1", item3);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Create an array and add references
    cJSON *array = cJSON_CreateArray();
    cJSON_AddItemReferenceToArray(array, item1);
    cJSON_AddItemReferenceToArray(array, item2);

    // Add references to the root object
    cJSON_AddItemReferenceToObject(root, "refKey1", item1);
    cJSON_AddItemReferenceToObject(root, "refKey2", item2);

    // Delete items from array and object
    cJSON_DeleteItemFromArray(array, 0);
    cJSON_DeleteItemFromObject(root, "key1");
    cJSON_DeleteItemFromObjectCaseSensitive(root, "constKey1");

    // Prepare a writable copy of input data for minification
    char *jsonString = static_cast<char*>(malloc(Size + 1));
    if (jsonString) {
        memcpy(jsonString, Data, Size);
        jsonString[Size] = '\0';

        // Minify the JSON string
        cJSON_Minify(jsonString);

        free(jsonString);
    }

    // Cleanup
    cJSON_Delete(root);
    cJSON_Delete(array);

    return 0;
}