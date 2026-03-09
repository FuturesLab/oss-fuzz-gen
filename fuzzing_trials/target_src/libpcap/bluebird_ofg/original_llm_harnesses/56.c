#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first 4 bytes of data as an integer
    int tstamp_type = *(const int*)data;

    // Call the function-under-test
    const char *description = pcap_tstamp_type_val_to_description(tstamp_type);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (description) {
        // For this fuzzing harness, we just check if the description is not NULL
        volatile const char *desc = description;
        (void)desc;
    }

    return 0;
}