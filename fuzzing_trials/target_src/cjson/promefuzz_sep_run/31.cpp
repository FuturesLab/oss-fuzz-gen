// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2183:22 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_AddNullToObject at cJSON.c:2135:22 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_AddBoolToObject at cJSON.c:2171:22 in cJSON.h
// cJSON_IsNumber at cJSON.c:3007:26 in cJSON.h
// cJSON_IsString at cJSON.c:3017:26 in cJSON.h
// cJSON_IsArray at cJSON.c:3027:26 in cJSON.h
// cJSON_IsNull at cJSON.c:2997:26 in cJSON.h
// cJSON_IsObject at cJSON.c:3037:26 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_AddItemReferenceToObject at cJSON.c:2125:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_IsObject at cJSON.c:3037:26 in cJSON.h
// cJSON_AddObjectToObject at cJSON.c:2219:22 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

static cJSON* create_random_cJSON(const uint8_t *Data, size_t Size) {
    if (Size == 0) return NULL;

    cJSON *item = cJSON_CreateObject();
    if (item == NULL) return NULL;

    size_t index = 0;
    while (index < Size) {
        int type = Data[index] % 6; // Choose a type based on the data
        index++;
        switch (type) {
            case 0: // Number
                if (index + sizeof(double) <= Size) {
                    double number;
                    memcpy(&number, &Data[index], sizeof(double));
                    cJSON_AddNumberToObject(item, "number", number);
                    index += sizeof(double);
                }
                break;
            case 1: // String
                if (index < Size) {
                    size_t str_len = Data[index] % (Size - index);
                    index++;
                    if (index + str_len <= Size) {
                        char *str = (char *)malloc(str_len + 1);
                        if (str != NULL) {
                            memcpy(str, &Data[index], str_len);
                            str[str_len] = '\0';
                            cJSON_AddStringToObject(item, "string", str);
                            free(str);
                            index += str_len;
                        }
                    }
                }
                break;
            case 2: // Array
                {
                    cJSON *array = cJSON_CreateArray();
                    cJSON_AddItemToObject(item, "array", array);
                }
                break;
            case 3: // Null
                cJSON_AddNullToObject(item, "null");
                break;
            case 4: // Object
                {
                    cJSON *object = cJSON_CreateObject();
                    cJSON_AddItemToObject(item, "object", object);
                }
                break;
            case 5: // Boolean
                if (index < Size) {
                    cJSON_AddBoolToObject(item, "bool", Data[index] % 2);
                    index++;
                }
                break;
        }
    }
    return item;
}

int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    cJSON *item = create_random_cJSON(Data, Size);
    if (item == NULL) return 0;

    // Test cJSON_IsNumber
    cJSON_IsNumber(item);

    // Test cJSON_IsString
    cJSON_IsString(item);

    // Test cJSON_IsArray
    cJSON_IsArray(item);

    // Test cJSON_IsNull
    cJSON_IsNull(item);

    // Test cJSON_AddItemReferenceToObject
    if (cJSON_IsObject(item)) {
        cJSON *child = cJSON_CreateString("child");
        if (child != NULL) {
            cJSON_AddItemReferenceToObject(item, "child_ref", child);
            cJSON_Delete(child);
        }
    }

    // Test cJSON_AddObjectToObject
    if (cJSON_IsObject(item)) {
        cJSON *new_object = cJSON_AddObjectToObject(item, "new_object");
        if (new_object != NULL) {
            cJSON_AddStringToObject(new_object, "key", "value");
        }
    }

    cJSON_Delete(item);
    return 0;
}