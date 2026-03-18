#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int tstamp_type = *(const int *)data;

    // Call the function-under-test
    const char *name = pcap_tstamp_type_val_to_name(tstamp_type);

    // Use the result in some way to prevent compiler optimizations
    if (name != NULL) {
        // For example, we could print it, but in a real fuzzing scenario,
        // we would avoid side effects like printing to stdout.
        (void)name; // Suppress unused variable warning
    }

    return 0;
}