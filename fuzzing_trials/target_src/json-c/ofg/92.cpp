#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/printbuf.h"

extern "C" int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object
    struct json_object *jobj = json_object_new_object();
    if (!jobj) return 0; // Exit if json_object creation failed

    // Create a printbuf
    struct printbuf *pbuf = printbuf_new();
    if (!pbuf) {
        json_object_put(jobj); // Clean up json_object
        return 0; // Exit if printbuf creation failed
    }

    // Consume integers for the function parameters
    int level = fuzzed_data.ConsumeIntegral<int>();
    int flags = fuzzed_data.ConsumeIntegral<int>();

    // Fuzz the function
    json_object_double_to_json_string(jobj, pbuf, level, flags);

    // Clean up
    printbuf_free(pbuf);
    json_object_put(jobj);

    return 0;
}