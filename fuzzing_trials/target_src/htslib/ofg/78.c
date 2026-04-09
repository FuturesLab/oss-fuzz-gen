#include <stdint.h>
#include <stddef.h>

extern const char *hts_test_feature(unsigned int);

int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int feature = *(unsigned int *)data;

    // Call the function-under-test
    const char *result = hts_test_feature(feature);

    // Optionally, you can add some checks or logging here
    // For example, you can print the result if needed
    // printf("Feature: %u, Result: %s\n", feature, result);

    return 0;
}