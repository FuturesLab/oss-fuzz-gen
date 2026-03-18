// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2435:26 in cJSON.h
// cJSON_AddItemReferenceToObject at cJSON.c:2125:26 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2183:22 in cJSON.h
// cJSON_CreateNull at cJSON.c:2446:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_AddArrayToObject at cJSON.c:2231:22 in cJSON.h
// cJSON_CreateTrue at cJSON.c:2457:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_AddItemToObjectCS at cJSON.c:2110:26 in cJSON.h
// cJSON_CreateFalse at cJSON.c:2468:23 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "cJSON.h"

static void initialize_json_objects(cJSON **object, cJSON **new_item, cJSON **reference_item) {
    *object = cJSON_CreateObject();
    *new_item = cJSON_CreateNumber(42);
    *reference_item = cJSON_CreateString("reference");
}

static void cleanup_json_objects(cJSON *object, cJSON *new_item, cJSON *reference_item) {
    cJSON_Delete(object);
    cJSON_Delete(new_item);
    cJSON_Delete(reference_item);
}

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    cJSON *object = NULL;
    cJSON *new_item = NULL;
    cJSON *reference_item = NULL;
    initialize_json_objects(&object, &new_item, &reference_item);

    char key[256];
    snprintf(key, sizeof(key), "%.*s", (int)(Size % 255), Data);

    // Fuzz cJSON_ReplaceItemInObject
    cJSON_ReplaceItemInObject(object, key, new_item);

    // Fuzz cJSON_AddItemReferenceToObject
    cJSON_AddItemReferenceToObject(object, key, reference_item);

    // Fuzz cJSON_AddNumberToObject
    cJSON_AddNumberToObject(object, key, 123.456);

    // Fuzz cJSON_AddItemToObject
    cJSON_AddItemToObject(object, key, cJSON_CreateNull());

    // Fuzz cJSON_AddArrayToObject
    cJSON *array = cJSON_AddArrayToObject(object, key);
    if (array) {
        cJSON_AddItemToArray(array, cJSON_CreateTrue());
    }

    // Fuzz cJSON_AddItemToObjectCS
    cJSON_AddItemToObjectCS(object, "constant_key", cJSON_CreateFalse());

    cleanup_json_objects(object, new_item, reference_item);
    return 0;
}