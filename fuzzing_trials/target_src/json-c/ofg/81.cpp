#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object
    json_object *jobj = json_object_new_object();
    if (jobj == nullptr) {
        return 0; // If json_object creation fails, exit early
    }

    // Consume a pointer-sized value from the fuzzed data
    void *userdata = reinterpret_cast<void *>(fuzzed_data.ConsumeIntegral<uintptr_t>());

    // Consume a function pointer from the fuzzed data
    json_object_delete_fn *delete_fn = reinterpret_cast<json_object_delete_fn *>(fuzzed_data.ConsumeIntegral<uintptr_t>());

    // Call the function-under-test
    json_object_set_userdata(jobj, userdata, delete_fn);

    // Decrement reference count of json_object
    json_object_put(jobj);

    return 0;
}