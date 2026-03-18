#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Call the function-under-test
    int version_number = sqlite3_libversion_number();

    // Optionally, use the version_number for further operations or checks
    // For the purpose of fuzzing, we just call the function

    return 0;
}