// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_GetNumberValue at cJSON.c:109:22 in cJSON.h
// cJSON_GetNumberValue at cJSON.c:109:22 in cJSON.h
// cJSON_GetNumberValue at cJSON.c:109:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include "cJSON.h"

static double get_double_from_data(const uint8_t *data, size_t size) {
    if (size < sizeof(double)) {
        return 0.0;
    }
    double value;
    memcpy(&value, data, sizeof(double));
    return value;
}

static const char* get_string_from_data(const uint8_t *data, size_t size) {
    if (size == 0) {
        return "";
    }
    char *str = (char *)malloc(size + 1);
    if (str == NULL) {
        return "";
    }
    memcpy(str, data, size);
    str[size] = '\0';
    return str;
}

int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a cJSON string item
    const char *string_data = get_string_from_data(Data, Size);
    cJSON *json_string = cJSON_CreateString(string_data);
    free((void*)string_data);

    // Create a cJSON number item
    double number_data = get_double_from_data(Data, Size);
    cJSON *json_number = cJSON_CreateNumber(number_data);

    // Get number value from json_number
    double value1 = cJSON_GetNumberValue(json_number);
    (void)value1; // Suppress unused variable warning

    // Get number value from json_string (should return NaN)
    double value2 = cJSON_GetNumberValue(json_string);
    (void)value2; // Suppress unused variable warning

    // Get number value from json_number again
    double value3 = cJSON_GetNumberValue(json_number);
    (void)value3; // Suppress unused variable warning

    // Clean up
    cJSON_Delete(json_string);
    cJSON_Delete(json_number);

    return 0;
}