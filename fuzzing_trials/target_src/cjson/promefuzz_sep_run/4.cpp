// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_GetErrorPtr at cJSON.c:94:28 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1973:23 in cJSON.h
// cJSON_IsString at cJSON.c:3017:26 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1973:23 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1973:23 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1973:23 in cJSON.h
// cJSON_IsNumber at cJSON.c:3007:26 in cJSON.h
// cJSON_IsNumber at cJSON.c:3007:26 in cJSON.h
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

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    // Ensure null-termination for the input data
    char *jsonString = (char *)malloc(Size + 1);
    if (!jsonString) {
        return 0; // Out of memory, exit gracefully
    }
    memcpy(jsonString, Data, Size);
    jsonString[Size] = '\0';

    // Step 1: Parse the JSON string
    cJSON *root = cJSON_Parse(jsonString);
    if (!root) {
        const char *errorPtr = cJSON_GetErrorPtr();
        (void)errorPtr; // Use errorPtr if needed for debugging
        free(jsonString);
        return 0; // Parsing failed, exit gracefully
    }

    // Step 2: Get an item from the JSON object
    cJSON *item = cJSON_GetObjectItemCaseSensitive(root, "key");
    if (item && cJSON_IsString(item)) {
        // Process the string item if needed
    }

    // Step 3: Retrieve multiple items and check their types
    cJSON *numberItem1 = cJSON_GetObjectItemCaseSensitive(root, "number1");
    cJSON *numberItem2 = cJSON_GetObjectItemCaseSensitive(root, "number2");
    cJSON *numberItem3 = cJSON_GetObjectItemCaseSensitive(root, "number3");

    if (numberItem1 && cJSON_IsNumber(numberItem1)) {
        // Process numberItem1 if needed
    }

    if (numberItem2 && cJSON_IsNumber(numberItem2)) {
        // Process numberItem2 if needed
    }

    // Step 4: Clean up
    cJSON_Delete(root);
    free(jsonString);

    return 0;
}