#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/printbuf.h"
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a json_object
    struct json_object *jobj = json_object_new_object();
    if (!jobj) return 0;  // Exit if creation failed

    // Create a printbuf
    struct printbuf *pbuf = printbuf_new();
    if (!pbuf) {
        json_object_put(jobj);
        return 0;  // Exit if creation failed
    }

    // Consume integers for the function parameters
    int level = fuzzed_data.ConsumeIntegral<int>();
    int flags = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test
    json_object_double_to_json_string(jobj, pbuf, level, flags);

    // Clean up
    json_object_put(jobj);
    printbuf_free(pbuf);

    return 0;
}