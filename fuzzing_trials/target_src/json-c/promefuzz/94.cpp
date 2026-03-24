// This fuzz driver is generated for library json-c, aiming to fuzz the following functions:
// json_parse_uint64 at json_util.c:260:5 in json_util.h
// json_parse_int64 at json_util.c:243:5 in json_util.h
// json_object_new_int64 at json_object.c:799:21 in json_object.h
// json_object_get_int64 at json_object.c:819:9 in json_object.h
// json_object_get_uint64 at json_object.c:872:10 in json_object.h
// json_object_int_inc at json_object.c:943:5 in json_object.h
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
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <json_util.h>
#include <json_object.h>
#include <limits.h>

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create a null-terminated string from the input data
    char *inputStr = static_cast<char *>(malloc(Size + 1));
    if (!inputStr) return 0;
    memcpy(inputStr, Data, Size);
    inputStr[Size] = '\0';

    // Fuzz json_parse_uint64
    uint64_t uint64_val;
    json_parse_uint64(inputStr, &uint64_val);

    // Fuzz json_parse_int64
    int64_t int64_val;
    json_parse_int64(inputStr, &int64_val);

    // Fuzz json_object_new_int64
    struct json_object *jsonObj = json_object_new_int64(int64_val);

    if (jsonObj) {
        // Fuzz json_object_get_int64
        errno = 0;
        json_object_get_int64(jsonObj);

        // Fuzz json_object_get_uint64
        errno = 0;
        json_object_get_uint64(jsonObj);

        // Fuzz json_object_int_inc with a random increment value
        int64_t inc_val = static_cast<int64_t>(Data[0]);
        json_object_int_inc(jsonObj, inc_val);

        // Proper cleanup
        json_object_put(jsonObj);
    }

    free(inputStr);
    return 0;
}