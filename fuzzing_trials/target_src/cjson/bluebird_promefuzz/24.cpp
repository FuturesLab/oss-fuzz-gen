#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "../cJSON.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *jsonString = static_cast<char*>(malloc(Size + 1));
    if (!jsonString) {
        return 0;
    }
    memcpy(jsonString, Data, Size);
    jsonString[Size] = '\0';

    // Parse the JSON data
    cJSON *json = cJSON_Parse(jsonString);
    free(jsonString);

    if (json == nullptr) {
        return 0;
    }

    // Invoke the target functions
    cJSON_IsFalse(json);
    cJSON_IsObject(json);
    cJSON_IsTrue(json);
    cJSON_IsRaw(json);
    cJSON_IsString(json);
    cJSON_IsNull(json);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_DeleteItemFromArray
    double ret_cJSON_GetNumberValue_awckb = cJSON_GetNumberValue(json);
    if (ret_cJSON_GetNumberValue_awckb < 0){
    	return 0;
    }

    cJSON_DeleteItemFromArray(json, (int )ret_cJSON_GetNumberValue_awckb);

    // End mutation: Producer.APPEND_MUTATOR

    cJSON_Delete(json);

    return 0;
}