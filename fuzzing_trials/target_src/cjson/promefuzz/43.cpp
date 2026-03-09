// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_GetStringValue at cJSON.c:99:22 in cJSON.h
// cJSON_CreateRaw at cJSON.c:2566:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2533:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

static void fuzz_cJSON_AddStringToObject(cJSON *object, const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    size_t name_len = Data[0] % (Size - 1);
    char *name = (char *)malloc(name_len + 1);
    if (!name) return;
    memcpy(name, Data + 1, name_len);
    name[name_len] = '\0';

    size_t string_len = Size - 1 - name_len;
    char *string = (char *)malloc(string_len + 1);
    if (!string) {
        free(name);
        return;
    }
    memcpy(string, Data + 1 + name_len, string_len);
    string[string_len] = '\0';

    cJSON_AddStringToObject(object, name, string);

    free(name);
    free(string);
}

static void fuzz_cJSON_GetStringValue(cJSON *item) {
    const char *value = cJSON_GetStringValue(item);
    if (value) {
        // Do something with the value if needed
    }
}

static void fuzz_cJSON_CreateRaw(const uint8_t *Data, size_t Size) {
    char *raw = (char *)malloc(Size + 1);
    if (!raw) return;
    memcpy(raw, Data, Size);
    raw[Size] = '\0';

    cJSON *raw_item = cJSON_CreateRaw(raw);
    if (raw_item) {
        cJSON_Delete(raw_item);
    }

    free(raw);
}

static void fuzz_cJSON_PrintUnformatted(cJSON *item) {
    if (item) {
        char *unformatted = cJSON_PrintUnformatted(item);
        if (unformatted) {
            free(unformatted);
        }
    }
}

static void fuzz_cJSON_CreateStringReference(const uint8_t *Data, size_t Size) {
    char *string = (char *)malloc(Size + 1);
    if (!string) return;
    memcpy(string, Data, Size);
    string[Size] = '\0';

    cJSON *string_ref = cJSON_CreateStringReference(string);
    if (string_ref) {
        cJSON_Delete(string_ref);
    }

    free(string);
}

static void fuzz_cJSON_Parse(const uint8_t *Data, size_t Size) {
    char *json_string = (char *)malloc(Size + 1);
    if (!json_string) return;
    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';

    cJSON *parsed = cJSON_Parse(json_string);
    if (parsed) {
        cJSON_Delete(parsed);
    }

    free(json_string);
}

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    cJSON *object = cJSON_CreateObject();
    if (!object) return 0;

    fuzz_cJSON_AddStringToObject(object, Data, Size);
    fuzz_cJSON_GetStringValue(object);
    fuzz_cJSON_CreateRaw(Data, Size);
    fuzz_cJSON_PrintUnformatted(object);
    fuzz_cJSON_CreateStringReference(Data, Size);
    fuzz_cJSON_Parse(Data, Size);

    cJSON_Delete(object);
    return 0;
}