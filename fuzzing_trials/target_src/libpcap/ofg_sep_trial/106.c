#include <stdint.h>
#include <stddef.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    // Ensure that size is large enough to extract an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an int from the data
    int dlt_value = 0;
    for (size_t i = 0; i < sizeof(int); i++) {
        dlt_value |= data[i] << (i * 8);
    }

    // Call the function-under-test
    const char *description = pcap_datalink_val_to_description_or_dlt(dlt_value);

    // Use the description in some way to prevent compiler optimization issues
    if (description != NULL) {
        // For example, just check the first character
        volatile char first_char = description[0];
        (void)first_char;  // Prevent unused variable warning
    }

    return 0;
}