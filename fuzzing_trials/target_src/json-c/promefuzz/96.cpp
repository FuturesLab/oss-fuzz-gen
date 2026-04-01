// This fuzz driver is generated for library json-c, aiming to fuzz the following functions:
// json_parse_uint64 at json_util.c:260:5 in json_util.h
// json_parse_int64 at json_util.c:243:5 in json_util.h
// json_object_new_int64 at json_object.c:799:21 in json_object.h
// json_object_get_int64 at json_object.c:819:9 in json_object.h
// json_object_int_inc at json_object.c:943:5 in json_object.h
// json_object_get_uint64 at json_object.c:872:10 in json_object.h
// json_object_put at json_object.c:272:5 in json_object.h
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
#include <cerrno>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <iostream>
#include "json_util.h"
#include "json_object.h"

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size) {
    // Ensure that the input data is null-terminated
    char *input_data = static_cast<char*>(malloc(Size + 1));
    if (!input_data) return 0;
    memcpy(input_data, Data, Size);
    input_data[Size] = '\0';

    // Test json_parse_uint64
    uint64_t uint64_val;
    int parse_uint64_result = json_parse_uint64(input_data, &uint64_val);

    // Test json_parse_int64
    int64_t int64_val;
    int parse_int64_result = json_parse_int64(input_data, &int64_val);

    // Test json_object_new_int64
    struct json_object *json_obj = json_object_new_int64(int64_val);
    if (json_obj) {
        // Test json_object_get_int64
        errno = 0;
        int64_t retrieved_int64 = json_object_get_int64(json_obj);

        // Test json_object_int_inc
        json_object_int_inc(json_obj, int64_val);

        // Test json_object_get_uint64
        errno = 0;
        uint64_t retrieved_uint64 = json_object_get_uint64(json_obj);

        // Cleanup
        json_object_put(json_obj);
    }

    free(input_data);
    return 0;
}