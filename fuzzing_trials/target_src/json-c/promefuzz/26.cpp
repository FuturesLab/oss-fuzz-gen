// This fuzz driver is generated for library json-c, aiming to fuzz the following functions:
// json_object_new_double_s at json_object.c:1180:21 in json_object.h
// json_object_put at json_object.c:272:5 in json_object.h
// json_object_new_double at json_object.c:1170:21 in json_object.h
// json_object_get_double at json_object.c:1223:8 in json_object.h
// json_object_put at json_object.c:272:5 in json_object.h
// json_object_new_double at json_object.c:1170:21 in json_object.h
// json_object_set_double at json_object.c:1281:5 in json_object.h
// json_object_put at json_object.c:272:5 in json_object.h
// json_parse_double at json_util.c:236:5 in json_util.h
// json_object_new_double at json_object.c:1170:21 in json_object.h
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
extern "C" {
#include <json_util.h>
#include <json_object.h>
#include <errno.h>
#include <stdint.h>
#include <math.h>
}

#include <fuzzer/FuzzedDataProvider.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    FuzzedDataProvider fuzzed_data(Data, Size);

    // Fuzzing json_object_new_double_s
    double double_value = fuzzed_data.ConsumeFloatingPoint<double>();
    std::string double_string = fuzzed_data.ConsumeRandomLengthString(100);
    struct json_object *obj_double_s = json_object_new_double_s(double_value, double_string.c_str());
    if (obj_double_s) {
        json_object_put(obj_double_s);
    }

    // Fuzzing json_object_get_double
    struct json_object *obj_double = json_object_new_double(double_value);
    if (obj_double) {
        errno = 0;
        double retrieved_double = json_object_get_double(obj_double);
        if (errno != 0) {
            // Handle error
        }
        json_object_put(obj_double);
    }

    // Fuzzing json_object_set_double
    struct json_object *obj_set_double = json_object_new_double(double_value);
    if (obj_set_double) {
        double new_double_value = fuzzed_data.ConsumeFloatingPoint<double>();
        int set_result = json_object_set_double(obj_set_double, new_double_value);
        if (set_result != 0) {
            // Successfully set the double value
        }
        json_object_put(obj_set_double);
    }

    // Fuzzing json_parse_double
    std::string parse_double_string = fuzzed_data.ConsumeRandomLengthString(100);
    double parsed_double;
    int parse_result = json_parse_double(parse_double_string.c_str(), &parsed_double);
    if (parse_result == 0) {
        // Successfully parsed the double
    }

    // Fuzzing json_object_get_uint64
    struct json_object *obj_uint64 = json_object_new_double(double_value);
    if (obj_uint64) {
        errno = 0;
        uint64_t retrieved_uint64 = json_object_get_uint64(obj_uint64);
        if (errno != 0) {
            // Handle error
        }
        json_object_put(obj_uint64);
    }

    return 0;
}