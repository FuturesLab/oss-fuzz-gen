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
#include <cstdlib>
#include <cstring>
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Create a new JSON tokener
    struct json_tokener *tok = json_tokener_new();
    if (!tok) {
        return 0;
    }

    // Set flags for the tokener
    json_tokener_set_flags(tok, 0);

    // Parse the input data
    json_object *jobj = NULL;
    enum json_tokener_error jerr;
    const char *inputStr = reinterpret_cast<const char*>(Data);
    int inputLen = static_cast<int>(Size);

    do {
        jobj = json_tokener_parse_ex(tok, inputStr, inputLen);
    } while ((jerr = json_tokener_get_error(tok)) == json_tokener_continue);

    // Check if there are extra characters after the parsed JSON object

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_tokener_get_error to json_object_set_serializer
    struct json_object* ret_json_tokener_parse_xcqke = json_tokener_parse((const char *)"r");
    if (ret_json_tokener_parse_xcqke == NULL){
    	return 0;
    }

    json_object_set_serializer(ret_json_tokener_parse_xcqke, NULL, (void *)tok, NULL);

    // End mutation: Producer.APPEND_MUTATOR

    if (json_tokener_get_parse_end(tok) < inputLen) {
        // Handle extra characters if needed
    }

    // Free the JSON object if it was successfully created
    if (jerr == json_tokener_success && jobj != NULL) {
        json_object_put(jobj);
    }

    // Reset the tokener for reuse
    json_tokener_reset(tok);

    // Clean up and free the tokener
    json_tokener_free(tok);

    return 0;
}