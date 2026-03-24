#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a source json_object from the fuzzed data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString(fuzzed_data.remaining_bytes());
    struct json_object *src = json_tokener_parse(json_string.c_str());

    // Prepare a destination json_object pointer
    struct json_object *dst = nullptr;

    // Define a shallow copy function pointer, set to nullptr for default behavior
    json_c_shallow_copy_fn *shallow_copy_fn = nullptr;

    // Call the function-under-test
    json_object_deep_copy(src, &dst, shallow_copy_fn);

    // Clean up
    if (src) {
        json_object_put(src);
    }
    if (dst) {
        json_object_put(dst);
    }

    return 0;
}