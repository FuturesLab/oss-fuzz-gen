#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include "../cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Ensure the input is null-terminated for parsing
    char *jsonInput = new char[Size + 1];
    memcpy(jsonInput, Data, Size);
    jsonInput[Size] = '\0';

    const char *parse_end = nullptr;
    cJSON *json = cJSON_ParseWithOpts(jsonInput, &parse_end, cJSON_True);

    if (json != nullptr) {
        // Use cJSON_PrintBuffered
        char *bufferedOutput = cJSON_PrintBuffered(json, 1024, cJSON_True);
        if (bufferedOutput) {
            free(bufferedOutput);
        }

        // Use cJSON_Print
        char *formattedOutput = cJSON_Print(json);
        if (formattedOutput) {
            free(formattedOutput);
        }

        // Use cJSON_PrintUnformatted
        char *unformattedOutput = cJSON_PrintUnformatted(json);
        if (unformattedOutput) {
            free(unformattedOutput);
        }

        // Minify the JSON input
        cJSON_Minify(jsonInput);

        // Clean up the cJSON object
        cJSON_Delete(json);
    }

    delete[] jsonInput;
    return 0;
}