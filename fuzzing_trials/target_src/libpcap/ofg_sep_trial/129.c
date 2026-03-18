#include <stdint.h>
#include <stddef.h>
#include <pcap/pcap.h>

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0; // Not enough data to form an int
    }

    // Interpret the first 4 bytes of data as an int
    int tstamp_type = *(const int *)data;

    // Call the function-under-test
    const char *result = pcap_tstamp_type_val_to_name(tstamp_type);

    // Do something with the result to avoid compiler optimizations
    if (result != NULL) {
        volatile char c = result[0];
        (void)c;
    }

    return 0;
}