#include <fuzzer/FuzzedDataProvider.h>
#include <json-c/json_tokener.h>

extern "C" int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume an integer to use as the argument for json_tokener_new_ex
    int depth = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test
    struct json_tokener *tokener = json_tokener_new_ex(depth);

    // Clean up
    if (tokener) {
        json_tokener_free(tokener);
    }

    return 0;
}