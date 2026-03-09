// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2533:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_SetValuestring at cJSON.c:430:21 in cJSON.h
// cJSON_GetObjectItem at cJSON.c:1968:23 in cJSON.h
// cJSON_GetObjectItem at cJSON.c:1968:23 in cJSON.h
// cJSON_SetValuestring at cJSON.c:430:21 in cJSON.h
// cJSON_GetObjectItem at cJSON.c:1968:23 in cJSON.h
// cJSON_GetObjectItem at cJSON.c:1968:23 in cJSON.h
// cJSON_SetValuestring at cJSON.c:430:21 in cJSON.h
// cJSON_GetObjectItem at cJSON.c:1968:23 in cJSON.h
// cJSON_GetObjectItem at cJSON.c:1968:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

static void write_to_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    // Ensure the data is null-terminated for string operations
    char *input = (char *)malloc(Size + 1);
    if (!input) {
        return 0;
    }
    memcpy(input, Data, Size);
    input[Size] = '\0';

    // Step 1: Parse JSON
    cJSON *root = cJSON_Parse(input);
    if (!root) {
        free(input);
        return 0;
    }

    // Step 2: Create a string
    cJSON *string_item = cJSON_CreateString("value");
    if (!string_item) {
        cJSON_Delete(root);
        free(input);
        return 0;
    }

    // Step 3: Create a string reference
    cJSON *string_ref = cJSON_CreateStringReference("reference");
    if (!string_ref) {
        cJSON_Delete(string_item);
        cJSON_Delete(root);
        free(input);
        return 0;
    }

    // Step 4: Add items to root object
    cJSON_AddItemToObject(root, "key1", string_item);
    cJSON_AddItemToObject(root, "key2", string_ref);

    // Step 5: Set value string
    cJSON_SetValuestring(string_item, "new_value");

    // Step 6: Get object items
    cJSON *item1 = cJSON_GetObjectItem(root, "key1");
    cJSON *item2 = cJSON_GetObjectItem(root, "key2");

    // Step 7: Set value string again
    cJSON_SetValuestring(item1, "another_value");

    // Step 8: Get object items again
    cJSON *item3 = cJSON_GetObjectItem(root, "key1");
    cJSON *item4 = cJSON_GetObjectItem(root, "key2");

    // Step 9: Set value string again
    cJSON_SetValuestring(item3, "final_value");

    // Step 10: Get object items again
    cJSON *item5 = cJSON_GetObjectItem(root, "key1");
    cJSON *item6 = cJSON_GetObjectItem(root, "key2");

    // Clean up
    cJSON_Delete(root);
    free(input);

    return 0;
}