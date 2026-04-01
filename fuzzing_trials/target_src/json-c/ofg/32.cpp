#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <string>

extern "C" const char * json_util_get_last_err();

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Since json_util_get_last_err() does not take any input parameters,
    // we directly call the function to fuzz it.
    const char *error_message = json_util_get_last_err();

    // To avoid unused variable warnings, we can check if the error_message
    // is not nullptr and perform a trivial operation.
    if (error_message) {
        volatile size_t length = strlen(error_message);
        (void)length; // Use the length in a volatile context to avoid optimization.
    }

    return 0;
}