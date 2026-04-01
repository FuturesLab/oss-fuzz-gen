#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object
    json_object *jobj = json_object_new_object();

    // Define a json_object_to_json_string_fn function
    json_object_to_json_string_fn *to_json_string_fn = 
        [](json_object *obj, struct printbuf *pb, int level, int flags) -> int {
            const char* json_str = json_object_to_json_string_ext(obj, flags);
            printbuf_memappend(pb, json_str, strlen(json_str));
            return 0;
        };

    // Create a dummy context
    void *dummy_context = reinterpret_cast<void*>(fuzzed_data.ConsumeIntegral<uintptr_t>());

    // Define a json_object_delete_fn function
    json_object_delete_fn *delete_fn = 
        [](json_object *obj, void *ptr) {
            // Do nothing
        };

    // Call the function-under-test
    json_object_set_serializer(jobj, to_json_string_fn, dummy_context, delete_fn);

    // Clean up
    json_object_put(jobj);

    return 0;
}