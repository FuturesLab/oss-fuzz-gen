#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider with the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object
    json_object *jobj = json_object_new_object();

    // Consume a pointer-sized integer from the fuzzed data to use as userdata
    void *userdata = reinterpret_cast<void*>(fuzzed_data.ConsumeIntegral<uintptr_t>());

    // Define a dummy delete function that does something observable
    json_object_delete_fn *delete_fn = [](json_object *obj, void *userdata) {
        // Perform an observable action, like logging
        std::cout << "Delete function called with userdata: " << userdata << std::endl;
    };

    // Call the function-under-test
    json_object_set_userdata(jobj, userdata, delete_fn);

    // Free the json_object, which should trigger the delete function
    json_object_put(jobj);

    return 0;
}