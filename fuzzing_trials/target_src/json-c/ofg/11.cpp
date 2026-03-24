#include <fuzzer/FuzzedDataProvider.h>
#include <json-c/json_tokener.h>

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Call the function-under-test
    struct json_tokener *tokener = json_tokener_new();

    // Clean up
    if (tokener != nullptr) {
        json_tokener_free(tokener);
    }

    return 0;
}