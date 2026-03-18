// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_ParseWithLength at cJSON.c:1227:23 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1973:23 in cJSON.h
// cJSON_IsString at cJSON.c:3017:26 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1973:23 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1973:23 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1973:23 in cJSON.h
// cJSON_Duplicate at cJSON.c:2769:23 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1973:23 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1973:23 in cJSON.h
// cJSON_Compare at cJSON.c:3057:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
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

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Write the input data to a dummy file
    write_dummy_file(Data, Size);

    // Create a cJSON object from the input data
    cJSON *root = cJSON_ParseWithLength((const char *)Data, Size);
    if (!root) {
        return 0;
    }

    // Invoke cJSON_GetObjectItemCaseSensitive
    cJSON *item1 = cJSON_GetObjectItemCaseSensitive(root, "key1");
    cJSON_IsString(item1);

    // Invoke cJSON_GetObjectItemCaseSensitive again
    cJSON *item2 = cJSON_GetObjectItemCaseSensitive(root, "key2");
    cJSON_IsTrue(item2);

    // Invoke cJSON_GetObjectItemCaseSensitive again
    cJSON *item3 = cJSON_GetObjectItemCaseSensitive(root, "key3");

    // Invoke cJSON_GetObjectItemCaseSensitive again
    cJSON *item4 = cJSON_GetObjectItemCaseSensitive(root, "key4");

    // Duplicate the JSON object
    cJSON *duplicate = cJSON_Duplicate(root, 1);

    // Invoke cJSON_GetObjectItemCaseSensitive again
    cJSON *item5 = cJSON_GetObjectItemCaseSensitive(root, "key5");

    // Invoke cJSON_GetObjectItemCaseSensitive again
    cJSON *item6 = cJSON_GetObjectItemCaseSensitive(root, "key6");

    // Compare the original and duplicated JSON objects
    cJSON_Compare(root, duplicate, 1);

    // Clean up
    cJSON_Delete(root);
    cJSON_Delete(duplicate);

    return 0;
}