#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include "/src/json-c/json_visit.h"

extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object from a string
    std::string json_str = fuzzed_data.ConsumeRandomLengthString();
    struct json_object *src_obj = json_tokener_parse(json_str.c_str());

    // Create a destination json_object pointer
    struct json_object *dst_obj = nullptr;

    // Define a shallow copy function
    json_c_shallow_copy_fn *shallow_copy_fn = nullptr;

    // Call the function-under-test
    if (src_obj) {
        json_object_deep_copy(src_obj, &dst_obj, shallow_copy_fn);
    }

    // Clean up
    if (src_obj) {
        json_object_put(src_obj);
    }
    if (dst_obj) {
        json_object_put(dst_obj);
    }

    return 0;
}